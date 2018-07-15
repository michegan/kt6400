#ifndef _SEQ_NO_H_
#define _SEQ_NO_H_


#include <QString>

#include "libcommon.h"


class Modes;


// ʱ���ļ�
namespace SeqFile
{
    // Һ·��ʼ��ʱ���
    COMMON_EXPORT QString initSeqNo();

    // ������ϴʱ���
    COMMON_EXPORT QString startingUpSeqNo();

    // �ػ���ϴʱ��
    COMMON_EXPORT QString shutdownSeqNo();

    // ��������ʱ����
    COMMON_EXPORT QString autoSleepEnterSeqNo();
    // �˳�����ʱ���
    COMMON_EXPORT QString autoSleepExitSeqNo();

    // ������Ѫ��ʱ���
    COMMON_EXPORT QString lyseFillSeqNo();
    // ����ϡ��Һʱ���
    COMMON_EXPORT QString diluentFillSeqNo();

    // �Ŷ�ʱ���
    COMMON_EXPORT QString backFlushSeqNo();
    // ǿ���Ŷ�ʱ���
    COMMON_EXPORT QString enhancedFlushSeqNo();

    // ��ϴʱ���
    COMMON_EXPORT QString cleanSeqNo();
    // ǿ����ϴʱ���
    COMMON_EXPORT QString enhancedCleanSeqNo();

    // ������עʱ���
    COMMON_EXPORT QString wholeFillSeqNo();

    // �ſռ�����ʱ���
    COMMON_EXPORT QString emptyPoolSeqNo();

    // ��ϡ��Һ׼��ʱ���
    COMMON_EXPORT QString diluentInitSeqNo();
    // ��ϡ��Һʱ���
    COMMON_EXPORT QString diluentFloodSeqNo();

    // ����ʱ���
    COMMON_EXPORT QString countSeqNo(const Modes& modes, int speed, int diluent, int lyse);

    // ʱ��ʱ��
    COMMON_EXPORT float getSeqTime(const QString& seqNo);

    // ʱ���Լ���������λml)
    COMMON_EXPORT float getSeqReagent(const QString& seqNo, int reagent);
};


#endif // _SEQ_NO_H_