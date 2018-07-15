#ifndef _PARA_H_
#define _PARA_H_


#include <QList>
#include <QStringList>

#include "flag.h"
#include "libcommon.h"


// 参数
class COMMON_EXPORT Para
{
public:
    Para();
    Para(const Para& other);
    Para(const QString& name);
    virtual ~Para();

    // 设置范围
    void setLimit(float low, float high);

    // 设置参数信息（调试用）
    void setInfo(const QString& name, float value, int flag, const QString& unit);

    // 格式化
    QString toString() const;
    QString flagToString() const;
    QString valueToString(int decimal) const;

    // 报警
    bool hasFlag() const;

    // 运算符重载
    operator int() const;

    Para& operator= (const Para& other);

    bool operator==(const Para& other) const;

public:
    // 参数名称
    QString name;

    // 值
    float value;

    // 报警
    int flag;

    // 单位
    QString unit;
};


// 参数列表
class COMMON_EXPORT ParaList : public QList<Para>
{
public:
    ParaList();
    virtual ~ParaList();

    // 输出
    void output();

    // 参数名称链表
    QStringList paraNames();

    // 参数索引
    int indexOfPara(const QString& name) const;

    // 根据参数名取对应参数
    Para para(const QString& name);
    const Para& para(const QString& name) const;

    // 根据参数名称取报警
    int paraFlag(const QString& name) const;

    // 根据参数名取对应参数值
    float paraValue(const QString& name) const;
    void setParaValue(const QString& name, float value);

    // 设置范围
    void setLimits(const ParaList& lowLimits, const ParaList& highLimits);

    // 追加参数
    void appendPara(const QString& name, float value);
    void appendPara(const QString& name, float value, int flag);
    void appendPara(const QString& name, float value, int flag, const QString& unit);
};


#endif // _PARA_H_