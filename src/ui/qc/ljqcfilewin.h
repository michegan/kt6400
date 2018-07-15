#ifndef _LJ_QC_FILE_WIN_
#define _LJ_QC_FILE_WIN_


#include "funcwin.h"

#include "ui_ljqcfilewin.h"

class LJQcFileTable;
class LJQcFileTableWidget;


// LJ�ʿ��ļ�����
class LJQcFileWin : public FuncWin
{
    Q_OBJECT

public:
    LJQcFileWin(QWidget* parent = 0);
    virtual ~LJQcFileWin();

private slots:
    // ��ť���
    void onBtnListClicked();
    void onBtnGraphClicked();
    void onBtnSetupClicked();

    // ��ѡ��
    void onTableWidgetRowClicked(int row, bool selected);

private:    
    // �ʿ���Ϣ��
    Ui::LJQcFileWin ui;

    // �ļ���
    LJQcFileTable* fileTable;

    // �ļ����
    LJQcFileTableWidget* tableWidget;
};


#endif // _LJ_QC_FILE_WIN_
