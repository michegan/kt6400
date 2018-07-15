#include <QMap>

#include "modes.h"
#include "reagent.h"
#include "seqfile.h"


// ʱ���ļ�
namespace SeqFile
{
    // Һ·��ʼ��ʱ���
    QString initSeqNo()
    {
        return "Init";
    }

    // ������ϴʱ���
    QString startingUpSeqNo()
    {
        return "Starting_up";
    }

    // �ػ���ϴʱ��
    QString shutdownSeqNo()
    {
        return "Shutdown_Task";
    }

    // ��������ʱ����
    QString autoSleepEnterSeqNo()
    {
        return "Screen_Init";
    }

    // �˳�����ʱ���
    QString autoSleepExitSeqNo()
    {
        return "Screen_End";
    }

    // ������Ѫ��ʱ���
    QString lyseFillSeqNo()
    {
        return "Lyse_Fill_Task";
    }

    // ����ϡ��Һʱ���
    QString diluentFillSeqNo()
    {
        return "Diluent_Fill_Task";
    }

    // �Ŷ�ʱ���
    QString backFlushSeqNo()
    {
        return "Back_Flush_Task";
    }

    // ǿ���Ŷ�ʱ���
    QString enhancedFlushSeqNo()
    {
        return "Enhanced_Flush_Task";
    }

    // ��ϴʱ���
    QString cleanSeqNo()
    {
        return "Clean_Task";
    }

    // ǿ����ϴʱ���
    QString enhancedCleanSeqNo()
    {
        return "Enahanced_Clean_Task";
    }

    // ������עʱ���
    QString wholeFillSeqNo()
    {
        return "Whole_Fill_Task";
    }

    // �ſռ�����ʱ���
    QString emptyPoolSeqNo()
    {
        return "Empty_Pool_Task";
    }

    // ��ϡ��Һ׼��ʱ���
    QString diluentInitSeqNo()
    {
        return "Diluent_Init";
    }

    // ��ϡ��Һʱ���
    QString diluentFloodSeqNo()
    {
        return "Diluent_Flood_1000";
    }

    // ����ʱ���
    QString countSeqNo(const Modes& modes, int speed, int diluent, int lyse)
    {
        QString prefix = (PREPROCESS_MODE_PREDILUENT == modes.preprocessMode ? "Diluent" : "Test");

        // Diluent_40_100_120
        return QString("%1_%2_%3_%4").arg(prefix).arg(speed).arg(diluent).arg(lyse);
    }

