#include <QImage>
#include <QtDebug>
#include <QPainter>

#include "cache.h"
#include "paras.h"
#include "print.h"
#include "utility.h"
#include "datetime.h"
#include "language.h"
#include "paraname.h"
#include "sampleinfo.h"
#include "calfactorxml.h"
#include "qextserialport.h"


// ��ӡֽ�Ŵ�С
#define PRINTER_PAPER_WIDTH             (576)
#define PRINTER_PAPER_HEIGHT            (576)

#define RECORDER_PAPER_WIDTH            (576)

// �и�
#define PRINTER_ROW_HEIGHT              (40)

#define RECORDER_ROW_HEIGHT             (40)


class PrintPrivate
{
public:
    PrintPrivate();
    ~PrintPrivate();

    // �Ƿ����ô�ӡ
    bool isUsbPrint();

    // ��ȡ�ַ���
    QString getString(const QString& ids);

    // ��ӡ�ļ�
    QString newPrintFileName() const;

    // ������ӡ
    bool thermalPrint(const QImage* image);
    bool thermalPrint(const QByteArray& byteArray);

    // ��ӡ����
    bool usbPrintSample(QPainter& painter, const SampleInfo& sampleInfo, const ParaList& paraResult, 
                        const HistInfo& wbcHist, const HistInfo& rbcHist, const HistInfo& pltHist);

    bool thermalPrintSample(QPainter& painter, const SampleInfo& sampleInfo, const ParaList& paraResult, 
                            const HistInfo& wbcHist, const HistInfo& rbcHist, const HistInfo& pltHist);
    bool thermalPrintSampleVertical(QPainter& painter, const SampleInfo& sampleInfo, const ParaList& paraResult, 
                                    const HistInfo& wbcHist, const HistInfo& rbcHist, const HistInfo& pltHist);
    bool thermalPrintSampleHorizontal(QPainter& painter, const SampleInfo& sampleInfo, const ParaList& paraResult, 
                                      const HistInfo& wbcHist, const HistInfo& rbcHist, const HistInfo& pltHist);

    // ��ӡУ׼ϵ��
    bool usbPrintCalFactors(QPainter& painter, const QList<CalFactor>& peripheralCalFactors, 
                            const QList<CalFactor>& prediluentCalFactors, const QList<CalFactor>& wholeBloodCalFactors);

    bool thermalPrintCalFactors(QPainter& painter, float y, const QString& title, const QList<CalFactor>& calFactors);
    bool thermalPrintCalFactors(QPainter& painter, const QList<CalFactor>& peripheralCalFactors, 
                                const QList<CalFactor>& prediluentCalFactors, const QList<CalFactor>& wholeBloodCalFactors);

public:
};

PrintPrivate::PrintPrivate()
{

}

PrintPrivate::~PrintPrivate()
{

}

// �Ƿ����ô�ӡ
bool PrintPrivate::isUsbPrint()
{
    return false;
}

// ��ȡ�ַ���
QString PrintPrivate::getString(const QString& ids)
{
    return Language::getString(ids);
}

// ��ӡ�ļ�
QString PrintPrivate::newPrintFileName() const
{
    QString guid = Utility::newGuid();
    return QString("./%1.png").arg(guid);
}

// ������ӡ
bool PrintPrivate::thermalPrint(const QImage* image)
{
    bool ret = false;

    // ͼƬ��ת180��
    QMatrix matrix;
    matrix.rotate(180);
    QImage rImage = image->transformed(matrix); 

    // ��ӡ��ת���ͼƬ
    int width = rImage.width();
    int height = rImage.height();

    // ÿ10��1�����ݰ�
    for (int i = 0; i < height; i += 10)
    {
        QByteArray byteArray;
        byteArray.append(0x68);
        byteArray.append(0x02);
        byteArray.append(0x02);
        byteArray.append(0xDA);

        for (int n = 0; n < 10; n++)
        {
            byteArray.append(0xa5);
            for (int j = 0; j < width; j += 8)
            {
                quint8 bits = 0;
                for (int k = 0; k < 8; k++)
                {
                    QRgb rgb = rImage.pixel(j + k, i + n);

                    int r = qRed(rgb);
                    quint8 bit = (r < 0x80 ? 0x01 : 0x00);

                    bits = ((bits << 1) | bit);                
                }
                byteArray.append(bits);
            }
        }

        byteArray.append((char)0x00);
        byteArray.append(0x16);

        ret = this->thermalPrint(byteArray);
        if (!ret)
        {
            break;
        }
    }

    return ret;
}

