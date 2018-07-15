#include <QtDebug>

#include "field.h"
#include "nextsampletable.h"


// F_ID值
#define F_ID_V                      (1)


NextSampleTable::NextSampleTable()
    : SampleTable("T_NEXTSAMPLE")
{

}

NextSampleTable::~NextSampleTable()
{

}

// 获取下一样本信息
bool NextSampleTable::nextSampleInfo(SampleInfo& sampleInfo)
{
    bool ret = false;

    // 查询上述条件记录（只应该查询到1条记录）
    QSqlQuery query = this->selectRecord(F_ID_V);
    if (query.next())
    {
        // 提取所需要的字段
        QSqlRecord record = query.record();
        this->getSampleInfo(sampleInfo, record);

        ret = true;
    }

    return ret;
}

// 更新下一样本信息
bool NextSampleTable::setNextSampleInfo(const SampleInfo& sampleInfo)
{
    bool ret = false;

    // 查询上述条件记录（只应该查询到1条记录）
    QSqlQuery query = this->selectRecord(F_ID_V);
    if (query.next())
    {
        // 更新需要更新的字段
        QSqlRecord record = query.record();
        this->setSampleInfo(record, sampleInfo);

        // 执行对应SQL操作
        ret = this->updateRecord(record);
    }

    return ret;
}