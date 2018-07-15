#ifndef _LJ_QC_FILE_TABLE_WIDGET_H_
#define _LJ_QC_FILE_TABLE_WIDGET_H_


#include "tablewidget.h"

class LJQcFileTable;
class LJQcSampleTable;


// LJ�ʿ��ļ����ؼ�
class LJQcFileTableWidget : public TableWidget
{
    Q_OBJECT

public:
    LJQcFileTableWidget(QWidget* parent = 0);
    virtual ~LJQcFileTableWidget();

    // �ļ���
    void setLJQcFileTable(LJQcFileTable* fileTable);

protected:
    // ��ȡ��ͷ����
    virtual QStringList headText() const;

    // ��ȡ�������
    virtual int numOfItems();
    virtual QStringList rowText(int row) const;

private:
    // �ļ���
    LJQcFileTable* fileTable;
};


#endif // _LJ_QC_FILE_TABLE_WIDGET_H_