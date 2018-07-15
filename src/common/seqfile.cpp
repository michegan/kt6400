#include <QMap>

#include "modes.h"
#include "reagent.h"
#include "seqfile.h"


// 时序文件
namespace SeqFile
{
    // 液路初始化时序号
    QString initSeqNo()
    {
        return "Init";
    }

    // 开机清洗时序号
    QString startingUpSeqNo()
    {
        return "Starting_up";
    }

    // 关机清洗时序
    QString shutdownSeqNo()
    {
        return "Shutdown_Task";
    }

    // 进入休眠时序序
    QString autoSleepEnterSeqNo()
    {
        return "Screen_Init";
    }

    // 退出休眠时序号
    QString autoSleepExitSeqNo()
    {
        return "Screen_End";
    }

    // 更换溶血剂时序号
    QString lyseFillSeqNo()
    {
        return "Lyse_Fill_Task";
    }

    // 更换稀释液时序号
    QString diluentFillSeqNo()
    {
        return "Diluent_Fill_Task";
    }

    // 排堵时序号
    QString backFlushSeqNo()
    {
        return "Back_Flush_Task";
    }

    // 强力排堵时序号
    QString enhancedFlushSeqNo()
    {
        return "Enhanced_Flush_Task";
    }

    // 清洗时序号
    QString cleanSeqNo()
    {
        return "Clean_Task";
    }

    // 强力清洗时序号
    QString enhancedCleanSeqNo()
    {
        return "Enahanced_Clean_Task";
    }

    // 整机灌注时序号
    QString wholeFillSeqNo()
    {
        return "Whole_Fill_Task";
    }

    // 排空计数池时序号
    QString emptyPoolSeqNo()
    {
        return "Empty_Pool_Task";
    }

    // 加稀释液准备时序号
    QString diluentInitSeqNo()
    {
        return "Diluent_Init";
    }

    // 加稀释液时序号
    QString diluentFloodSeqNo()
    {
        return "Diluent_Flood_1000";
    }

    // 计数时序号
    QString countSeqNo(const Modes& modes, int speed, int diluent, int lyse)
    {
        QString prefix = (PREPROCESS_MODE_PREDILUENT == modes.preprocessMode ? "Diluent" : "Test");

        // Diluent_40_100_120
        return QString("%1_%2_%3_%4").arg(prefix).arg(speed).arg(diluent).arg(lyse);
    }

