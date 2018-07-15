#include <QFile>
#include <QImage>
#include <QColor>
#include <QtDebug>

#include "path.h"
#include "utility.h"
#include "qextserialport.h"
#include "thermalprinter.h"


// 命令字符定义
#define CHAR_ESC                0x1B
#define CHAR_LF                 0x0A
#define CHAR_CR                 0x0D
#define CHAR_FD                 0xFD // 浓度设置
#define CHAR_BG                 0x06 // 进入设置
#define CHAR_ED                 0x16 // 设置完成


class ThermalPrinterPrivate
{
public:
    ThermalPrinterPrivate();
    ~ThermalPrinterPrivate();

    // 初始化
    bool init();

    // 自检
    bool selftest();

    // 是否缺纸
    bool hasPaper();

    // 是否走纸中
    bool isFeeding();

    // 是否打印中
    bool isPrinting();

    // 是否联机
    bool isConnected();

    // 是否打印机机头过热
    bool isSuperHeated();

    // 状态
    quint8 getState(quint8 para);

    // 走纸
    bool feed(quint8 ucLineNum = 50);

    // 设置走纸距离（单位：mm）
    bool setFeed(quint8 distance);

    // 设置行间距
    bool setLineSpace(quint8 space);

    // 设置浓度
    bool setConcentrationPrivate(int conCentration);

    // 打印一行
    bool printLine(const quint8* data, int dataLen);

private:
    // 读取状态
    quint8 getState1();

    // 接收
    int read(quint8* data, int maxSize);

    // 发送
    int send(const quint8* data, int maxSize);

public:
    // 串口
    QextSerialPort* serial;
};

ThermalPrinterPrivate::ThermalPrinterPrivate()
    : serial(new QextSerialPort("/dev/ttySAC1"))
{
    // 通信串口
    if (this->serial->open(QIODevice::ReadWrite))
    {
        this->serial->setDataBits(DATA_8);
        this->serial->setParity(PAR_NONE);
        this->serial->setStopBits(STOP_1);
        this->serial->setBaudRate(BAUD115200);
        this->serial->setFlowControl(FLOW_OFF);
        this->serial->setTimeout(5, 0);

        qDebug() << "QextSerialPort QextSerialPort open success";
    }
    else
    {
        qWarning() << "QextSerialPort QextSerialPort open fail";
    }
}

ThermalPrinterPrivate::~ThermalPrinterPrivate()
{
    delete this->serial;
}

// 初始化
bool ThermalPrinterPrivate::init()
{
    quint8 aucBuf[] = { CHAR_ESC, 0x40, 0x00 };
    return (sizeof(aucBuf) == this->send(aucBuf, sizeof(aucBuf)));
}

// 自检
bool ThermalPrinterPrivate::selftest()
{
    return true;
}

// 是否缺纸
bool ThermalPrinterPrivate::hasPaper()
{
    quint8 state = ThermalPrinterPrivate::getState1();

    // BIT5（0：不缺纸；1：缺纸）
    return (0x00 == (state & 0x20));
}

// 是否走纸中
bool ThermalPrinterPrivate::isFeeding()
{
    quint8 state = ThermalPrinterPrivate::getState1();

    // BIT3（0：空闲；1：走纸中）
    return (0x02 == (state & 0x02));
}

// 是否打印中
bool ThermalPrinterPrivate::isPrinting()
{
    quint8 state = ThermalPrinterPrivate::getState1();

    // BIT7（0：空闲；1：打印中）
    return (0x01 == (state & 0x01));
}

// 是否联机
bool ThermalPrinterPrivate::isConnected()
{
    quint8 state = this->getState1();

    // BIT3（0：联机；1：脱机）
    return (0x00 == (state & 0x08));
}

// 是否打印头过热
bool ThermalPrinterPrivate::isSuperHeated()
{
    quint8 state = this->getState1();

    // BIT6（0：不过热；1：过热）
    return (0x40 == (state & 0x40));
}

// 状态
quint8 ThermalPrinterPrivate::getState(quint8 para)
{
    quint8 state = 0x7B; // 默认都是错误状态

    do 
    {
#ifdef _WIN32
        state = 0x84; // 默认都是正确状态
#else
        // 发送查询指令
        quint8 aucBuf[] = { 0x10, 0x04, para };
        if (this->send(aucBuf, sizeof(aucBuf)) != sizeof(aucBuf))
        {
            qWarning() << "ThermalPrinterPrivate getState send fail";
            break;
        }

        // 读取查询结果
        Utility::msleep(2);

        if (1 != this->read(aucBuf, 1))
        {
            qWarning() << "ThermalPrinterPrivate getState read fail";
            break;
        }

        // 解析查询结果
        state = aucBuf[0];
#endif
        qDebug() << "ThermalPrinterPrivate getState state" << QString::number(state, 16);
    } while (0);

    return state;
}


