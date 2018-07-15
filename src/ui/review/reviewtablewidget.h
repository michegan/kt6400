#ifndef _REVIEW_TABLE_WIDGET_H_
#define _REVIEW_TABLE_WIDGET_H_


#include "tablewidget.h"

class ReviewSampleTable;


// �ع˱��ؼ�
class ReviewTableWidget : public TableWidget
{
    Q_OBJECT

public:
    ReviewTableWidget(QWidget* parent = 0);
    virtual ~ReviewTableWidget();

    // ������ʼ����
    void setFrom(int from);

    // ���õ�ǰҳ����
    void setSamples(const QList<int>& samples);

    // ������
    void setReviewSampleTable(ReviewSampleTable* sampleTable);

protected:
    // ѡ��ģʽ��Ĭ�ϵ�ѡ��
    bool isSingleSelect() const;

    // ��ȡ��ͷ����
    virtual QStringList headText() const;

    // ��ȡ�������
    virtual int numOfItems();
    virtual QStringList columnText(int column);

private:
    // ��ʼ����
    int from;

    // ��ǰҳ����
    QList<int> samples;

    // ������
    ReviewSampleTable* sampleTable;
};


#endif // _REVIEW_TABLE_WIDGET_H_