    // 时序时间
    float getSeqTime(const QString& seqNo)
    {
        QMap<QString, float> seqTimes;

        seqTimes.insert("Test_35_100_100", 105.0); // 计数时序
        seqTimes.insert("Test_35_100_120", 105.0); // 计数时序
        seqTimes.insert("Test_35_130_100", 105.0); // 计数时序
        seqTimes.insert("Test_35_130_120", 105.0); // 计数时序
        seqTimes.insert("Test_35_150_100", 105.0); // 计数时序
        seqTimes.insert("Test_35_150_120", 105.0); // 计数时序

        seqTimes.insert("Test_40_100_100", 90.0); // 计数时序
        seqTimes.insert("Test_40_100_120", 90.0); // 计数时序
        seqTimes.insert("Test_40_130_100", 90.0); // 计数时序
        seqTimes.insert("Test_40_130_120", 90.0); // 计数时序
        seqTimes.insert("Test_40_150_100", 90.0); // 计数时序
        seqTimes.insert("Test_40_150_120", 90.0); // 计数时序

        seqTimes.insert("Test_60_100_100", 70); // 计数时序
        seqTimes.insert("Test_60_100_120", 70); // 计数时序
        seqTimes.insert("Test_60_130_100", 70); // 计数时序
        seqTimes.insert("Test_60_130_120", 70); // 计数时序
        seqTimes.insert("Test_60_150_100", 70); // 计数时序
        seqTimes.insert("Test_60_150_120", 70); // 计数时序

        seqTimes.insert("Diluent_35_100_100", 100.0); // 计数时序
        seqTimes.insert("Diluent_35_100_120", 100.0); // 计数时序
        seqTimes.insert("Diluent_35_130_100", 100.0); // 计数时序
        seqTimes.insert("Diluent_35_130_120", 100.0); // 计数时序
        seqTimes.insert("Diluent_35_150_100", 100.0); // 计数时序
        seqTimes.insert("Diluent_35_150_120", 100.0); // 计数时序

        seqTimes.insert("Diluent_40_100_100", 90.0); // 计数时序
        seqTimes.insert("Diluent_40_100_120", 90.0); // 计数时序
        seqTimes.insert("Diluent_40_130_100", 90.0); // 计数时序
        seqTimes.insert("Diluent_40_130_120", 90.0); // 计数时序
        seqTimes.insert("Diluent_40_150_100", 90.0); // 计数时序
        seqTimes.insert("Diluent_40_150_120", 90.0); // 计数时序

        seqTimes.insert("Diluent_60_100_100", 70); // 计数时序
        seqTimes.insert("Diluent_60_100_120", 70); // 计数时序
        seqTimes.insert("Diluent_60_130_100", 70); // 计数时序
        seqTimes.insert("Diluent_60_130_120", 70); // 计数时序
        seqTimes.insert("Diluent_60_150_100", 70); // 计数时序
        seqTimes.insert("Diluent_60_150_120", 70); // 计数时序

        seqTimes.insert(SeqFile::initSeqNo(), 10); // 液路初始化时序号
        seqTimes.insert(SeqFile::lyseFillSeqNo(), 40.0); // 更换溶血剂时序号
        seqTimes.insert(SeqFile::diluentFillSeqNo(), 0x0023); // 更换稀释液时序号
        seqTimes.insert(SeqFile::wholeFillSeqNo(), 120.0); // 整机灌注时序号
        seqTimes.insert(SeqFile::enhancedFlushSeqNo(), 32.0); // 强力排堵时序号
        seqTimes.insert(SeqFile::enhancedCleanSeqNo(), 8.0); // 强力清洗时序号
        seqTimes.insert(SeqFile::emptyPoolSeqNo(), 11.0); // 排空计数池时序号
        seqTimes.insert(SeqFile::diluentInitSeqNo(), 10.0); // 加稀释液准备时序号
        seqTimes.insert(SeqFile::diluentFloodSeqNo(), 10.0); // 加稀释液时序号
        seqTimes.insert(SeqFile::cleanSeqNo(), 0x003B); // 清洗时序号
        seqTimes.insert(SeqFile::startingUpSeqNo(), 50); // 开机清洗时序号
        seqTimes.insert(SeqFile::autoSleepEnterSeqNo(), 10.0); // 进入休眠时序序
        seqTimes.insert(SeqFile::autoSleepExitSeqNo(), 10.0); // 退出休眠时序号
        seqTimes.insert(SeqFile::shutdownSeqNo(), 0x001C); // 关机清洗时序
        seqTimes.insert(SeqFile::backFlushSeqNo(), 0x0028); // 排堵时序号

#ifdef _WIN32
        return 3.0;
#else
        return seqTimes.value(seqNo, 30.0f);
#endif
    }

