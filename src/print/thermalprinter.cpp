#include <QFile>
#include <QImage>
#include <QColor>
#include <QtDebug>

#include "path.h"
#include "utility.h"
#include "qextserialport.h"
#include "thermalprinter.h"


// �����ַ�����
#define CHAR_ESC                0x1B
#define CHAR_LF                 0x0A
#define CHAR_CR                 0x0D
#define CHAR_FD                 0xFD // Ũ������
#define CHAR_BG                 0x06 // ��������
#define CHAR_ED                 0x16 // �������


class ThermalPrinterPrivate
{
public:
    ThermalPrinterPrivate();
    ~ThermalPrinterPrivate();

    // ��ʼ��
    bool init();

    // �Լ죀
    bool selftest();

    // �Ƿ�ȱֽ
    bool hasPaper();

    // �Ƿ���ֽ��
    bool isFeeding();

    // �Ƿ��ӡ��
    bool isPrinting();

    // �Ƿ�����
    bool isConnected();

    // �Ƿ��ӡ����ͷ����
    bool isSuperHeated();

    // ״̬
    quint8 getState(quint8 para);

    // ��ֽ
    bool feed(quint8 ucLineNum = 50);

    // ������ֽ���루��λ��mm��
    bool setFeed(quint8 distance);

    // �����м��
    bool setLineSpace(quint8 space);

    // ����Ũ��
    bool setConcentrationPrivate(int conCentration);

    // ��ӡһ��
    bool printLine(const quint8* data, int dataLen);

private:
    // ��ȡ״̬
    quint8 getState1();

    // ����
    int read(quint8* data, int maxSize);

    // ����
    int send(const quint8* data, int maxSize);

public:
    // ����
    QextSerialPort* serial;
};

