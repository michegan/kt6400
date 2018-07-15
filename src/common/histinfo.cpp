#include <QList>
#include <QtDebug>
#include <string.h>

#include "histinfo.h"


HistInfo::HistInfo()
    : lineLen(0), dataLen(0)
{
    // 分类线
    memset(lines, 0, sizeof(lines));

    // 直方图数据
    memset(datas, 0, sizeof(datas));
}

HistInfo::HistInfo(const HistInfo& other)
{
    // 分类线
    lineLen = other.lineLen;
    memcpy(lines, other.lines, sizeof(lines));

    // 直方图数据
    dataLen = other.dataLen;
    memcpy(datas, other.datas, sizeof(datas));
}

HistInfo::~HistInfo()
{

}

// 初始化
void HistInfo::clear()
{
    // 分类线
    lineLen = 0;
    memset(lines, 0, sizeof(lines));

    // 直方图数据
    dataLen = 0;
    memset(datas, 0, sizeof(datas));
}

// 输出
void HistInfo::output()
{
    qDebug() << "HistInfo output lineLen" << this->lineLen;
    for (int i = 0; i < this->lineLen; i++)
    {
        qDebug() << "HistInfo output line" << i << this->lines[i];
    }

    qDebug() << "HistInfo output dataLen" << this->dataLen;
}

// 运算符重载
HistInfo& HistInfo::operator=(const HistInfo& other)
{
    // 分类线
    lineLen = other.lineLen;
    memcpy(lines, other.lines, sizeof(lines));

    // 直方图数据
    dataLen = other.dataLen;
    memcpy(datas, other.datas, sizeof(datas));

    return *this;
}


WbcHistInfo::WbcHistInfo()
    : HistInfo()
{
    // 直方图
    QList<int> ldatas;
    ldatas << 0 << 0 << 0 << 1 << 3 << 5 << 7 << 9 << 11 << 11 << 10 << 9 << 7 << 5 << 4 << 3 << 2 << 2 << 2 << 2 << 3 << 4 << 5 << 8 
        << 15 << 26 << 44 << 70 << 104 << 144 << 186 << 227 << 259 << 280 << 286 << 279 << 260 << 231 << 201 << 170 << 143 << 119 
        << 100 << 86 << 74 << 65 << 57 << 51 << 46 << 40 << 35 << 30 << 26 << 22 << 19 << 17 << 15 << 13 << 12 << 10 << 8 << 7 << 5 
        << 4 << 3 << 2 << 1 << 1 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 
        << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 
        << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 
        << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 
        << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 
        << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 
        << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 
        << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0;

    for (int i = 0; i < ldatas.length(); i++)
    {
        this->datas[i] = ldatas.at(i);
    }
    this->dataLen = ldatas.length();

    // 分类线
    this->lines[0] = 50;
    this->lines[1] = 100;
    this->lineLen = 2;
}

WbcHistInfo::~WbcHistInfo()
{

}


RbcHistInfo::RbcHistInfo()
    : HistInfo()
{
    // 直方图
    QList<int> ldatas;
    ldatas << 0 << 0 << 0 << 1 << 1 << 5 << 9 << 17 << 26 << 33 << 40 << 43 << 43 << 40 << 35 << 31 << 25 << 22 << 18 << 16 << 14 << 13 << 13 << 11 << 10 << 10 
        << 9 << 8 << 6 << 5 << 5 << 3 << 3 << 3 << 2 << 2 << 1 << 1 << 1 << 1 << 1 << 1 << 1 << 1 << 1 << 1 << 2 << 2 << 2 << 2 << 2 << 2 << 2 << 2 << 2 << 3 
        << 4 << 6 << 8 << 11 << 13 << 16 << 20 << 26 << 32 << 39 << 48 << 58 << 71 << 82 << 98 << 117 << 137 << 158 << 180 << 208 << 237 << 268 << 307 << 347 
        << 390 << 431 << 468 << 513 << 555 << 592 << 622 << 654 << 672 << 684 << 696 << 714 << 732 << 743 << 758 << 754 << 744 << 735 << 721 << 703 << 681 
        << 652 << 624 << 587 << 543 << 506 << 470 << 438 << 403 << 369 << 343 << 310 << 279 << 248 << 219 << 196 << 166 << 151 << 135 << 121 << 105 << 90 
        << 78 << 64 << 52 << 44 << 37 << 33 << 27 << 23 << 21 << 18 << 16 << 14 << 13 << 11 << 10 << 9 << 8 << 7 << 7 << 7 << 6 << 6 << 6 << 5 << 5 << 4 << 4 
        << 3 << 3 << 4 << 3 << 4 << 4 << 5 << 6 << 6 << 7 << 7 << 7 << 7 << 7 << 7 << 6 << 6 << 5 << 5 << 4 << 4 << 3 << 3 << 3 << 4 << 4 << 4 << 5 << 5 << 5 
        << 4 << 5 << 5 << 5 << 6 << 7 << 7 << 7 << 7 << 7 << 6 << 6 << 6 << 6 << 6 << 5 << 4 << 5 << 4 << 4 << 3 << 3 << 4 << 4 << 5 << 5 << 5 << 4 << 4 << 4 
        << 4 << 4 << 4 << 4 << 3 << 3 << 3 << 2 << 3 << 2 << 3 << 2 << 2 << 2 << 1 << 1 << 1 << 1 << 1 << 1 << 1 << 1 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 
        << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 1 << 1 << 1 << 0 << 0 << 0 << 0 << 0;

    for (int i = 0; i < ldatas.length(); i++)
    {
        this->datas[i] = ldatas.at(i);
    }
    this->dataLen = ldatas.length();

    // 分类线
    this->lines[0] = 30;
    this->lines[1] = 80;
    this->lineLen = 2;
}

RbcHistInfo::~RbcHistInfo()
{

}


PltHistInfo::PltHistInfo()
    : HistInfo()
{
    // 直方图
    QList<int> ldatas;
    ldatas << 0 << 1 << 5 << 11 << 19 << 26 << 30 << 33 << 35 << 39 << 44 << 50 << 55 << 61 << 65 << 70 << 76 << 80 << 82 << 81 << 80 << 80 
        << 80 << 80 << 76 << 73 << 68 << 66 << 64 << 63 << 60 << 57 << 52 << 48 << 45 << 42 << 40 << 37 << 33 << 29 << 26 << 25 << 24 
        << 23 << 21 << 19 << 17 << 16 << 16 << 15 << 15 << 15 << 16 << 15 << 14 << 12 << 10 << 8 << 7 << 6 << 6 << 7 << 6 << 0;

    for (int i = 0; i < ldatas.length(); i++)
    {
        this->datas[i] = ldatas.at(i);
    }
    this->dataLen = ldatas.length();

    // 分类线
    this->lines[0] = 8;
    this->lines[1] = 24;
    this->lineLen = 2;
}

PltHistInfo::~PltHistInfo()
{

}