#include <QtDebug>

#include "hal.h"
#include "cache.h"
#include "faultid.h"
#include "halfpga.h"
#include "mcucomm.h"
#include "utility.h"
#include "sysstate.h"
#include "qextserialport.h"


McuComm::McuComm()
    : QThread(), serial(0)
{
    // 通信串口
    this->serial = new QextSerialPort("/dev/ttySAC2");
    if (this->serial)
    {
        if (this->serial->open(QIODevice::ReadWrite))
        {
            this->serial->setDataBits(DATA_8);
            this->serial->setParity(PAR_NONE);
            this->serial->setStopBits(STOP_1);
            this->serial->setBaudRate(BAUD38400);
            this->serial->setFlowControl(FLOW_OFF);
            this->serial->setTimeout(1, 0);
            // 设定为5秒可能导致MCU上报的串口指令延迟，从而影响FPGA相关指令执行的时间准确性
            // this->serial->setTimeout(5, 0);

            qDebug() << "McuComm McuComm open success";
        }
        else
        {
            qWarning() << "McuComm McuComm open fail";
        }
    }
    else
    {
        qWarning() << "McuComm McuComm new fail";
    }
}

McuComm::~McuComm()
{
    // 通信串口
    if (this->serial)
    {
        delete this->serial;
        this->serial = 0;
    }
}

// 数据发送
bool McuComm::write(const QByteArray& dataArray)
{
#ifdef _WIN32
    return true;
#else
    // 通信串口
    if (0 == this->serial)
    {
        qWarning() << "McuComm write no serial";
        return false;
    }

    // 抓包
    qDebug() << "McuComm write";
    Utility::dump(dataArray);

    // 数据发送
    int length = dataArray.length();
    return (length == this->serial->write(dataArray.constData(), length));
#endif
}

bool McuComm::post(const QByteArray& dataArray)
{
    // 通信串口
    if (0 == this->serial)
    {
        qWarning() << "McuComm post no serial";
        return false;
    }

    QByteArray byteArray;

    // 组合包头包尾，添加校验和
    byteArray.append(0x68);
    byteArray.append(0x2B);
    byteArray.append(dataArray.length());
    byteArray.append(dataArray);
    byteArray.append(this->checkSum(byteArray));
    byteArray.append(0x16);

    // 抓包
    Utility::dump(byteArray);

    // 数据发送
    int length = byteArray.length();
    return (length == this->serial->write(byteArray.constData(), length));
}

bool McuComm::query(const QByteArray& dataArray, char* result)
{
    // 通信串口
    if (0 == this->serial)
    {
        qWarning() << "McuComm query no serial";
        return false;
    }

    bool ret = false;
    QByteArray byteArray;

    // 组合包头包尾，添加校验和
    byteArray.append(0x68);
    byteArray.append(0x29);
    byteArray.append(dataArray.length());
    byteArray.append(dataArray);
    byteArray.append(this->checkSum(byteArray));
    byteArray.append(0x16);

    // 抓包
    Utility::dump(byteArray);

    // 数据发送，然后等待一定延迟后，读取应答
    int length = byteArray.length();
    if (length == this->serial->write(byteArray.constData(), length))
    {
        QByteArray recvArray;
        int ack = byteArray.at(1);

        // 同步信号数据
        QSemaphore* sem = new QSemaphore();

        this->waitSem.insert(ack, sem);
        this->waitArray.insert(ack, recvArray);

        // 同步等待
        ret = sem->tryAcquire(1, 5);
        if (ret && result)
        {
            *result = recvArray.at(5);
        }

        // 摘除等待节点
        this->waitSem.remove(ack);
        this->waitArray.remove(ack);

        delete sem;
    }

    return ret;
}

// 计算校验和
char McuComm::checkSum(const QByteArray& byteArray)
{
    int sum = 0;

    for (int i = 1; i < byteArray.length(); i++)
    {
        sum += byteArray.at(i);
    }

    return (sum % 8);
}

// 线程执行体
void McuComm::run()
{
    qDebug() << "McuComm run";

    while (this->serial)
    {
        int bytes = this->serial->bytesAvailable();
        if (0 < bytes)
        {
            qDebug() << "McuComm run bytesAvailable" << bytes;

            // 串口数据就绪
            this->onReadyRead();
        }
    }
}

// 串口数据就绪
void McuComm::onReadyRead()
{
    // 读取数据
    QByteArray byteArray = this->serial->readAll();
    this->recvArray.append(byteArray);
    Utility::dump(byteArray);

    // 数据解析，检测到完成数据包就上报
    while (1)
    {
        // 提取一个完整的数据包
        byteArray = this->getOnePackage(this->recvArray);
        if (byteArray.isEmpty())
        {
            break;
        }

        // 协议关键字
        char ack = byteArray.at(1);

        // 同步信号数据处理
        if (this->waitArray.contains(ack))
        {
            this->waitArray[ack] = byteArray;
        }

        if (this->waitSem.contains(ack))
        {
            this->waitSem[ack]->release(1);
        }

        // 收到一个数据包处理
        this->onRecvOnePackage(byteArray);
        this->recvArray.remove(0, byteArray.length());
    }
}

