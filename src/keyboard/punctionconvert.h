#ifndef _PUNCTION_CONVERT_H_
#define _PUNCTION_CONVERT_H_

#include <QString>

namespace PunctionConvert
{
    // ����Ƿ���ת��Ϊȫ�Ƿ��ţ��������뷨���棩
    bool convertToChinesePuncForPyInput(int srcPunc, QString& strDst);

    // ����Ƿ���ת��Ϊȫ�Ƿ��ţ�ȫ�Ƿ������뷨���棩
    bool convertToChinesePunc(int srcPunc, QString& strDst);
}

#endif //_PUNCTION_CONVERT_H_