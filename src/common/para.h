#ifndef _PARA_H_
#define _PARA_H_


#include <QList>
#include <QStringList>

#include "flag.h"
#include "libcommon.h"


// ����
class COMMON_EXPORT Para
{
public:
    Para();
    Para(const Para& other);
    Para(const QString& name);
    virtual ~Para();

    // ���÷�Χ
    void setLimit(float low, float high);

    // ���ò�����Ϣ�������ã�
    void setInfo(const QString& name, float value, int flag, const QString& unit);

    // ��ʽ��
    QString toString() const;
    QString flagToString() const;
    QString valueToString(int decimal) const;

    // ����
    bool hasFlag() const;

    // ���������
    operator int() const;

    Para& operator= (const Para& other);

    bool operator==(const Para& other) const;

public:
    // ��������
    QString name;

    // ֵ
    float value;

    // ����
    int flag;

    // ��λ
    QString unit;
};


// �����б�
class COMMON_EXPORT ParaList : public QList<Para>
{
public:
    ParaList();
    virtual ~ParaList();

    // ���
    void output();

    // ������������
    QStringList paraNames();

    // ��������
    int indexOfPara(const QString& name) const;

    // ���ݲ�����ȡ��Ӧ����
    Para para(const QString& name);
    const Para& para(const QString& name) const;

    // ���ݲ�������ȡ����
    int paraFlag(const QString& name) const;

    // ���ݲ�����ȡ��Ӧ����ֵ
    float paraValue(const QString& name) const;
    void setParaValue(const QString& name, float value);

    // ���÷�Χ
    void setLimits(const ParaList& lowLimits, const ParaList& highLimits);

    // ׷�Ӳ���
    void appendPara(const QString& name, float value);
    void appendPara(const QString& name, float value, int flag);
    void appendPara(const QString& name, float value, int flag, const QString& unit);
};


#endif // _PARA_H_