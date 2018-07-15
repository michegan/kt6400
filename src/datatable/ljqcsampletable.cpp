#include <QtDebug>

#include "field.h"
#include "paras.h"
#include "ljqcsampletable.h"


LJQcSampleTable::LJQcSampleTable(int fileNo)
    : SampleTable("T_LJQCSAMPLE")
{
    this->fileNo = fileNo;
}

LJQcSampleTable::~LJQcSampleTable()
{

}

// 记录数
int LJQcSampleTable::numOfRecords()
{
    // 查询条件
    this->clearConditions();
    this->addAndCondition(F_FILENO, this->fileNo);

    // 记录数
    return SampleTable::numOfRecords();
}

// 全部样本
QList<int> LJQcSampleTable::allSamples()
{
    // 全部样本
    QList<int> allSamples;

    // 查询条件
    this->clearConditions();
    this->addAndCondition(F_FILENO, this->fileNo);

    // 加载全部样本信息
    QSqlQuery sqlQuery = this->selectRecord();
    while (sqlQuery.next())
    {
        // 当前记录值
        QSqlRecord record = sqlQuery.record();

        // 用户信息
        int fid = record.value(F_SID).toInt();
        allSamples.append(fid);
    }

    return allSamples;
}

// 获取样本
bool LJQcSampleTable::getSample(int fid, SampleInfo& sampleInfo, ParaList& paraResult)
{
    // 查询，检测有效样本数
    QSqlQuery query = this->selectRecord(fid);

    bool ret = query.next();
    if (ret)
    {
        // 当前记录值
        QSqlRecord record = query.record();

        // 样本信息
        this->getSampleInfo(sampleInfo, record);
        // 参数结果
        this->getParaResult(paraResult, record);
    }

    return ret;
}

// 添加样本
bool LJQcSampleTable::addSample(int& fid, const QDateTime& testTime, const ParaList& paraResult)
{
    bool ret = false;

    do 
    {
        // 下一F_ID
        int nid = this->nextFid();
        if (nid <= 0)
        {
            break;
        }

        // 表对应记录
        QSqlRecord record = this->record();
        record.clearValues();

        // 更新需要更新的字段
        record.setValue(F_ID, nid);
        record.setValue(F_FILENO, this->fileNo);
        record.setValue(F_TEST_TIME, testTime);
        this->setParaResult(record, paraResult);

        // 执行对应SQL操作
        if (!this->insertRecord(record))
        {
            break;
        }

        ret = true;
        fid = nid;
    } while (0);

    return ret;
}

// 删除样本
bool LJQcSampleTable::deleteAllSamples()
{
    // 查询条件
    this->clearConditions();
    this->addAndCondition(F_FILENO, this->fileNo);

    // 删除记录
    return this->deleteRecord();
}

bool LJQcSampleTable::deleteSelectSamples()
{
    return this->deleteSelectdRecords();
}