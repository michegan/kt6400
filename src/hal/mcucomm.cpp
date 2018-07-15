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
    // ͨ�Ŵ���
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
            // �趨Ϊ5����ܵ���MCU�ϱ��Ĵ���ָ���ӳ٣��Ӷ�Ӱ��FPGA���ָ��ִ�е�ʱ��׼ȷ��
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
    // ͨ�Ŵ���
    if (this->serial)
    {
        delete this->serial;
        this->serial = 0;
    }
}

// ���ݷ���
bool McuComm::write(const QByteArray& dataArray)
{
#ifdef _WIN32
    return true;
#else
    // ͨ�Ŵ���
    if (0 == this->serial)
    {
        qWarning() << "McuComm write no serial";
        return false;
    }

    // ץ��
    qDebug() << "McuComm write";
    Utility::dump(dataArray);

    // ���ݷ���
    int length = dataArray.length();
    return (length == this->serial->write(dataArray.constData(), length));
#endif
}

bool McuComm::post(const QByteArray& dataArray)
{
    // ͨ�Ŵ���
    if (0 == this->serial)
    {
        qWarning() << "McuComm post no serial";
        return false;
    }

    QByteArray byteArray;

    // ��ϰ�ͷ��β�����У���
    byteArray.append(0x68);
    byteArray.append(0x2B);
    byteArray.append(dataArray.length());
    byteArray.append(dataArray);
    byteArray.append(this->checkSum(byteArray));
    byteArray.append(0x16);

    // ץ��
    Utility::dump(byteArray);

    // ���ݷ���
    int length = byteArray.length();
    return (length == this->serial->write(byteArray.constData(), length));
}

bool McuComm::query(const QByteArray& dataArray, char* result)
{
    // ͨ�Ŵ���
    if (0 == this->serial)
    {
        qWarning() << "McuComm query no serial";
        return false;
    }

    bool ret = false;
    QByteArray byteArray;

    // ��ϰ�ͷ��β�����У���
    byteArray.append(0x68);
    byteArray.append(0x29);
    byteArray.append(dataArray.length());
    byteArray.append(dataArray);
    byteArray.append(this->checkSum(byteArray));
    byteArray.append(0x16);

    // ץ��
    Utility::dump(byteArray);

    // ���ݷ��ͣ�Ȼ��ȴ�һ���ӳٺ󣬶�ȡӦ��
    int length = byteArray.length();
    if (length == this->serial->write(byteArray.constData(), length))
    {
        QByteArray recvArray;
        int ack = byteArray.at(1);

        // ͬ���ź�����
        QSemaphore* sem = new QSemaphore();

        this->waitSem.insert(ack, sem);
        this->waitArray.insert(ack, recvArray);

        // ͬ���ȴ�
        ret = sem->tryAcquire(1, 5);
        if (ret && result)
        {
            *result = recvArray.at(5);
        }

        // ժ���ȴ��ڵ�
        this->waitSem.remove(ack);
        this->waitArray.remove(ack);

        delete sem;
    }

    return ret;
}

// ����У���
char McuComm::checkSum(const QByteArray& byteArray)
{
    int sum = 0;

    for (int i = 1; i < byteArray.length(); i++)
    {
        sum += byteArray.at(i);
    }

    return (sum % 8);
}

// �߳�ִ����
void McuComm::run()
{
    qDebug() << "McuComm run";

    while (this->serial)
    {
        int bytes = this->serial->bytesAvailable();
        if (0 < bytes)
        {
            qDebug() << "McuComm run bytesAvailable" << bytes;

            // �������ݾ���
            this->onReadyRead();
        }
    }
}

// �������ݾ���
void McuComm::onReadyRead()
{
    // ��ȡ����
    QByteArray byteArray = this->serial->readAll();
    this->recvArray.append(byteArray);
    Utility::dump(byteArray);

    // ���ݽ�������⵽������ݰ����ϱ�
    while (1)
    {
        // ��ȡһ�����������ݰ�
        byteArray = this->getOnePackage(this->recvArray);
        if (byteArray.isEmpty())
        {
            break;
        }

        // Э��ؼ���
        char ack = byteArray.at(1);

        // ͬ���ź����ݴ���
        if (this->waitArray.contains(ack))
        {
            this->waitArray[ack] = byteArray;
        }

        if (this->waitSem.contains(ack))
        {
            this->waitSem[ack]->release(1);
        }

        // �յ�һ�����ݰ�����
        this->onRecvOnePackage(byteArray);
        this->recvArray.remove(0, byteArray.length());
    }
}