bool PrintPrivate::thermalPrint(const QByteArray& byteArray)
{
    // ͨ�Ŵ���
    QextSerialPort serial("/dev/ttySAC1");
    if (serial.open(QIODevice::ReadWrite))
    {
        serial.setDataBits(DATA_8);
        serial.setParity(PAR_NONE);
        serial.setStopBits(STOP_1);
        serial.setBaudRate(BAUD115200);
        serial.setFlowControl(FLOW_OFF);
        serial.setTimeout(5, 0);

        int length = byteArray.length();
        int ret = serial.write(byteArray.constData(), length);
        qDebug() << "PrintPrivate thermalPrint" << length << ret;

        serial.close();

        return (ret == length);
    }
    else
    {
        qWarning() << "PrintPrivate thermalPrint open fail";
        return false;
    }
}

// ��ӡ����
bool PrintPrivate::usbPrintSample(QPainter& painter, const SampleInfo& sampleInfo, const ParaList& paraResult, 
                                  const HistInfo& wbcHist, const HistInfo& rbcHist, const HistInfo& pltHist)
{
    return true;
}

bool PrintPrivate::thermalPrintSample(QPainter& painter, const SampleInfo& sampleInfo, const ParaList& paraResult, 
                                      const HistInfo& wbcHist, const HistInfo& rbcHist, const HistInfo& pltHist)
{
    if (true) // ��ֱģ��
    {
        return this->thermalPrintSampleVertical(painter, sampleInfo, paraResult, wbcHist, rbcHist, pltHist);
    }
    else
    {
        return this->thermalPrintSampleHorizontal(painter, sampleInfo, paraResult, wbcHist, rbcHist, pltHist);
    }
}

bool PrintPrivate::thermalPrintSampleVertical(QPainter& painter, const SampleInfo& sampleInfo, const ParaList& paraResult, 
                                              const HistInfo& wbcHist, const HistInfo& rbcHist, const HistInfo& pltHist)
{
    int yoffset = 160;

    // ����
    {
        QRect rect = QRect(0, yoffset, RECORDER_PAPER_WIDTH, RECORDER_ROW_HEIGHT * 2);
        painter.drawText(rect, Qt::AlignCenter, "HEMATOLOGY REPOART");

        yoffset += 2 * RECORDER_ROW_HEIGHT;
    }

    // ������Ϣ��������Ϣ��6��4�У�
    {
        // ��1�У��������Ա����䡢���ҡ����š������ߣ�
        QStringList keys1;
        keys1 << "IDS_NAME" << "IDS_GENDER" << "IDS_AGE" << "IDS_DEPARTMENT" << "IDS_BED_NO" << "IDS_TESTOR";

        QStringList values1;
        values1 << sampleInfo.name << this->getString(sampleInfo.genderIds()) << sampleInfo.age 
                << sampleInfo.department << sampleInfo.bedNo << sampleInfo.tester;

        // ��2�У�������š�����ʱ�䡢ģʽ�������š��ͼ��ߡ�����ߣ�
        QStringList keys2;
        keys2 << "IDS_SAMPLE_ID" << "IDS_TEST_TIME" << "IDS_MODE" << "IDS_PATIENT_ID" << "IDS_SENDER" << "IDS_CHECKER";

        QStringList values2;
        values2 << sampleInfo.sampleId << DateTime::datetimeToStringC(sampleInfo.testTime) << this->getString(sampleInfo.modes.ids()) 
                << sampleInfo.patientId << sampleInfo.sender << sampleInfo.checker;

        for (int i = 0; i < 6; i++)
        {
            float y = yoffset + i * RECORDER_ROW_HEIGHT;

            painter.drawText(0, y, this->getString(keys1.at(i)));
            painter.drawText(100, y, values1.at(i));
            painter.drawText(300, y, this->getString(keys2.at(i)));
            painter.drawText(400, y, values2.at(i));
        }

        // 6������ + 1�п���
        yoffset += 7 * RECORDER_ROW_HEIGHT;
    }

    // �������⣨1��5�У����ơ��������λ���ο���Χ���ߵͱ�����
    {
        QStringList keys;
        keys << "IDS_NAME" << "IDS_RESULT" << "IDS_NULL" << "IDS_REF_RANGE" << "IDS_NULL";

        painter.drawText(0, yoffset, this->getString(keys.at(0)));
        painter.drawText(200, yoffset, this->getString(keys.at(1)));
        painter.drawText(260, yoffset, this->getString(keys.at(2)));
        painter.drawText(360, yoffset, this->getString(keys.at(3)));
        painter.drawText(520, yoffset, this->getString(keys.at(4)));

        // 1������
        yoffset += RECORDER_ROW_HEIGHT;
    }

    // ���������20��5�У����ơ��������λ���ο���Χ���ߵͱ�����
    {
        QStringList values;
        QStringList units;
        QStringList limits;
        QStringList alerts;

        QStringList names = Paras::reportParaNames();
        foreach (QString name, names)
        {
            Para para = paraResult.para(name);

            values.append(para.valueToString(2));
            units.append(para.unit);
            limits.append("4.0-10.0");
            alerts.append(para.flagToString());
        }

        for (int i = 0; i < names.length(); i++)
        {
            float y = yoffset + i * RECORDER_ROW_HEIGHT;

            painter.drawText(0, y, names.at(i));
            painter.drawText(200, y, values.at(i));
            painter.drawText(260, y, units.at(i));
            painter.drawText(360, y, limits.at(i));
            painter.drawText(500, y, alerts.at(i));
        }

        // 20���� + 1�п���
        yoffset += 21 * RECORDER_ROW_HEIGHT;
    }

    // WBCֱ��ͼ

    // RBCֱ��ͼ

    // PLTֱ��ͼ

    return true;
}

