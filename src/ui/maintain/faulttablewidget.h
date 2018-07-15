#ifndef _FAULT_TABLE_WIDGET_H_
#define _FAULT_TABLE_WIDGET_H_


#include "para.h"
#include "tablewidget.h"


// ���ϱ��ؼ�
class FaultTableWidget : public TableWidget
{
    Q_OBJECT

public:
    FaultTableWidget(QWidget* parent = 0);
    virtual ~FaultTableWidget();

    // �����б�
    void setFaults(const QList<int>& faults);

protected:
    // ��ȡ��ͷ����
    virtual QStringList headText() const;

    // ��ȡ�������
    virtual int numOfItems();
    virtual QStringList rowText(int row) const;

private:
    // �����б�
    QList<int> faults;

    // ��������
    QStringList faultIds;
};


#endif // _FAULT_TABLE_WIDGET_H_