    // 时序试剂耗量（单位ml)
    float getSeqReagent(const QString& seqNo, int reagent)
    {
        if (REAGENT_LH == reagent)
        {
            QMap<QString, float> volumes;

            volumes.insert("Test_35_100_100", 105.0); // 计数时序
            volumes.insert("Test_35_100_120", 105.0); // 计数时序
            volumes.insert("Test_35_130_100", 105.0); // 计数时序
            volumes.insert("Test_35_130_120", 105.0); // 计数时序
            volumes.insert("Test_35_150_100", 105.0); // 计数时序
            volumes.insert("Test_35_150_120", 105.0); // 计数时序

            volumes.insert("Test_40_100_100", 90.0); // 计数时序
            volumes.insert("Test_40_100_120", 90.0); // 计数时序
            volumes.insert("Test_40_130_100", 90.0); // 计数时序
            volumes.insert("Test_40_130_120", 90.0); // 计数时序
            volumes.insert("Test_40_150_100", 90.0); // 计数时序
            volumes.insert("Test_40_150_120", 90.0); // 计数时序

            volumes.insert("Test_60_100_100", 64.0); // 计数时序
            volumes.insert("Test_60_100_120", 64.0); // 计数时序
            volumes.insert("Test_60_130_100", 64.0); // 计数时序
            volumes.insert("Test_60_130_120", 64.0); // 计数时序
            volumes.insert("Test_60_150_100", 64.0); // 计数时序
            volumes.insert("Test_60_150_120", 64.0); // 计数时序

            volumes.insert("Diluent_35_100_100", 100.0); // 计数时序
            volumes.insert("Diluent_35_100_120", 100.0); // 计数时序
            volumes.insert("Diluent_35_130_100", 100.0); // 计数时序
            volumes.insert("Diluent_35_130_120", 100.0); // 计数时序
            volumes.insert("Diluent_35_150_100", 100.0); // 计数时序
            volumes.insert("Diluent_35_150_120", 100.0); // 计数时序

            volumes.insert("Diluent_40_100_100", 90.0); // 计数时序
            volumes.insert("Diluent_40_100_120", 90.0); // 计数时序
            volumes.insert("Diluent_40_130_100", 90.0); // 计数时序
            volumes.insert("Diluent_40_130_120", 90.0); // 计数时序
            volumes.insert("Diluent_40_150_100", 90.0); // 计数时序
            volumes.insert("Diluent_40_150_120", 90.0); // 计数时序

            volumes.insert("Diluent_60_100_100", 72.0); // 计数时序
            volumes.insert("Diluent_60_100_120", 72.0); // 计数时序
            volumes.insert("Diluent_60_130_100", 72.0); // 计数时序
            volumes.insert("Diluent_60_130_120", 72.0); // 计数时序
            volumes.insert("Diluent_60_150_100", 72.0); // 计数时序
            volumes.insert("Diluent_60_150_120", 72.0); // 计数时序

            volumes.insert(SeqFile::initSeqNo(), 10.0); // 液路初始化时序号
            volumes.insert(SeqFile::lyseFillSeqNo(), 40.0); // 更换溶血剂时序号
            volumes.insert(SeqFile::diluentFillSeqNo(), 0x0023); // 更换稀释液时序号
            volumes.insert(SeqFile::wholeFillSeqNo(), 120.0); // 整机灌注时序号
            volumes.insert(SeqFile::enhancedFlushSeqNo(), 32.0); // 强力排堵时序号
            volumes.insert(SeqFile::enhancedCleanSeqNo(), 8.0); // 强力清洗时序号
            volumes.insert(SeqFile::emptyPoolSeqNo(), 11.0); // 排空计数池时序号
            volumes.insert(SeqFile::diluentInitSeqNo(), 10.0); // 加稀释液准备时序号
            volumes.insert(SeqFile::diluentFloodSeqNo(), 10.0); // 加稀释液时序号
            volumes.insert(SeqFile::cleanSeqNo(), 0x003B); // 清洗时序号
            volumes.insert(SeqFile::startingUpSeqNo(), 0x003C); // 开机清洗时序号
            volumes.insert(SeqFile::autoSleepEnterSeqNo(), 10.0); // 进入休眠时序序
            volumes.insert(SeqFile::autoSleepExitSeqNo(), 10.0); // 退出休眠时序号
            volumes.insert(SeqFile::shutdownSeqNo(), 0x001C); // 关机清洗时序
            volumes.insert(SeqFile::backFlushSeqNo(), 0x0028); // 排堵时序号

            return volumes.value(seqNo, 0);
        }
        else if (REAGENT_DT == reagent)
        {
            QMap<QString, float> volumes;

            volumes.insert("Test_35_100_100", 105.0); // 计数时序
            volumes.insert("Test_35_100_120", 105.0); // 计数时序
            volumes.insert("Test_35_130_100", 105.0); // 计数时序
            volumes.insert("Test_35_130_120", 105.0); // 计数时序
            volumes.insert("Test_35_150_100", 105.0); // 计数时序
            volumes.insert("Test_35_150_120", 105.0); // 计数时序

            volumes.insert("Test_40_100_100", 90.0); // 计数时序
            volumes.insert("Test_40_100_120", 90.0); // 计数时序
            volumes.insert("Test_40_130_100", 90.0); // 计数时序
            volumes.insert("Test_40_130_120", 90.0); // 计数时序
            volumes.insert("Test_40_150_100", 90.0); // 计数时序
            volumes.insert("Test_40_150_120", 90.0); // 计数时序

            volumes.insert("Test_60_100_100", 64.0); // 计数时序
            volumes.insert("Test_60_100_120", 64.0); // 计数时序
            volumes.insert("Test_60_130_100", 64.0); // 计数时序
            volumes.insert("Test_60_130_120", 64.0); // 计数时序
            volumes.insert("Test_60_150_100", 64.0); // 计数时序
            volumes.insert("Test_60_150_120", 64.0); // 计数时序

            volumes.insert("Diluent_35_100_100", 100.0); // 计数时序
            volumes.insert("Diluent_35_100_120", 100.0); // 计数时序
            volumes.insert("Diluent_35_130_100", 100.0); // 计数时序
            volumes.insert("Diluent_35_130_120", 100.0); // 计数时序
            volumes.insert("Diluent_35_150_100", 100.0); // 计数时序
            volumes.insert("Diluent_35_150_120", 100.0); // 计数时序

            volumes.insert("Diluent_40_100_100", 90.0); // 计数时序
            volumes.insert("Diluent_40_100_120", 90.0); // 计数时序
            volumes.insert("Diluent_40_130_100", 90.0); // 计数时序
            volumes.insert("Diluent_40_130_120", 90.0); // 计数时序
            volumes.insert("Diluent_40_150_100", 90.0); // 计数时序
            volumes.insert("Diluent_40_150_120", 90.0); // 计数时序

            volumes.insert("Diluent_60_100_100", 72.0); // 计数时序
            volumes.insert("Diluent_60_100_120", 72.0); // 计数时序
            volumes.insert("Diluent_60_130_100", 72.0); // 计数时序
            volumes.insert("Diluent_60_130_120", 72.0); // 计数时序
            volumes.insert("Diluent_60_150_100", 72.0); // 计数时序
            volumes.insert("Diluent_60_150_120", 72.0); // 计数时序

            volumes.insert(SeqFile::initSeqNo(), 10.0); // 液路初始化时序号
            volumes.insert(SeqFile::lyseFillSeqNo(), 40.0); // 更换溶血剂时序号
            volumes.insert(SeqFile::diluentFillSeqNo(), 0x0023); // 更换稀释液时序号
            volumes.insert(SeqFile::wholeFillSeqNo(), 120.0); // 整机灌注时序号
            volumes.insert(SeqFile::enhancedFlushSeqNo(), 32.0); // 强力排堵时序号
            volumes.insert(SeqFile::enhancedCleanSeqNo(), 8.0); // 强力清洗时序号
            volumes.insert(SeqFile::emptyPoolSeqNo(), 11.0); // 排空计数池时序号
            volumes.insert(SeqFile::diluentInitSeqNo(), 10.0); // 加稀释液准备时序号
            volumes.insert(SeqFile::diluentFloodSeqNo(), 10.0); // 加稀释液时序号
            volumes.insert(SeqFile::cleanSeqNo(), 0x003B); // 清洗时序号
            volumes.insert(SeqFile::startingUpSeqNo(), 0x003C); // 开机清洗时序号
            volumes.insert(SeqFile::autoSleepEnterSeqNo(), 10.0); // 进入休眠时序序
            volumes.insert(SeqFile::autoSleepExitSeqNo(), 10.0); // 退出休眠时序号
            volumes.insert(SeqFile::shutdownSeqNo(), 0x001C); // 关机清洗时序
            volumes.insert(SeqFile::backFlushSeqNo(), 0x0028); // 排堵时序号

            return volumes.value(seqNo, 0);
        }
        else
        {
            return 0;
        }
    }
}