    // ʱ��ʱ��
    float getSeqTime(const QString& seqNo)
    {
        QMap<QString, float> seqTimes;

        seqTimes.insert("Test_35_100_100", 105.0); // ����ʱ��
        seqTimes.insert("Test_35_100_120", 105.0); // ����ʱ��
        seqTimes.insert("Test_35_130_100", 105.0); // ����ʱ��
        seqTimes.insert("Test_35_130_120", 105.0); // ����ʱ��
        seqTimes.insert("Test_35_150_100", 105.0); // ����ʱ��
        seqTimes.insert("Test_35_150_120", 105.0); // ����ʱ��

        seqTimes.insert("Test_40_100_100", 90.0); // ����ʱ��
        seqTimes.insert("Test_40_100_120", 90.0); // ����ʱ��
        seqTimes.insert("Test_40_130_100", 90.0); // ����ʱ��
        seqTimes.insert("Test_40_130_120", 90.0); // ����ʱ��
        seqTimes.insert("Test_40_150_100", 90.0); // ����ʱ��
        seqTimes.insert("Test_40_150_120", 90.0); // ����ʱ��

        seqTimes.insert("Test_60_100_100", 70); // ����ʱ��
        seqTimes.insert("Test_60_100_120", 70); // ����ʱ��
        seqTimes.insert("Test_60_130_100", 70); // ����ʱ��
        seqTimes.insert("Test_60_130_120", 70); // ����ʱ��
        seqTimes.insert("Test_60_150_100", 70); // ����ʱ��
        seqTimes.insert("Test_60_150_120", 70); // ����ʱ��

        seqTimes.insert("Diluent_35_100_100", 100.0); // ����ʱ��
        seqTimes.insert("Diluent_35_100_120", 100.0); // ����ʱ��
        seqTimes.insert("Diluent_35_130_100", 100.0); // ����ʱ��
        seqTimes.insert("Diluent_35_130_120", 100.0); // ����ʱ��
        seqTimes.insert("Diluent_35_150_100", 100.0); // ����ʱ��
        seqTimes.insert("Diluent_35_150_120", 100.0); // ����ʱ��

        seqTimes.insert("Diluent_40_100_100", 90.0); // ����ʱ��
        seqTimes.insert("Diluent_40_100_120", 90.0); // ����ʱ��
        seqTimes.insert("Diluent_40_130_100", 90.0); // ����ʱ��
        seqTimes.insert("Diluent_40_130_120", 90.0); // ����ʱ��
        seqTimes.insert("Diluent_40_150_100", 90.0); // ����ʱ��
        seqTimes.insert("Diluent_40_150_120", 90.0); // ����ʱ��

        seqTimes.insert("Diluent_60_100_100", 70); // ����ʱ��
        seqTimes.insert("Diluent_60_100_120", 70); // ����ʱ��
        seqTimes.insert("Diluent_60_130_100", 70); // ����ʱ��
        seqTimes.insert("Diluent_60_130_120", 70); // ����ʱ��
        seqTimes.insert("Diluent_60_150_100", 70); // ����ʱ��
        seqTimes.insert("Diluent_60_150_120", 70); // ����ʱ��

        seqTimes.insert(SeqFile::initSeqNo(), 10); // Һ·��ʼ��ʱ���
        seqTimes.insert(SeqFile::lyseFillSeqNo(), 40.0); // ������Ѫ��ʱ���
        seqTimes.insert(SeqFile::diluentFillSeqNo(), 0x0023); // ����ϡ��Һʱ���
        seqTimes.insert(SeqFile::wholeFillSeqNo(), 120.0); // ������עʱ���
        seqTimes.insert(SeqFile::enhancedFlushSeqNo(), 32.0); // ǿ���Ŷ�ʱ���
        seqTimes.insert(SeqFile::enhancedCleanSeqNo(), 8.0); // ǿ����ϴʱ���
        seqTimes.insert(SeqFile::emptyPoolSeqNo(), 11.0); // �ſռ�����ʱ���
        seqTimes.insert(SeqFile::diluentInitSeqNo(), 10.0); // ��ϡ��Һ׼��ʱ���
        seqTimes.insert(SeqFile::diluentFloodSeqNo(), 10.0); // ��ϡ��Һʱ���
        seqTimes.insert(SeqFile::cleanSeqNo(), 0x003B); // ��ϴʱ���
        seqTimes.insert(SeqFile::startingUpSeqNo(), 50); // ������ϴʱ���
        seqTimes.insert(SeqFile::autoSleepEnterSeqNo(), 10.0); // ��������ʱ����
        seqTimes.insert(SeqFile::autoSleepExitSeqNo(), 10.0); // �˳�����ʱ���
        seqTimes.insert(SeqFile::shutdownSeqNo(), 0x001C); // �ػ���ϴʱ��
        seqTimes.insert(SeqFile::backFlushSeqNo(), 0x0028); // �Ŷ�ʱ���

#ifdef _WIN32
        return 3.0;
#else
        return seqTimes.value(seqNo, 30.0f);
#endif
    }

