#ifndef _SAMPLE_ID_H_
#define _SAMPLE_ID_H_


#include <QString>

#include "libcommon.h"


// �������
namespace SampleId
{
    // �����������
    COMMON_EXPORT QString background();

    // ��������Ƿ���Ч
    COMMON_EXPORT bool isValid(const QString& sampleId);

    // ��������Զ�����
    COMMON_EXPORT QString autoInc(const QString& sampleId);
};


#endif // _SAMPLE_ID_H_