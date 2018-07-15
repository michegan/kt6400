#include <QtDebug>
#include <QMultiHash>

#include "flag.h"
#include "para.h"


Para::Para()
    : name(""), value(0), flag(PARA_IGNORE_FLAG)
{

}

Para::Para(const Para& other)
    : name(""), value(0), flag(PARA_IGNORE_FLAG), unit("")
{
    this->name = other.name;
    this->value = other.value;
    this->flag = other.flag;
    this->unit = other.unit;
}

Para::Para(const QString& name)
    : name(""), value(0), flag(PARA_IGNORE_FLAG), unit("")
{
    this->name = name;
}

Para::~Para()
{

}

// 设置范围
void Para::setLimit(float low, float high)
{
    if (PARA_NORMAL_FLAG == this->flag)
    {
        if (this->value < low)
        {
            this->flag = PARA_L_FLAG;
        }
        else if (high < this->value)
        {
            this->flag = PARA_H_FLAG;
        }
    }
}

// 设置参数信息（调试用）
void Para::setInfo(const QString& name, float value, int flag, const QString& unit)
{
    this->name = name;
    this->value = value;
    this->flag = flag;
    this->unit = unit;
}

// 格式化
QString Para::toString() const
{
    return QString("%1 : %2 : %3").arg(this->name).arg(this->value).arg(this->flag);
}

QString Para::flagToString() const
{
    if (PARA_H_FLAG == this->flag)
    {
        return QChar(0x2191);
    }
    else if (PARA_L_FLAG == this->flag)
    {
        return QChar(0x2193);
    }
    else if (PARA_DOULT_FLAG == this->flag)
    {
        return "R";
    }
    else
    {
        return "";
    }
}

QString Para::valueToString(int decimal) const
{
    if (PARA_STAR_FLAG == this->flag)
    {
        return "***.**";
    }
    else if (PARA_IGNORE_FLAG == this->flag)
    {
        return "";
    }
    else
    {
        return QString::number(this->value, 'f', decimal);
    }
}

// 报警
bool Para::hasFlag() const
{
    return (PARA_NORMAL_FLAG != this->flag && PARA_IGNORE_FLAG != this->flag);
}

// 运算符重载
Para::operator int() const
{
    return this->value;
}

Para& Para::operator=(const Para& other)
{
    this->name = other.name;
    this->value = other.value;
    this->flag = other.flag;
    this->unit = unit;

    return *this;
}

bool Para::operator==(const Para& other) const
{
    return (this->name == other.name && this->value == other.value && this->flag == other.flag);
}


ParaList::ParaList()
{

}

ParaList::~ParaList()
{

}

// 输出
void ParaList::output()
{
    QStringList names;
    for (int i = 0; i < this->size(); i++)
    {
        const Para& para = at(i);
        qDebug() << para.toString();
    }
}

// 参数名称链表
QStringList ParaList::paraNames()
{
    QStringList names;
    for (int i = 0; i < this->size(); i++)
    {
        const Para& para = at(i);
        names.append(para.name);
    }
    return names;
}

// 参数索引
int ParaList::indexOfPara(const QString& name) const
{
    for (int i = 0; i < size(); i++)
    {
        const Para& para = at(i);
        if (name == para.name)
        {
            return i;
        }
    }
    return -1;
}

// 根据参数名取对应参数
Para ParaList::para(const QString& name)
{
    for (int i = 0; i < size(); i++)
    {
        const Para& para = at(i);
        if (name == para.name)
        {
            return para;
        }
    }

    return Para();
}

const Para& ParaList::para(const QString& name) const
{
    int index = indexOfPara(name);
    return this->at(index);
}

// 根据参数名称取报警
int ParaList::paraFlag(const QString& name) const
{
    for (int i = 0; i < size(); i++)
    {
        const Para& para = at(i);
        if (0 == name.compare(para.name, Qt::CaseInsensitive))
        {
            return para.flag;
        }
    }
    return PARA_NORMAL_FLAG;
}

// 根据参数名取对应参数值
float ParaList::paraValue(const QString& name) const
{
    for (int i = 0; i < size(); i++)
    {
        const Para& para = at(i);
        if (0 == name.compare(para.name, Qt::CaseInsensitive))
        {
            return para.value;
        }
    }

    return 0.0;
}

void ParaList::setParaValue(const QString& name, float value)
{
    for (int i = 0; i < size(); i++)
    {
        Para& para = (*this)[i];
        if (0 == name.compare(para.name, Qt::CaseInsensitive))
        {
            para.value = value;
        }
    }
}

// 设置范围
void ParaList::setLimits(const ParaList& lowLimits, const ParaList& highLimits)
{
    for (int i = 0; i < size(); i++)
    {
        Para& para = (*this)[i];
        
        float low = lowLimits.paraValue(para.name);
        float high = highLimits.paraValue(para.name);

        para.setLimit(low, high);
    }
}

// 追加参数
void ParaList::appendPara(const QString& name, float value)
{
    this->appendPara(name, value, PARA_NORMAL_FLAG);
}

void ParaList::appendPara(const QString& name, float value, int flag)
{
    this->appendPara(name, value, flag, "");
}

void ParaList::appendPara(const QString& name, float value, int flag, const QString& unit)
{
    Para para;
    para.setInfo(name, value, flag, unit);
    this->append(para);
}