// 走纸
bool ThermalPrinterPrivate::feed(quint8 ucLineNum)
{
    qDebug() << "ThermalPrinterPrivate feed" << ucLineNum;

    quint8 aucBuf[] = { CHAR_ESC, 'J', ucLineNum };
    return (sizeof(aucBuf) == this->send(aucBuf, sizeof(aucBuf)));
}

// 设置走纸距离（单位：mm）
// 先发送1B 06进入设置模式,最后发送1B 16确定设置
bool ThermalPrinterPrivate::setFeed(quint8 distance)
{
    bool ret = false;

    qDebug() << "ThermalPrinterPrivate setFeed" << distance;

    do 
    {
        // 进入设置模式
        quint8 aucBuf1[] = { CHAR_ESC, 0x06 };
        if (this->send(aucBuf1, sizeof(aucBuf1)) != sizeof(aucBuf1))
        {
            qWarning() << "ThermalPrinterPrivate setFeed send fail";
            break;
        }

        // 执行设置
        Utility::msleep(2);

        quint8 aucBuf2[] = { distance };
        if (1 != this->send(aucBuf2, sizeof(aucBuf2)))
        {
            qWarning() << "ThermalPrinterPrivate setFeed send fail";
            break;
        }

        // 确定设置
        quint8 aucBuf3[] = { CHAR_ESC, 0x16 };
        if (this->send(aucBuf3, sizeof(aucBuf3)) != sizeof(aucBuf3))
        {
            qWarning() << "ThermalPrinterPrivate setFeed send fail";
            break;
        }

        ret = true;
    } while (0);

    return ret;
}

// 设置行间距
bool ThermalPrinterPrivate::setLineSpace(quint8 space)
{
    qDebug() << "ThermalPrinterPrivate setLineSpace" << space;

    quint8 aucBuf[] = { CHAR_ESC, '1', space };
    return (sizeof(aucBuf) == this->send(aucBuf, sizeof(aucBuf)));
}

// 打印一行
bool ThermalPrinterPrivate::printLine(const quint8* data, int dataLen)
{
    bool ret = false;
    quint8* dataBuf = 0;
    int dataBufLen = dataLen + 6;

    do 
    {
        // 参数检测
        if (0 == data)
        {
            qWarning() << "ThermalPrinterPrivate printLine invalid para" << data << dataLen;
            break;
        }

        // 打印缓冲区
        dataBuf = new quint8[dataBufLen];
        if (0 == dataBuf)
        {
            qWarning() << "ThermalPrinterPrivate printLine new fail";
            break;
        }

        // 填充数据缓冲区
        *(dataBuf) = CHAR_ESC;
        *(dataBuf + 1) = 'K';
        *(dataBuf + 2) = (dataLen & 0xFF); // 点数
        *(dataBuf + 3) = ((dataLen >> 8) & 0xFF);
        memcpy(dataBuf + 4, data, dataLen); // 图形数据
        *(dataBuf + dataLen + 4) = CHAR_LF; // 结束符
        *(dataBuf + dataLen + 5) = CHAR_CR;

        // 发送数据缓冲区
        ret = true;
        for (int i = 0; i < dataBufLen; i+=16)
        {
            int size = qMin<int>(dataBufLen - i, 16);
            if (size != this->send(dataBuf + i, size))
            {
                ret = false;
                qWarning() << "ThermalPrinterPrivate printLine send fail" << size << i << dataBufLen;
                break;
            }
        }

    } while (0);

    // 释放内存
    if (dataBuf)
    {
        delete [] dataBuf;
    }

    return ret;
}

// 读取状态
quint8 ThermalPrinterPrivate::getState1()
{
    return this->getState(0x01);
}

// 热敏打印机通信（接收）
int ThermalPrinterPrivate::read(quint8* data, int maxSize)
{
    return (this->serial ? this->serial->read((char*)data, maxSize) : -1);
}

// 热敏打印机通信（发送）
int ThermalPrinterPrivate::send(const quint8* data, int maxSize)
{
    return (this->serial ? this->serial->write((char*)data, maxSize) : -1);
}

// 发送指令
bool ThermalPrinterPrivate::setConcentrationPrivate(int conCentration)
{
    {
        bool ret = false;

        qDebug() << "ThermalPrinter setConcentration" << conCentration;

        do 
        {
            // 进入设置模式
            quint8 aucBuf1[] = { CHAR_ESC, CHAR_BG };
            if (this->send(aucBuf1, sizeof(aucBuf1)) != sizeof(aucBuf1))
            {
                qWarning() << "ThermalPrinterPrivate setConcentration send fail";
                break;
            }

            // 执行设置
            Utility::msleep(2);

            quint8 aucBuf2[] = { CHAR_ESC, CHAR_FD, conCentration - 1};
            if (sizeof(aucBuf2) != this->send(aucBuf2, sizeof(aucBuf2)))
            {
                qWarning() << "ThermalPrinterPrivate setConcentration send fail";
                break;
            }

            // 确定设置
            quint8 aucBuf3[] = { CHAR_ESC, CHAR_ED };
            if (this->send(aucBuf3, sizeof(aucBuf3)) != sizeof(aucBuf3))
            {
                qWarning() << "ThermalPrinterPrivate setConcentration send fail";
                break;
            }

            ret = true;
        } while (0);

        return ret;
    }
}

