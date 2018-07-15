#include <QtDebug>
#include <QByteArray>

#include "cache.h"
#include "paraname.h"
#include "transmit.h"
#include "qextserialport.h"


// ͨ��
namespace Transmit
{
    // ���ݷ���
    bool send(const QByteArray& byteArray)
    {
        // �������
        for (int i = 0; i < byteArray.length(); i += 100)
        {
            int length = qMin<int>(100, byteArray.length() - i);
            qDebug() << "Transmit send" << QString(byteArray.mid(i, length));
        }

        // �򿪴���
        QextSerialPort serial = QextSerialPort("/dev/ttySAC0");
        if (serial.open(QIODevice::ReadWrite))
        {
            // ���ô�������
            serial.setDataBits(DATA_8);
            serial.setParity(PAR_NONE);
            serial.setStopBits(STOP_1);
            serial.setBaudRate(BAUD9600);
            serial.setFlowControl(FLOW_OFF);
            serial.setTimeout(5, 0);

            // ���ݷ���
            int length = byteArray.length();
            int sended = serial.write(byteArray.data(), length);
            qDebug() << "Transmit send write" << length << sended;

            // �رմ���
            serial.close();

            return (length == length);
        }
        else
        {
            qWarning() << "Transmit send open fail";
            return false;
        }
    }

    // ��ʽ��
    QString format(int width, int value)
    {
        return QString("%1").arg(value, width, 10, QChar('0'));
    }

    QString format(int width, const QString& value)
    {
        return value.rightJustified(width, QChar('0'), true);
    }

    // ����ͨ��
    bool sendSample(const SampleInfo& sampleInfo, const ParaList& paraResult, const HistInfo& wbcHist, const HistInfo& rbcHist, const HistInfo& pltHist)
    {
        // ����
        QByteArray byteArray;

        // ֡ͷ
        byteArray.append("@");
        byteArray.append("a");

        // ������ţ�9λ��������ಹ0
        QString sampleId = Transmit::format(9, sampleInfo.sampleId);
        byteArray.append(sampleId);

        // ����ʱ�䣺14λ
        QString testTime = sampleInfo.testTime.toString("yyyyMMddhhmmss");
        byteArray.append(testTime);

        // ���������4λ��5λ��������ಹ0
        // ���У�MCV��MCH��MCHC3��������5λ������������4λ����
        // ����˳��
        // ���磺166h = 16.6�� 066# = 6.6 1025l=102.5
        QStringList names;
        names << PARA_WBC << PARA_LYM_PER << PARA_MID_PER << PARA_GRAN_PER << PARA_LYM_NUM << PARA_MID_NUM << PARA_GRAN_NUM;
        names << PARA_RBC << PARA_HGB << PARA_HCT << PARA_MCV << PARA_MCH << PARA_MCHC << PARA_RDW_CV << PARA_RDW_SD;
        names << PARA_PLT << PARA_MPV << PARA_PCT << PARA_PDW << PARA_PLCR;

        foreach (QString name, names)
        {
            int width = ((PARA_MCV == name || PARA_MCH == name || PARA_MCHC == name) ? 4 : 3);
        
            int flag = paraResult.paraFlag(name);
            if (PARA_NORMAL_FLAG == flag || PARA_H_FLAG == flag || PARA_L_FLAG == flag)
            {
                // �Ŵ�10��֮���ٸ�ʽ����ȡС����ǰ�����
                int value = (int)(paraResult.paraValue(name) * 10);

                QString svalue = Transmit::format(width, value);
                byteArray.append(svalue);

                if (PARA_NORMAL_FLAG == flag)
                {
                    byteArray.append("#");
                }
                else if (PARA_H_FLAG == flag)
                {
                    byteArray.append("h");
                }
                else if (PARA_L_FLAG == flag)
                {
                    byteArray.append("l");
                }
            }
            else if (PARA_ALARM_FLAG == flag)
            {
                QString svalue = QString().fill(QChar('*'), width);
                byteArray.append(svalue);

                byteArray.append("#");
            }
        }

        // ����λ����109�ֽ� -> ��114�ֽڣ�
        byteArray.append("0");
        byteArray.append("1");
        byteArray.append("1");
        byteArray.append("0");
        byteArray.append("2");
        byteArray.append("1");

        // �����ţ�15λ��������ಹ0
        QString patientId = Transmit::format(15, sampleInfo.patientId);
        byteArray.append(patientId);

        // ֱ��ͼ������Rm R1 R2 R3 R4
        // �ж�Ӧ�����������r���޶�Ӧ�����������#
        byteArray.append("#");
        byteArray.append("#");
        byteArray.append("#");
        byteArray.append("#");
        byteArray.append("#");

        // 9�������ֽ�
        for (int i = 0; i < 9; i++)
        {
            byteArray.append("#");
        }

        // 4����ϸ��ֱ��ͼ������
        for (int i = 0; i < 4; i++)
        {
            QString svalue = Transmit::format(3, wbcHist.lines[i]);
            byteArray.append(svalue);
        }
        // 2����ϸ��ֱ��ͼ������
        for (int i = 0; i < 2; i++)
        {
            QString svalue = Transmit::format(3, rbcHist.lines[i]);
            byteArray.append(svalue);
        }
        // 2��ѪС��ֱ��ͼ������
        for (int i = 0; i < 2; i++)
        {
            QString svalue = Transmit::format(3, pltHist.lines[i] / 2);
            byteArray.append(svalue);
        }

        // 8�������ֽ�
        for (int i = 0; i < 8; i++)
        {
            byteArray.append("#");
        }

        // ��ϸ��ֱ��ͼ����
        for (int i = 0; i < wbcHist.dataLen; i++)
        {
            QString svalue = Transmit::format(3, wbcHist.datas[i]);
            byteArray.append(svalue);
        }
        // ��ϸ��ֱ��ͼ����
        for (int i = 0; i < rbcHist.dataLen; i++)
        {
            QString svalue = Transmit::format(3, rbcHist.datas[i]);
            byteArray.append(svalue);
        }
        // ѪС��ֱ��ͼ����
        for (int i = 0; i < pltHist.dataLen; i++)
        {
            QString svalue = Transmit::format(3, pltHist.datas[i]);
            byteArray.append(svalue);
        }

        // ֡β
        byteArray.append("&");

        // ���ݷ���
        return Transmit::send(byteArray);
    }
}