// 收到一个数据包
void McuComm::onRecvOnePackage(const QByteArray& byteArray)
{
    // 抓包
    qDebug() << "McuComm onRecvOnePackage";
    Utility::dump(byteArray);

    if (0x40 == byteArray.at(1))
    {
        if (0x02 == byteArray.at(5))
        {
            if (0x00 == (byteArray.at(6) & 0xf0))
            {
                // 加载"水平电机故障"
                Cache::sysState()->raiseFault(FAULT_MOTOR_H);
            }
            else if (0x20 == (byteArray.at(6) & 0xf0))
            {
                // 加载"垂直电机故障"
                Cache::sysState()->raiseFault(FAULT_MOTOR_V);
            }
        }
        else if (0x03 == byteArray.at(5))
        {
            if (0x00 == (byteArray.at(6) & 0xf0))
            {
                //  加载"吸样泵电机故障"
                Cache::sysState()->raiseFault(FAULT_SYRINGE_1);
            }
            else if (0x20 == (byteArray.at(6) & 0xf0))
            {
                // 加载"负压泵电机故障"
                Cache::sysState()->raiseFault(FAULT_SYRINGE_2);
            }
        }
    }
    else if (0xa9 == byteArray.at(1))
    {
        // 废液满故障
        if (0x03 == byteArray.at(4))
        {
            Cache::sysState()->setFault(FAULT_WASTE_FULL, 1 == byteArray.at(5));
        }
        // 无稀释液故障
        else if (0x01 == byteArray.at(4))
        {
            Cache::sysState()->setFault(FAULT_NO_DILUENT, 1 == byteArray.at(5));
        }
        // 无溶血剂故障
        else if (0x00 == byteArray.at(4))
        {
            Cache::sysState()->setFault(FAULT_NO_LYSE, 1 == byteArray.at(5));
        }
    }
    else if (0xb6 == byteArray.at(1))
    {
        if (0x62 == byteArray.at(3))
        {
            // "68 b6 02 62 00 02 16 "
            // "68 b6 02 62 00 02 16 " 
            if (0x00 == byteArray.at(4))
            {
                // pEvtBuf->table[7] = 1;
                // 测试判断标志 1：可以测试 0：不可以测试
            }
        }
        else if (0x61 == byteArray.at(3))
        {
            // "68 b6 03 61 10 01 03 16 " 
            // "68 b6 03 61 10 00 02 16 " 
            if (0x10 == byteArray.at(4))
            {
                // 开启/关闭HGB灯
                HalFpga::write(HGB_LED, byteArray.at(5));
            }
            // "68 b6 05 61 18 00 c8 0a 06 16 " 
            else if (0x18 == byteArray.at(4))
            {
                // 采集HGB本底电压
                HalFpga::write(HGB_BK_COLLECT);
            }
            // "68 b6 05 61 19 00 c8 0a 07 16 " 
            else if (0x19 == byteArray.at(4))
            {
                // 采集HGB参考电压
                HalFpga::write(HGB_REF_COLLECT);
            }
            // "68 b6 03 61 15 01 00 16 " 
            // "68 b6 03 61 15 00 07 16 " 
            else if (0x15 == byteArray.at(4))
            {
                // 开启/关闭恒流源
                HalFpga::write(WBC_CONST, byteArray.at(5));
            }
            // "68 b6 04 61 11 00 64 00 16 " 
            else if (0x11 == byteArray.at(4))
            {
                // WBC灼烧
                HalFpga::write(WBC_BURN, byteArray.at(6));
            }
            // "68 b6 04 61 12 00 64 01 16 " 
            else if (0x12 == byteArray.at(4))
            {
                // RBC灼烧
                HalFpga::write(RBC_BURN, byteArray.at(6));
            }
            // "68 b6 04 61 16 00 64 05 16 " 
            else if (0x16 == byteArray.at(4))
            {
                // 开始采样
                HalFpga::write(WBC_RBC_PLT_COLLECT_START, byteArray.at(6));
            }
            // "68 b6 02 61 1a 03 16 " 
            else if (0x1A == byteArray.at(4))
            {
                // 停止采样
                HalFpga::write(WBC_RBC_PLT_COLLECT_STOP);

                // 上报数据采集结束
                emit dmaDataReady();
            }
        }
    }
}

// 提取一个数据包
QByteArray McuComm::getOnePackage(const QByteArray& byteArray)
{
    // 至少需要3个字节，byte 3表示可变参数长度
    if (3 < this->recvArray.length())
    {
        // 是否完整数据包
        int packLen = (5 + this->recvArray.at(2));
        if (packLen <= this->recvArray.length())
        {
            return this->recvArray.left(packLen);
        }
    }
    
    return QByteArray();
}