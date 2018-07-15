#ifndef _LJ_QC_TABLE_WIDGET_H_
#define _LJ_QC_TABLE_WIDGET_H_


#include "tablewidget.h"

class LJQcSampleTable;


// LJ�ʿر��ؼ�
class LJQcTableWidget : public TableWidget
{
    Q_OBJECT

public:
    LJQcTableWidget(QWidget* parent = 0);
    virtual ~LJQcTableWidget();

    // ���õ�ǰҳ����
    void setSamples(const QList<int>& samples);

    // ������
    void setLJQcSampleTable(LJQcSampleTable* sampleTable);

protected:
    // ��ȡ��ͷ����
    virtual QStringList headText() const;

    // ��ȡ�������
    virtual int numOfItems();
    virtual QStringList columnText(int columnNo);

private:
    // ��ǰҳ����
    QList<int> samples;

    // ������
    LJQcSampleTable* sampleTable;
};


#endif // _LJ_QC_TABLE_WIDGET_H_