    // ʱ���Լ���������λml)
    float getSeqReagent(const QString& seqNo, int reagent)
    {
        if (REAGENT_LH == reagent)
        {
            QMap<QString, float> volumes;

            volumes.insert("Test_35_100_100", 105.0); // ����ʱ��
            volumes.insert("Test_35_100_120", 105.0); // ����ʱ��
            volumes.insert("Test_35_130_100", 105.0); // ����ʱ��
            volumes.insert("Test_35_130_120", 105.0); // ����ʱ��
            volumes.insert("Test_35_150_100", 105.0); // ����ʱ��
            volumes.insert("Test_35_150_120", 105.0); // ����ʱ��

            volumes.insert("Test_40_100_100", 90.0); // ����ʱ��
            volumes.insert("Test_40_100_120", 90.0); // ����ʱ��
            volumes.insert("Test_40_130_100", 90.0); // ����ʱ��
            volumes.insert("Test_40_130_120", 90.0); // ����ʱ��
            volumes.insert("Test_40_150_100", 90.0); // ����ʱ��
            volumes.insert("Test_40_150_120", 90.0); // ����ʱ��

            volumes.insert("Test_60_100_100", 64.0); // ����ʱ��
            volumes.insert("Test_60_100_120", 64.0); // ����ʱ��
            volumes.insert("Test_60_130_100", 64.0); // ����ʱ��
            volumes.insert("Test_60_130_120", 64.0); // ����ʱ��
            volumes.insert("Test_60_150_100", 64.0); // ����ʱ��
            volumes.insert("Test_60_150_120", 64.0); // ����ʱ��

            volumes.insert("Diluent_35_100_100", 100.0); // ����ʱ��
            volumes.insert("Diluent_35_100_120", 100.0); // ����ʱ��
            volumes.insert("Diluent_35_130_100", 100.0); // ����ʱ��
            volumes.insert("Diluent_35_130_120", 100.0); // ����ʱ��
            volumes.insert("Diluent_35_150_100", 100.0); // ����ʱ��
            volumes.insert("Diluent_35_150_120", 100.0); // ����ʱ��

            volumes.insert("Diluent_40_100_100", 90.0); // ����ʱ��
            volumes.insert("Diluent_40_100_120", 90.0); // ����ʱ��
            volumes.insert("Diluent_40_130_100", 90.0); // ����ʱ��
            volumes.insert("Diluent_40_130_120", 90.0); // ����ʱ��
            volumes.insert("Diluent_40_150_100", 90.0); // ����ʱ��
            volumes.insert("Diluent_40_150_120", 90.0); // ����ʱ��

            volumes.insert("Diluent_60_100_100", 72.0); // ����ʱ��
            volumes.insert("Diluent_60_100_120", 72.0); // ����ʱ��
            volumes.insert("Diluent_60_130_100", 72.0); // ����ʱ��
            volumes.insert("Diluent_60_130_120", 72.0); // ����ʱ��
            volumes.insert("Diluent_60_150_100", 72.0); // ����ʱ��
            volumes.insert("Diluent_60_150_120", 72.0); // ����ʱ��

            volumes.insert(SeqFile::initSeqNo(), 10.0); // Һ·��ʼ��ʱ���
            volumes.insert(SeqFile::lyseFillSeqNo(), 40.0); // ������Ѫ��ʱ���
            volumes.insert(SeqFile::diluentFillSeqNo(), 0x0023); // ����ϡ��Һʱ���
            volumes.insert(SeqFile::wholeFillSeqNo(), 120.0); // ������עʱ���
            volumes.insert(SeqFile::enhancedFlushSeqNo(), 32.0); // ǿ���Ŷ�ʱ���
            volumes.insert(SeqFile::enhancedCleanSeqNo(), 8.0); // ǿ����ϴʱ���
            volumes.insert(SeqFile::emptyPoolSeqNo(), 11.0); // �ſռ�����ʱ���
            volumes.insert(SeqFile::diluentInitSeqNo(), 10.0); // ��ϡ��Һ׼��ʱ���
            volumes.insert(SeqFile::diluentFloodSeqNo(), 10.0); // ��ϡ��Һʱ���
            volumes.insert(SeqFile::cleanSeqNo(), 0x003B); // ��ϴʱ���
            volumes.insert(SeqFile::startingUpSeqNo(), 0x003C); // ������ϴʱ���
            volumes.insert(SeqFile::autoSleepEnterSeqNo(), 10.0); // ��������ʱ����
            volumes.insert(SeqFile::autoSleepExitSeqNo(), 10.0); // �˳�����ʱ���
            volumes.insert(SeqFile::shutdownSeqNo(), 0x001C); // �ػ���ϴʱ��
            volumes.insert(SeqFile::backFlushSeqNo(), 0x0028); // �Ŷ�ʱ���

            return volumes.value(seqNo, 0);
        }
        else if (REAGENT_DT == reagent)
        {
            QMap<QString, float> volumes;

            volumes.insert("Test_35_100_100", 105.0); // ����ʱ��
            volumes.insert("Test_35_100_120", 105.0); // ����ʱ��
            volumes.insert("Test_35_130_100", 105.0); // ����ʱ��
            volumes.insert("Test_35_130_120", 105.0); // ����ʱ��
            volumes.insert("Test_35_150_100", 105.0); // ����ʱ��
            volumes.insert("Test_35_150_120", 105.0); // ����ʱ��

            volumes.insert("Test_40_100_100", 90.0); // ����ʱ��
            volumes.insert("Test_40_100_120", 90.0); // ����ʱ��
            volumes.insert("Test_40_130_100", 90.0); // ����ʱ��
            volumes.insert("Test_40_130_120", 90.0); // ����ʱ��
            volumes.insert("Test_40_150_100", 90.0); // ����ʱ��
            volumes.insert("Test_40_150_120", 90.0); // ����ʱ��

            volumes.insert("Test_60_100_100", 64.0); // ����ʱ��
            volumes.insert("Test_60_100_120", 64.0); // ����ʱ��
            volumes.insert("Test_60_130_100", 64.0); // ����ʱ��
            volumes.insert("Test_60_130_120", 64.0); // ����ʱ��
            volumes.insert("Test_60_150_100", 64.0); // ����ʱ��
            volumes.insert("Test_60_150_120", 64.0); // ����ʱ��

            volumes.insert("Diluent_35_100_100", 100.0); // ����ʱ��
            volumes.insert("Diluent_35_100_120", 100.0); // ����ʱ��
            volumes.insert("Diluent_35_130_100", 100.0); // ����ʱ��
            volumes.insert("Diluent_35_130_120", 100.0); // ����ʱ��
            volumes.insert("Diluent_35_150_100", 100.0); // ����ʱ��
            volumes.insert("Diluent_35_150_120", 100.0); // ����ʱ��

            volumes.insert("Diluent_40_100_100", 90.0); // ����ʱ��
            volumes.insert("Diluent_40_100_120", 90.0); // ����ʱ��
            volumes.insert("Diluent_40_130_100", 90.0); // ����ʱ��
            volumes.insert("Diluent_40_130_120", 90.0); // ����ʱ��
            volumes.insert("Diluent_40_150_100", 90.0); // ����ʱ��
            volumes.insert("Diluent_40_150_120", 90.0); // ����ʱ��

            volumes.insert("Diluent_60_100_100", 72.0); // ����ʱ��
            volumes.insert("Diluent_60_100_120", 72.0); // ����ʱ��
            volumes.insert("Diluent_60_130_100", 72.0); // ����ʱ��
            volumes.insert("Diluent_60_130_120", 72.0); // ����ʱ��
            volumes.insert("Diluent_60_150_100", 72.0); // ����ʱ��
            volumes.insert("Diluent_60_150_120", 72.0); // ����ʱ��

            volumes.insert(SeqFile::initSeqNo(), 10.0); // Һ·��ʼ��ʱ���
            volumes.insert(SeqFile::lyseFillSeqNo(), 40.0); // ������Ѫ��ʱ���
            volumes.insert(SeqFile::diluentFillSeqNo(), 0x0023); // ����ϡ��Һʱ���
            volumes.insert(SeqFile::wholeFillSeqNo(), 120.0); // ������עʱ���
            volumes.insert(SeqFile::enhancedFlushSeqNo(), 32.0); // ǿ���Ŷ�ʱ���
            volumes.insert(SeqFile::enhancedCleanSeqNo(), 8.0); // ǿ����ϴʱ���
            volumes.insert(SeqFile::emptyPoolSeqNo(), 11.0); // �ſռ�����ʱ���
            volumes.insert(SeqFile::diluentInitSeqNo(), 10.0); // ��ϡ��Һ׼��ʱ���
            volumes.insert(SeqFile::diluentFloodSeqNo(), 10.0); // ��ϡ��Һʱ���
            volumes.insert(SeqFile::cleanSeqNo(), 0x003B); // ��ϴʱ���
            volumes.insert(SeqFile::startingUpSeqNo(), 0x003C); // ������ϴʱ���
            volumes.insert(SeqFile::autoSleepEnterSeqNo(), 10.0); // ��������ʱ����
            volumes.insert(SeqFile::autoSleepExitSeqNo(), 10.0); // �˳�����ʱ���
            volumes.insert(SeqFile::shutdownSeqNo(), 0x001C); // �ػ���ϴʱ��
            volumes.insert(SeqFile::backFlushSeqNo(), 0x0028); // �Ŷ�ʱ���

            return volumes.value(seqNo, 0);
        }
        else
        {
            return 0;
        }
    }
}