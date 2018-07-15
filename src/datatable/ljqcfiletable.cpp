#include <QtDebug>

#include "field.h"
#include "ljqcfiletable.h"


LJQcFileTable::LJQcFileTable()
    : SampleTable("T_LJQCFILE")
{

}

LJQcFileTable::~LJQcFileTable()
{

}

// 读取文件
bool LJQcFileTable::getFile(int fid, LJQcInfo& qcInfo, ParaList& lowLimits, ParaList& highLimits)
{
    // 查询，检测有效样本数
    QSqlQuery query = this->selectRecord(fid);

    bool ret = query.next();
    if (ret)
    {
        // 当前记录值
        QSqlRecord record = query.record();

        // 质控信息
        this->getLJQcInfo(qcInfo, record);
        // 参考范围下限
        this->getLowLimit(lowLimits, record);
        // 参考范围上限
        this->getHighLimit(highLimits, record);
    }

    return ret;
}

// 更新文件
bool LJQcFileTable::updateFile(int fid, const LJQcInfo& qcInfo, const ParaList& lowLimits, const ParaList& highLimits)
{
    bool ret = false;

    // 查询上述条件记录（只应该查询到1条记录）
    QSqlQuery query = this->selectRecord(fid);
    if (query.next())
    {
        // 更新需要更新的字段
        QSqlRecord record = query.record();

        this->setLJQcInfo(record, qcInfo);
        this->setLowLimit(record, lowLimits);
        this->setHighLimit(record, highLimits);

        // 执行对应SQL操作
        ret = this->updateRecord(record);
    }

    return ret;
}

// 清空文件
bool LJQcFileTable::clearFile(int fid)
{
    // 查询条件
    this->clearConditions();
    this->addAndCondition(F_ID, fid);

    // 删除
    return this->deleteRecord();
}