bool PrintPrivate::thermalPrintSampleHorizontal(QPainter& painter, const SampleInfo& sampleInfo, const ParaList& paraResult, 
                                                const HistInfo& wbcHist, const HistInfo& rbcHist, const HistInfo& pltHist)
{
    return true;
}

// ��ӡУ׼ϵ��
bool PrintPrivate::usbPrintCalFactors(QPainter& painter, const QList<CalFactor>& peripheralCalFactors, const QList<CalFactor>& prediluentCalFactors, 
                                      const QList<CalFactor>& wholeBloodCalFactors)
{
    const QStringList paraNames = Paras::calibrateParaNames();

    return false;
}

bool PrintPrivate::thermalPrintCalFactors(QPainter& painter, float y, const QString& title, const QList<CalFactor>& calFactors)
{
    // ����
    painter.drawText(200, y, title);

    QStringList items;
    items << "Para" << "Factor" << "Date";

    const QStringList paraNames = Paras::calibrateParaNames();
    foreach (QString paraName, paraNames)
    {
        foreach (CalFactor calFactor, calFactors)
        {
            if (calFactor.id == paraName)
            {
                items << paraName << QString::number(calFactor.value) << calFactor.date;
                break;
            }
        }
    }

    y += 50;
    for (int i = 0; i < items.length();)
    {
        painter.drawText(40, y, items.at(i));
        i++;

        painter.drawText(200, y, items.at(i));
        i++;

        painter.drawText(360, y, items.at(i));
        i++;

        y += RECORDER_ROW_HEIGHT;
    }

    return true;
}

bool PrintPrivate::thermalPrintCalFactors(QPainter& painter, const QList<CalFactor>& peripheralCalFactors, const QList<CalFactor>& prediluentCalFactors, 
                                          const QList<CalFactor>& wholeBloodCalFactors)
{
    // �������ӡ
    bool ret = this->thermalPrintCalFactors(painter, 50, "wholeBloodCalFactors", wholeBloodCalFactors);
    if (ret)
    {
        ret = this->thermalPrintCalFactors(painter, 250, "peripheralCalFactors", peripheralCalFactors);
        if (ret)
        {
            ret = this->thermalPrintCalFactors(painter, 450, "prediluentCalFactors", prediluentCalFactors);
        }
    }
    return ret;
}