ThermalPrinterPrivate::ThermalPrinterPrivate()
    : serial(new QextSerialPort("/dev/ttySAC1"))
{
    // ͨ�Ŵ���
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

// ��ʼ��
bool ThermalPrinterPrivate::init()
{
    quint8 aucBuf[] = { CHAR_ESC, 0x40, 0x00 };
    return (sizeof(aucBuf) == this->send(aucBuf, sizeof(aucBuf)));
}

// �Լ�
bool ThermalPrinterPrivate::selftest()
{
    return true;
}

// �Ƿ�ȱֽ
bool ThermalPrinterPrivate::hasPaper()
{
    quint8 state = ThermalPrinterPrivate::getState1();

    // BIT5��0����ȱֽ��1��ȱֽ��
    return (0x00 == (state & 0x20));
}

// �Ƿ���ֽ��
bool ThermalPrinterPrivate::isFeeding()
{
    quint8 state = ThermalPrinterPrivate::getState1();

    // BIT3��0�����У�1����ֽ�У�
    return (0x02 == (state & 0x02));
}

// �Ƿ��ӡ��
bool ThermalPrinterPrivate::isPrinting()
{
    quint8 state = ThermalPrinterPrivate::getState1();

    // BIT7��0�����У�1����ӡ�У�
    return (0x01 == (state & 0x01));
}

// �Ƿ�����
bool ThermalPrinterPrivate::isConnected()
{
    quint8 state = this->getState1();

    // BIT3��0��������1���ѻ���
    return (0x00 == (state & 0x08));
}

// �Ƿ��ӡͷ����
bool ThermalPrinterPrivate::isSuperHeated()
{
    quint8 state = this->getState1();

    // BIT6��0�������ȣ�1�����ȣ�
    return (0x40 == (state & 0x40));
}

// ״̬
quint8 ThermalPrinterPrivate::getState(quint8 para)
{
    quint8 state = 0x7B; // Ĭ�϶��Ǵ���״̬

    do 
    {
#ifdef _WIN32
        state = 0x84; // Ĭ�϶�����ȷ״̬
#else
        // ���Ͳ�ѯָ��
        quint8 aucBuf[] = { 0x10, 0x04, para };
        if (this->send(aucBuf, sizeof(aucBuf)) != sizeof(aucBuf))
        {
            qWarning() << "ThermalPrinterPrivate getState send fail";
            break;
        }

        // ��ȡ��ѯ���
        Utility::msleep(2);

        if (1 != this->read(aucBuf, 1))
        {
            qWarning() << "ThermalPrinterPrivate getState read fail";
            break;
        }

        // ������ѯ���
        state = aucBuf[0];
#endif
        qDebug() << "ThermalPrinterPrivate getState state" << QString::number(state, 16);
    } while (0);

    return state;
}


// ��ֽ
bool ThermalPrinterPrivate::feed(quint8 ucLineNum)
{
    qDebug() << "ThermalPrinterPrivate feed" << ucLineNum;

    quint8 aucBuf[] = { CHAR_ESC, 'J', ucLineNum };
    return (sizeof(aucBuf) == this->send(aucBuf, sizeof(aucBuf)));
}

// ������ֽ���루��λ��mm��
// �ȷ���1B 06��������ģʽ,�����1B 16ȷ������
bool ThermalPrinterPrivate::setFeed(quint8 distance)
{
    bool ret = false;

    qDebug() << "ThermalPrinterPrivate setFeed" << distance;

    do 
    {
        // ��������ģʽ
        quint8 aucBuf1[] = { CHAR_ESC, 0x06 };
        if (this->send(aucBuf1, sizeof(aucBuf1)) != sizeof(aucBuf1))
        {
            qWarning() << "ThermalPrinterPrivate setFeed send fail";
            break;
        }

        // ִ������
        Utility::msleep(2);

        quint8 aucBuf2[] = { distance };
        if (1 != this->send(aucBuf2, sizeof(aucBuf2)))
        {
            qWarning() << "ThermalPrinterPrivate setFeed send fail";
            break;
        }

        // ȷ������
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

// �����м��
bool ThermalPrinterPrivate::setLineSpace(quint8 space)
{
    qDebug() << "ThermalPrinterPrivate setLineSpace" << space;

    quint8 aucBuf[] = { CHAR_ESC, '1', space };
    return (sizeof(aucBuf) == this->send(aucBuf, sizeof(aucBuf)));
}

// ��ӡһ��
bool ThermalPrinterPrivate::printLine(const quint8* data, int dataLen)
{
    bool ret = false;
    quint8* dataBuf = 0;
    int dataBufLen = dataLen + 6;

    do 
    {
        // �������
        if (0 == data)
        {
            qWarning() << "ThermalPrinterPrivate printLine invalid para" << data << dataLen;
            break;
        }

        // ��ӡ������
        dataBuf = new quint8[dataBufLen];
        if (0 == dataBuf)
        {
            qWarning() << "ThermalPrinterPrivate printLine new fail";
            break;
        }

        // ������ݻ�����
        *(dataBuf) = CHAR_ESC;
        *(dataBuf + 1) = 'K';
        *(dataBuf + 2) = (dataLen & 0xFF); // ����
        *(dataBuf + 3) = ((dataLen >> 8) & 0xFF);
        memcpy(dataBuf + 4, data, dataLen); // ͼ������
        *(dataBuf + dataLen + 4) = CHAR_LF; // ������
        *(dataBuf + dataLen + 5) = CHAR_CR;

        // �������ݻ�����
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

    // �ͷ��ڴ�
    if (dataBuf)
    {
        delete [] dataBuf;
    }

    return ret;
}

// ��ȡ״̬
quint8 ThermalPrinterPrivate::getState1()
{
    return this->getState(0x01);
}

// ������ӡ��ͨ�ţ����գ�
int ThermalPrinterPrivate::read(quint8* data, int maxSize)
{
    return (this->serial ? this->serial->read((char*)data, maxSize) : -1);
}

// ������ӡ��ͨ�ţ����ͣ�
int ThermalPrinterPrivate::send(const quint8* data, int maxSize)
{
    return (this->serial ? this->serial->write((char*)data, maxSize) : -1);
}

// ����ָ��
bool ThermalPrinterPrivate::setConcentrationPrivate(int conCentration)
{
    {
        bool ret = false;

        qDebug() << "ThermalPrinter setConcentration" << conCentration;

        do 
        {
            // ��������ģʽ
            quint8 aucBuf1[] = { CHAR_ESC, CHAR_BG };
            if (this->send(aucBuf1, sizeof(aucBuf1)) != sizeof(aucBuf1))
            {
                qWarning() << "ThermalPrinterPrivate setConcentration send fail";
                break;
            }

            // ִ������
            Utility::msleep(2);

            quint8 aucBuf2[] = { CHAR_ESC, CHAR_FD, conCentration - 1};
            if (sizeof(aucBuf2) != this->send(aucBuf2, sizeof(aucBuf2)))
            {
                qWarning() << "ThermalPrinterPrivate setConcentration send fail";
                break;
            }

            // ȷ������
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

// ��ʼ��
bool ThermalPrinter::init()
{
    // ��ʼ�����������м��Ϊ0
    return (d->init() && d->setLineSpace(0));
}

// �Ƿ�ȱֽ
bool ThermalPrinter::hasPaper()
{
    return d->hasPaper();
}

// ����
QStringList ThermalPrinter::cmds()
{
    QStringList cmds;
    cmds << THERMAL_PRINTER_CMD;
    return cmds;
}

// �Ƿ�����
bool ThermalPrinter::isConnected()
{
    return d->isConnected();
}

// �Ƿ��ӡͷ����
bool ThermalPrinter::isSuperHeated()
{
    return d->isSuperHeated();
}

// ����Ũ��
bool ThermalPrinter::setConcentration(int conCentration)
{
    return d->setConcentrationPrivate(conCentration);
}

// ��ӡ
QString ThermalPrinter::print(const QHash<QString, QString>& paras)
{
    QString ret = PRINT_FAIL;

    do 
    {
        // ���ָ����ӡ���Ƿ�����
        if (!d->isConnected())
        {
            ret = "ERR_THERMAL_PRINTER_NO_PRINTER";
            qWarning() << "ThermalPrinter print no printer";
            break;
        }

        // ����ӡͷ�Ƿ����
        if (d->isSuperHeated())
        {
            ret = "ERR_THERMAL_PRINTER_SUPER_HEATED";
            qWarning() << "ThermalPrinter print supper heated";
            break;
        }

        // ����ӡ���Ƿ�ȱֽ
        if (!d->hasPaper())
        {
            ret = "ERR_THERMAL_PRINTER_OUT_OF_PAPER";
            qWarning() << "ThermalPrinter print no paper";
            break;
        }

        // �ļ�
        QString file = paras.value("FILE");
        qDebug() << "ThermalPrinter print" << file;

        if (!QFile::exists(file))
        {
            qWarning() << "ThermalPrinter print no file";
            break;
        }

        // ����λͼ
        QImage image;
        if (!image.load(file, "BMP"))
        {
            qWarning() << "ThermalPrinter print load file";
            break;
        }

        // �жϷ���
        if ("HORIZONTAL" == paras.value("ORIENTATION"))
        {
            QMatrix matrix;
            matrix.rotate(90);

            image = image.transformed(matrix);
        }

        // �߶ȿ��
        int height = image.height();
        int width = qMin<int>(384, image.width());

        // ���仺����
        quint8* data = new quint8[width];
        if (0 == data)
        {
            qWarning() << "ThermalPrinter print new fail";
            break;
        }

        // ��ҳ��ӡ
        int pages = paras.value("PAGES", "1").toInt();
        for (int page = 0; page < pages; page++)
        {
            // ��ֽ
            d->feed(50);

            // ִ�д�ӡ
            // ���磺384*640��λͼ����һ�η���384�ֽڣ�����640/8=80�Σ�
            ret = PRINT_SUCCESS;
            for (int h = 0; h < height; h += 8)
            {
                memset(data, 0, sizeof(quint8) * width);
                for (int w = 0; w < width; w++)
                {
                    quint8 bits = 0;
                    for (int i = 0; i < 8; i++)
                    {
                        quint8 bit = 0; // Ĭ�ϰ�
                        if (h + i < height)
                        {
                            // λͼ�Ǻڰ׵ģ���ɫֻ�кڣ�0���Ͱף�255��
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

                // �·�����
                if (!d->printLine(data, width))
                {
                    ret = PRINT_FAIL;
                    qWarning() << "ThermalPrinter print printLine fail" << h;

                    break;
                }

                // ������ӡ���������ȣ����ڶ�дȱ�١�Ӳ�������ơ�������ͨ��������ʱ�ķ�ʽ������
                Utility::msleep(10);
            }

            // ��ֽ
            d->feed(100);

            // ��ӡ
            if (PRINT_SUCCESS != ret)
            {
                qWarning() << "ThermalPrinter print fail" << page;
                break;
            }

            // ��ʱ����������
            Utility::ssleep(2);
        }
    } while (0);

    return ret;
}