#ifndef _PARAS_H_
#define _PARAS_H_


#include <QStringList>

#include "libcommon.h"


// ��Ŀ����
namespace Paras
{
    // �����ʿز���
    COMMON_EXPORT QStringList qcParaNames();

    // ����У׼����
    COMMON_EXPORT QStringList calibrateParaNames();

    // ����ģʽ��Ӧ�����б������
    COMMON_EXPORT QStringList reportParaNames();

    COMMON_EXPORT QStringList wbcReportParaNames();
    COMMON_EXPORT QStringList rbcReportParaNames();
    COMMON_EXPORT QStringList pltReportParaNames();

    // ��������
    COMMON_EXPORT QString paraIds(const QString& paraName);
};


#endif // _PARAS_H_