// �յ�һ�����ݰ�
void McuComm::onRecvOnePackage(const QByteArray& byteArray)
{
    // ץ��
    qDebug() << "McuComm onRecvOnePackage";
    Utility::dump(byteArray);

    if (0x40 == byteArray.at(1))
    {
        if (0x02 == byteArray.at(5))
        {
            if (0x00 == (byteArray.at(6) & 0xf0))
            {
                // ����"ˮƽ�������"
                Cache::sysState()->raiseFault(FAULT_MOTOR_H);
            }
            else if (0x20 == (byteArray.at(6) & 0xf0))
            {
                // ����"��ֱ�������"
                Cache::sysState()->raiseFault(FAULT_MOTOR_V);
            }
        }
        else if (0x03 == byteArray.at(5))
        {
            if (0x00 == (byteArray.at(6) & 0xf0))
            {
                //  ����"�����õ������"
                Cache::sysState()->raiseFault(FAULT_SYRINGE_1);
            }
            else if (0x20 == (byteArray.at(6) & 0xf0))
            {
                // ����"��ѹ�õ������"
                Cache::sysState()->raiseFault(FAULT_SYRINGE_2);
            }
        }
    }
    else if (0xa9 == byteArray.at(1))
    {
        // ��Һ������
        if (0x03 == byteArray.at(4))
        {
            Cache::sysState()->setFault(FAULT_WASTE_FULL, 1 == byteArray.at(5));
        }
        // ��ϡ��Һ����
        else if (0x01 == byteArray.at(4))
        {
            Cache::sysState()->setFault(FAULT_NO_DILUENT, 1 == byteArray.at(5));
        }
        // ����Ѫ������
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
                // �����жϱ�־ 1�����Բ��� 0�������Բ���
            }
        }
        else if (0x61 == byteArray.at(3))
        {
            // "68 b6 03 61 10 01 03 16 " 
            // "68 b6 03 61 10 00 02 16 " 
            if (0x10 == byteArray.at(4))
            {
                // ����/�ر�HGB��
                HalFpga::write(HGB_LED, byteArray.at(5));
            }
            // "68 b6 05 61 18 00 c8 0a 06 16 " 
            else if (0x18 == byteArray.at(4))
            {
                // �ɼ�HGB���׵�ѹ
                HalFpga::write(HGB_BK_COLLECT);
            }
            // "68 b6 05 61 19 00 c8 0a 07 16 " 
            else if (0x19 == byteArray.at(4))
            {
                // �ɼ�HGB�ο���ѹ
                HalFpga::write(HGB_REF_COLLECT);
            }
            // "68 b6 03 61 15 01 00 16 " 
            // "68 b6 03 61 15 00 07 16 " 
            else if (0x15 == byteArray.at(4))
            {
                // ����/�رպ���Դ
                HalFpga::write(WBC_CONST, byteArray.at(5));
            }
            // "68 b6 04 61 11 00 64 00 16 " 
            else if (0x11 == byteArray.at(4))
            {
                // WBC����
                HalFpga::write(WBC_BURN, byteArray.at(6));
            }
            // "68 b6 04 61 12 00 64 01 16 " 
            else if (0x12 == byteArray.at(4))
            {
                // RBC����
                HalFpga::write(RBC_BURN, byteArray.at(6));
            }
            // "68 b6 04 61 16 00 64 05 16 " 
            else if (0x16 == byteArray.at(4))
            {
                // ��ʼ����
                HalFpga::write(WBC_RBC_PLT_COLLECT_START, byteArray.at(6));
            }
            // "68 b6 02 61 1a 03 16 " 
            else if (0x1A == byteArray.at(4))
            {
                // ֹͣ����
                HalFpga::write(WBC_RBC_PLT_COLLECT_STOP);

                // �ϱ����ݲɼ�����
                emit dmaDataReady();
            }
        }
    }
}

// ��ȡһ�����ݰ�
QByteArray McuComm::getOnePackage(const QByteArray& byteArray)
{
    // ������Ҫ3���ֽڣ�byte 3��ʾ�ɱ��������
    if (3 < this->recvArray.length())
    {
        // �Ƿ��������ݰ�
        int packLen = (5 + this->recvArray.at(2));
        if (packLen <= this->recvArray.length())
        {
            return this->recvArray.left(packLen);
        }
    }
    
    return QByteArray();
}