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
    // ��ǰ����
    int currentIndex;

    // ȫ������
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
    // Ĭ�ϲ�ѯȫ������
    this->selectSamples();
}

ReviewSampleTable::~ReviewSampleTable()
{
    delete this->d;
}

// ��ǰ����
int ReviewSampleTable::currentIndex() const
{
    return d->currentIndex;
}

void ReviewSampleTable::setCurrentIndex(int index)
{
    d->currentIndex = index;

    // ��ǰ�����仯�ź�
    emit currentSampleChanged(index, d->allSamples);
}

// ȫ������
QList<int> ReviewSampleTable::allSamples() const
{
    return d->allSamples;
}

// ��ȡ����
int ReviewSampleTable::fid(int index) const
{
    return (0 <= index && index < d->allSamples.length() ? d->allSamples.at(index) : INVALID_FID);
}

// ��ѯ
bool ReviewSampleTable::selectSamples()
{
    // ����ȫ��������Ϣ
    d->allSamples.clear();

    QSqlQuery sqlQuery = this->selectRecord();
    while (sqlQuery.next())
    {
        // ��ǰ��¼ֵ
        QSqlRecord record = sqlQuery.record();

        // �û���Ϣ
        int fid = record.value(F_ID).toInt();
        d->allSamples.append(fid);
    }

    // Ĭ�ϵ�ǰ������Ĭ��ѡ������
    this->clearSelectedRecords();

    d->currentIndex = (d->allSamples.isEmpty() ? INVALID_INDEX : d->allSamples.length() - 1);


    emit dataChanged();

    return true;
}

// ��ȡ����
bool ReviewSampleTable::getSample(int fid, SampleInfo& sampleInfo, ParaList& paraResult)
{
    // ��ѯ�������Ч������
    QSqlQuery query = this->selectRecord(fid);

    bool ret = query.next();
    if (ret)
    {
        // ��ǰ��¼ֵ
        QSqlRecord record = query.record();

        // ������Ϣ
        this->getSampleInfo(sampleInfo, record);
        // �������
        this->getParaResult(paraResult, record);
    }

    return ret;
}

bool ReviewSampleTable::getSample(int fid, HistInfo& wbcHist, HistInfo& rbcHist, HistInfo& pltHist)
{
    // ��ѯ�������Ч������
    QSqlQuery query = this->selectRecord(fid);

    bool ret = query.next();
    if (ret)
    {
        // ��ǰ��¼ֵ
        QSqlRecord record = query.record();

        // ֱ��ͼ��Ϣ
        this->getHistInfo(wbcHist, rbcHist, pltHist, record);
    }

    return ret;
}

// �������
bool ReviewSampleTable::addSample(int& fid, const SampleInfo& sampleInfo, const ParaList& paraResult)
{
    bool ret = AllSampleTable::addSample(fid, sampleInfo, paraResult);
    if (ret)
    {
        // ����������׷�Ӵ�����
        d->allSamples.append(fid);

        // ����������Ϊ��ǰ����
        this->setCurrentIndex(d->allSamples.length() - 1);
    }

    return ret;
}

// ɾ������
bool ReviewSampleTable::deleteAllSamples()
{
    // �����κ�����
    this->clearConditions();

    // ɾ��
    bool ret = this->deleteRecord();
    if (ret)
    {
        // �����������
        d->allSamples.clear();

        // ��ǰ������
        this->setCurrentIndex(INVALID_INDEX);

        // ѡ��������
        this->clearSelectedRecords();
    }

    return ret;
}

bool ReviewSampleTable::deleteCurrentSample()
{
    bool ret = false;

    do 
    {
        // ��ǰ��������
        int current = this->currentIndex();
        if (current < 0)
        {
            break;
        }

        // ��ǰ����FID
        int fid = this->fid(current);
        if (fid < 0)
        {
            break;
        }

        // �����ݿ���ɾ������
        ret = this->deleteRecord(fid);
        if (!ret)
        {
            break;
        }

        // ȫ��������ɾ��������
        d->allSamples.removeOne(fid);

        // ѡ��������ɾ��������
        QList<int> selectSamples = this->selectedRecords();
        if (selectSamples.contains(fid))
        {
            this->selectedRecord(fid, false);
        }

        // ���µ�ǰ����
        if (current < d->allSamples.length())
        {
            // ɾ�������м���������ǰλ�ü�������
            current = current;
        }
        else if (d->currentIndex == d->allSamples.length())
        {
            // ɾ���������һ�����������µ����һ��������Ϊ��ǰ����
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
    // ����ѡ������
    QList<int> selectSamples = this->selectedRecords();

    // �����ݿ���ɾ������
    bool ret = this->deleteSelectdRecords();
    if (ret)
    {
        // ȷ���µĵ�ǰ����
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

        // ȫ��������ɾ��ѡ������
        foreach (int fid, selectSamples)
        {
            d->allSamples.removeOne(fid);
        }

        // ���һ��������Ϊ��ǰ����
        int current = (0 <= cfid ? d->allSamples.indexOf(cfid) : INVALID_INDEX);
        this->setCurrentIndex(current);
    }

    return ret;
}

// ����
static ReviewSampleTable* s_sampleTable = 0;

void ReviewSampleTable::createInstance()
{
    s_sampleTable = new ReviewSampleTable();
}

ReviewSampleTable* ReviewSampleTable::instance()
{
    return s_sampleTable;
}