ThermalPrinter::ThermalPrinter(const QString& name, int baudrate, int databits)
    : AbstractPrinter(), d(new ThermalPrinterPrivate())
{

}

ThermalPrinter::~ThermalPrinter()
{
    delete d;
}

// 初始化
bool ThermalPrinter::init()
{
    // 初始化，并设置行间距为0
    return (d->init() && d->setLineSpace(0));
}

// 是否缺纸
bool ThermalPrinter::hasPaper()
{
    return d->hasPaper();
}

// 命令
QStringList ThermalPrinter::cmds()
{
    QStringList cmds;
    cmds << THERMAL_PRINTER_CMD;
    return cmds;
}

// 是否联机
bool ThermalPrinter::isConnected()
{
    return d->isConnected();
}

// 是否打印头过热
bool ThermalPrinter::isSuperHeated()
{
    return d->isSuperHeated();
}

// 设置浓度
bool ThermalPrinter::setConcentration(int conCentration)
{
    return d->setConcentrationPrivate(conCentration);
}

// 打印
QString ThermalPrinter::print(const QHash<QString, QString>& paras)
{
    QString ret = PRINT_FAIL;

    do 
    {
        // 检测指定打印机是否连接
        if (!d->isConnected())
        {
            ret = "ERR_THERMAL_PRINTER_NO_PRINTER";
            qWarning() << "ThermalPrinter print no printer";
            break;
        }

        // 检测打印头是否过热
        if (d->isSuperHeated())
        {
            ret = "ERR_THERMAL_PRINTER_SUPER_HEATED";
            qWarning() << "ThermalPrinter print supper heated";
            break;
        }

        // 检测打印机是否缺纸
        if (!d->hasPaper())
        {
            ret = "ERR_THERMAL_PRINTER_OUT_OF_PAPER";
            qWarning() << "ThermalPrinter print no paper";
            break;
        }

        // 文件
        QString file = paras.value("FILE");
        qDebug() << "ThermalPrinter print" << file;

        if (!QFile::exists(file))
        {
            qWarning() << "ThermalPrinter print no file";
            break;
        }

        // 加载位图
        QImage image;
        if (!image.load(file, "BMP"))
        {
            qWarning() << "ThermalPrinter print load file";
            break;
        }

        // 判断方向
        if ("HORIZONTAL" == paras.value("ORIENTATION"))
        {
            QMatrix matrix;
            matrix.rotate(90);

            image = image.transformed(matrix);
        }

        // 高度宽度
        int height = image.height();
        int width = qMin<int>(384, image.width());

        // 分配缓冲区
        quint8* data = new quint8[width];
        if (0 == data)
        {
            qWarning() << "ThermalPrinter print new fail";
            break;
        }

        // 多页打印
        int pages = paras.value("PAGES", "1").toInt();
        for (int page = 0; page < pages; page++)
        {
            // 走纸
            d->feed(50);

            // 执行打印
            // 假如：384*640的位图，则一次发送384字节，发送640/8=80次；
            ret = PRINT_SUCCESS;
            for (int h = 0; h < height; h += 8)
            {
                memset(data, 0, sizeof(quint8) * width);
                for (int w = 0; w < width; w++)
                {
                    quint8 bits = 0;
                    for (int i = 0; i < 8; i++)
                    {
                        quint8 bit = 0; // 默认白
                        if (h + i < height)
                        {
                            // 位图是黑白的，颜色只有黑（0）和白（255）
                            QRgb rgb = image.pixel(w, h + i);
                            if (qRed(rgb) < 0x80)
                            {
                                bit = 0x01;
                            }
                        }
                        bits = ((bits << 1) | bit);
                    }
                    *(data + w) = bits;
                }

                // 下发数据
                if (!d->printLine(data, width))
                {
                    ret = PRINT_FAIL;
                    qWarning() << "ThermalPrinter print printLine fail" << h;

                    break;
                }

                // 热敏打印机缓存优先，串口读写缺少【硬件流控制】，所以通过增加延时的方式来处理；
                Utility::msleep(10);
            }

            // 走纸
            d->feed(100);

            // 打印
            if (PRINT_SUCCESS != ret)
            {
                qWarning() << "ThermalPrinter print fail" << page;
                break;
            }

            // 延时，避免乱码
            Utility::ssleep(2);
        }
    } while (0);

    return ret;
}