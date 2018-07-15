#ifndef _SEQ_NO_H_
#define _SEQ_NO_H_


#include <QString>

#include "libcommon.h"


class Modes;


// 时序文件
namespace SeqFile
{
    // 液路初始化时序号
    COMMON_EXPORT QString initSeqNo();

    // 开机清洗时序号
    COMMON_EXPORT QString startingUpSeqNo();

    // 关机清洗时序
    COMMON_EXPORT QString shutdownSeqNo();

    // 进入休眠时序序
    COMMON_EXPORT QString autoSleepEnterSeqNo();
    // 退出休眠时序号
    COMMON_EXPORT QString autoSleepExitSeqNo();

    // 更换溶血剂时序号
    COMMON_EXPORT QString lyseFillSeqNo();
    // 更换稀释液时序号
    COMMON_EXPORT QString diluentFillSeqNo();

    // 排堵时序号
    COMMON_EXPORT QString backFlushSeqNo();
    // 强力排堵时序号
    COMMON_EXPORT QString enhancedFlushSeqNo();

    // 清洗时序号
    COMMON_EXPORT QString cleanSeqNo();
    // 强力清洗时序号
    COMMON_EXPORT QString enhancedCleanSeqNo();

    // 整机灌注时序号
    COMMON_EXPORT QString wholeFillSeqNo();

    // 排空计数池时序号
    COMMON_EXPORT QString emptyPoolSeqNo();

    // 加稀释液准备时序号
    COMMON_EXPORT QString diluentInitSeqNo();
    // 加稀释液时序号
    COMMON_EXPORT QString diluentFloodSeqNo();

    // 计数时序号
    COMMON_EXPORT QString countSeqNo(const Modes& modes, int speed, int diluent, int lyse);

    // 时序时间
    COMMON_EXPORT float getSeqTime(const QString& seqNo);

    // 时序试剂耗量（单位ml)
    COMMON_EXPORT float getSeqReagent(const QString& seqNo, int reagent);
};


#endif // _SEQ_NO_H_