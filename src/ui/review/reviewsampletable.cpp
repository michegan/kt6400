#include <QtDebug>

#include "field.h"
#include "paras.h"
#include "reviewsampletable.h"


class ReviewSampleTablePrivate
{
public:
    ReviewSampleTablePrivate();
    ~ReviewSampleTablePrivate();

public:
    // 当前样本
    int currentIndex;

    // 全部样本
    QList<int> allSamples;
};

ReviewSampleTablePrivate::ReviewSampleTablePrivate()
    : currentIndex(INVALID_INDEX)
{

}

ReviewSampleTablePrivate::~ReviewSampleTablePrivate()
{

}


ReviewSampleTable::ReviewSampleTable()
    : AllSampleTable(), d(new ReviewSampleTablePrivate())
{
    // 默认查询全部样本
    this->selectSamples();
}

ReviewSampleTable::~ReviewSampleTable()
{
    delete this->d;
}

// 当前样本
int ReviewSampleTable::currentIndex() const
{
    return d->currentIndex;
}

void ReviewSampleTable::setCurrentIndex(int index)
{
    d->currentIndex = index;

    // 当前样本变化信号
    emit currentSampleChanged(index, d->allSamples);
}

// 全部样本
QList<int> ReviewSampleTable::allSamples() const
{
    return d->allSamples;
}

// 获取样本
int ReviewSampleTable::fid(int index) const
{
    return (0 <= index && index < d->allSamples.length() ? d->allSamples.at(index) : INVALID_FID);
}

// 查询
bool ReviewSampleTable::selectSamples()
{
    // 加载全部样本信息
    d->allSamples.clear();

    QSqlQuery sqlQuery = this->selectRecord();
    while (sqlQuery.next())
    {
        // 当前记录值
        QSqlRecord record = sqlQuery.record();

        // 用户信息
        int fid = record.value(F_ID).toInt();
        d->allSamples.append(fid);
    }

    // 默认当前样本和默认选中样本
    this->clearSelectedRecords();

    d->currentIndex = (d->allSamples.isEmpty() ? INVALID_INDEX : d->allSamples.length() - 1);


    emit dataChanged();

    return true;
}

// 获取样本
bool ReviewSampleTable::getSample(int fid, SampleInfo& sampleInfo, ParaList& paraResult)
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

bool ReviewSampleTable::getSample(int fid, HistInfo& wbcHist, HistInfo& rbcHist, HistInfo& pltHist)
{
    // 查询，检测有效样本数
    QSqlQuery query = this->selectRecord(fid);

    bool ret = query.next();
    if (ret)
    {
        // 当前记录值
        QSqlRecord record = query.record();

        // 直方图信息
        this->getHistInfo(wbcHist, rbcHist, pltHist, record);
    }

    return ret;
}

// 添加样本
bool ReviewSampleTable::addSample(int& fid, const SampleInfo& sampleInfo, const ParaList& paraResult)
{
    bool ret = AllSampleTable::addSample(fid, sampleInfo, paraResult);
    if (ret)
    {
        // 所有样本中追加此样本
        d->allSamples.append(fid);

        // 新增样本作为当前样本
        this->setCurrentIndex(d->allSamples.length() - 1);
    }

    return ret;
}

// 删除样本
bool ReviewSampleTable::deleteAllSamples()
{
    // 不带任何条件
    this->clearConditions();

    // 删除
    bool ret = this->deleteRecord();
    if (ret)
    {
        // 所有样本清空
        d->allSamples.clear();

        // 当前样本空
        this->setCurrentIndex(INVALID_INDEX);

        // 选中样本空
        this->clearSelectedRecords();
    }

    return ret;
}

bool ReviewSampleTable::deleteCurrentSample()
{
    bool ret = false;

    do 
    {
        // 当前样本索引
        int current = this->currentIndex();
        if (current < 0)
        {
            break;
        }

        // 当前样本FID
        int fid = this->fid(current);
        if (fid < 0)
        {
            break;
        }

        // 从数据库中删除样本
        ret = this->deleteRecord(fid);
        if (!ret)
        {
            break;
        }

        // 全部样本中删除此样本
        d->allSamples.removeOne(fid);

        // 选中样本中删除此样本
        QList<int> selectSamples = this->selectedRecords();
        if (selectSamples.contains(fid))
        {
            this->selectedRecord(fid, false);
        }

        // 更新当前样本
        if (current < d->allSamples.length())
        {
            // 删除的是中间样本，则当前位置继续不变
            current = current;
        }
        else if (d->currentIndex == d->allSamples.length())
        {
            // 删除的是最后一个样本，则新的最后一个样本作为当前样本
            current = d->allSamples.length() - 1;
        }
        else
        {
            current = INVALID_INDEX;
        }
        this->setCurrentIndex(current);
    } while (0);

    return ret;
}

bool ReviewSampleTable::deleteSelectSamples()
{
    // 缓存选中样本
    QList<int> selectSamples = this->selectedRecords();

    // 从数据库中删除样本
    bool ret = this->deleteSelectdRecords();
    if (ret)
    {
        // 确定新的当前样本
        int cfid = -1;
        for (int i = this->currentIndex(); i < d->allSamples.length(); i++)
        {
            int fid = d->allSamples.at(i);
            if (!selectSamples.contains(fid))
            {
                cfid = fid;
                break;
            }
        }
        if (cfid < 0)
        {
            for (int i = this->currentIndex(); i >= 0; i--)
            {
                int fid = d->allSamples.at(i);
                if (!selectSamples.contains(fid))
                {
                    cfid = fid;
                    break;
                }
            }
        }

        // 全部样本中删除选中样本
        foreach (int fid, selectSamples)
        {
            d->allSamples.removeOne(fid);
        }

        // 最后一个样本作为当前样本
        int current = (0 <= cfid ? d->allSamples.indexOf(cfid) : INVALID_INDEX);
        this->setCurrentIndex(current);
    }

    return ret;
}

// 单键
static ReviewSampleTable* s_sampleTable = 0;

void ReviewSampleTable::createInstance()
{
    s_sampleTable = new ReviewSampleTable();
}

ReviewSampleTable* ReviewSampleTable::instance()
{
    return s_sampleTable;
}