Print::Print()
    : d(new PrintPrivate())
{

}

Print::~Print()
{
    delete d;
}

// ��ӡ����
bool Print::printSample(const SampleInfo& sampleInfo, const ParaList& paraResult, const HistInfo& wbcHist, const HistInfo& rbcHist, const HistInfo& pltHist)
{
    bool ret = false;
    QImage* image = 0;

    do 
    {
        // ��ӡ�豸
        bool usbPrint = d->isUsbPrint();

        // ֽ�Ŵ�С
        int width = (usbPrint ? PRINTER_PAPER_WIDTH : RECORDER_PAPER_WIDTH);
        int height = (usbPrint ? PRINTER_PAPER_HEIGHT : 1500);

        // ��ӡͼƬ
        image = new QImage(width, height, QImage::Format_Mono);
        if (0 == image)
        {
            break;
        }

        // ͼƬ����
        QPainter painter(image);

        painter.fillRect(0, 0, width, height, Qt::white);

        if (usbPrint)
        {
            ret = d->usbPrintSample(painter, sampleInfo, paraResult, wbcHist, rbcHist, pltHist);
        }
        else
        {
            ret = d->thermalPrintSample(painter, sampleInfo, paraResult, wbcHist, rbcHist, pltHist);
        }
        if (!ret)
        {
            break;
        }

        // ͼƬ����
        QString fileName = d->newPrintFileName();
        if (!image->save(fileName))
        {
            qWarning() << "Print printSample save fail" << fileName;
            break;
        }

        // ��ӡ���
        if (usbPrint)
        {
            ret = false;
        }
        else
        {
            ret = d->thermalPrint(image);
            if (!ret)
            {
                qWarning() << "Print printSample thermalPrint fail";
                break;
            }
        }
    } while (0);

    // ��Դ�ͷ�
    if (image)
    {
        delete image;
    }

    return ret;
}

// ��ӡУ׼ϵ��
bool Print::printCalFactors(const QList<CalFactor>& peripheralCalFactors, const QList<CalFactor>& prediluentCalFactors, const QList<CalFactor>& wholeBloodCalFactors)
{
    bool ret = false;
    QImage* image = 0;

    do 
    {
        // ��ӡ�豸
        bool usbPrint = d->isUsbPrint();

        // ֽ�Ŵ�С
        int width = (usbPrint ? PRINTER_PAPER_WIDTH : RECORDER_PAPER_WIDTH);
        int height = (usbPrint ? PRINTER_PAPER_HEIGHT : 500);

        // ��ӡͼƬ
        image = new QImage(width, height, QImage::Format_Mono);
        if (0 == image)
        {
            qWarning() << "Print printCalFactors new fail";
            break;
        }

        // ͼƬ����
        QPainter painter(image);

        painter.fillRect(0, 0, width, height, Qt::white);

        if (usbPrint)
        {
            ret = d->usbPrintCalFactors(painter, peripheralCalFactors, prediluentCalFactors, wholeBloodCalFactors);
            if (!ret)
            {
                qWarning() << "Print printCalFactors usbPrintCalFactors fail";
                break;
            }
        }
        else
        {
            ret = d->thermalPrintCalFactors(painter, peripheralCalFactors, prediluentCalFactors, wholeBloodCalFactors);
            if (!ret)
            {
                qWarning() << "Print printCalFactors thermalPrintCalFactors fail";
                break;
            }
        }

        // ͼƬ����
        QString fileName = d->newPrintFileName();
        if (!image->save(fileName))
        {
            qWarning() << "Print printCalFactors save fail" << fileName;
            break;
        }

        // ��ӡ���
        if (usbPrint)
        {
            ret = false;
        }
        else
        {
            ret = d->thermalPrint(image);
            if (!ret)
            {
                qWarning() << "Print printCalFactors thermalPrint fail";
                break;
            }
        }
    } while (0);

    // ��Դ�ͷ�
    if (image)
    {
        delete image;
    }

    return ret;
}