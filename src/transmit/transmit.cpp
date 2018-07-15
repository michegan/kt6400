#include <QtDebug>
#include <QByteArray>

#include "cache.h"
#include "paraname.h"
#include "transmit.h"
#include "qextserialport.h"


// 通信
namespace Transmit
{
    // 数据发送
    bool send(const QByteArray& byteArray)
    {
        // 调试输出
        for (int i = 0; i < byteArray.length(); i += 100)
        {
            int length = qMin<int>(100, byteArray.length() - i);
            qDebug() << "Transmit send" << QString(byteArray.mid(i, length));
        }

        // 打开串口
        QextSerialPort serial = QextSerialPort("/dev/ttySAC0");
        if (serial.open(QIODevice::ReadWrite))
        {
            // 设置串口属性
            serial.setDataBits(DATA_8);
            serial.setParity(PAR_NONE);
            serial.setStopBits(STOP_1);
            serial.setBaudRate(BAUD9600);
            serial.setFlowControl(FLOW_OFF);
            serial.setTimeout(5, 0);

            // 数据发送
            int length = byteArray.length();
            int sended = serial.write(byteArray.data(), length);
            qDebug() << "Transmit send write" << length << sended;

            // 关闭串口
            serial.close();

            return (length == length);
        }
        else
        {
            qWarning() << "Transmit send open fail";
            return false;
        }
    }

    // 格式化
    QString format(int width, int value)
    {
        return QString("%1").arg(value, width, 10, QChar('0'));
    }

    QString format(int width, const QString& value)
    {
        return value.rightJustified(width, QChar('0'), true);
    }

    // 样本通信
    bool sendSample(const SampleInfo& sampleInfo, const ParaList& paraResult, const HistInfo& wbcHist, const HistInfo& rbcHist, const HistInfo& pltHist)
    {
        // 编码
        QByteArray byteArray;

        // 帧头
        byteArray.append("@");
        byteArray.append("a");

        // 样本编号：9位，不足左侧补0
        QString sampleId = Transmit::format(9, sampleInfo.sampleId);
        byteArray.append(sampleId);

        // 分析时间：14位
        QString testTime = sampleInfo.testTime.toString("yyyyMMddhhmmss");
        byteArray.append(testTime);

        // 参数结果：4位或5位，不足左侧补0
        // 其中，MCV，MCH，MCHC3个参数是5位，其他参数是4位长度
        // 参数顺序：
        // 例如：166h = 16.6↑ 066# = 6.6 1025l=102.5
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
                // 放大10倍之后再格式化，取小数点前面的数
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

        // 保留位（第109字节 -> 第114字节）
        byteArray.append("0");
        byteArray.append("1");
        byteArray.append("1");
        byteArray.append("0");
        byteArray.append("2");
        byteArray.append("1");

        // 病历号：15位，不足左侧补0
        QString patientId = Transmit::format(15, sampleInfo.patientId);
        byteArray.append(patientId);

        // 直方图报警：Rm R1 R2 R3 R4
        // 有对应报警，则填充r，无对应报警，则填充#
        byteArray.append("#");
        byteArray.append("#");
        byteArray.append("#");
        byteArray.append("#");
        byteArray.append("#");

        // 9个保留字节
        for (int i = 0; i < 9; i++)
        {
            byteArray.append("#");
        }

        // 4条白细胞直方图分类线
        for (int i = 0; i < 4; i++)
        {
            QString svalue = Transmit::format(3, wbcHist.lines[i]);
            byteArray.append(svalue);
        }
        // 2条红细胞直方图分类线
        for (int i = 0; i < 2; i++)
        {
            QString svalue = Transmit::format(3, rbcHist.lines[i]);
            byteArray.append(svalue);
        }
        // 2条血小板直方图分类线
        for (int i = 0; i < 2; i++)
        {
            QString svalue = Transmit::format(3, pltHist.lines[i] / 2);
            byteArray.append(svalue);
        }

        // 8个保留字节
        for (int i = 0; i < 8; i++)
        {
            byteArray.append("#");
        }

        // 白细胞直方图数据
        for (int i = 0; i < wbcHist.dataLen; i++)
        {
            QString svalue = Transmit::format(3, wbcHist.datas[i]);
            byteArray.append(svalue);
        }
        // 红细胞直方图数据
        for (int i = 0; i < rbcHist.dataLen; i++)
        {
            QString svalue = Transmit::format(3, rbcHist.datas[i]);
            byteArray.append(svalue);
        }
        // 血小板直方图数据
        for (int i = 0; i < pltHist.dataLen; i++)
        {
            QString svalue = Transmit::format(3, pltHist.datas[i]);
            byteArray.append(svalue);
        }

        // 帧尾
        byteArray.append("&");

        // 数据发送
        return Transmit::send(byteArray);
    }
}