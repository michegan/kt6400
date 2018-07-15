#ifndef _CALIBRATE_TABLE_WIDGET_H_
#define _CALIBRATE_TABLE_WIDGET_H_


#include "para.h"
#include "tablewidget.h"


// У׼���ؼ�
class CalibrateTableWidget : public TableWidget
{
    Q_OBJECT

public:
    CalibrateTableWidget(QWidget* parent = 0);
    virtual ~CalibrateTableWidget();

    // �������
    void setContent(const QList<ParaList>& contents);

protected:
    // ��ȡ��ͷ����
    virtual QStringList headText() const;

    // ��ȡ�������
    virtual int numOfItems();
    virtual QStringList rowText(int row) const;

private:
    // У׼����
    QStringList paraNames;

    // ������ͷ
    QStringList vHeadText;

    // �������
    QList<ParaList> contents;
};


#endif // _CALIBRATE_TABLE_WIDGET_H_