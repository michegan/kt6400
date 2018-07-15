#ifndef _HIST_EDIT_DIALOG_H_
#define _HIST_EDIT_DIALOG_H_


#include "dialog.h"
#include "histwidget.h"
#include "ui_histeditdialog.h"


// ģʽ�༭�Ի���
class HistEditDialog : public Dialog
{
    Q_OBJECT

public:
    HistEditDialog(QWidget* parent = 0);
    virtual ~HistEditDialog();


private slots:
    // ��ť���
    virtual void onBtnOkClicked();
    virtual void onBtnCancelClicked();

private:
    // ����
    Ui::HistEditDialog ui;

    // ֱ��ͼ�ؼ�
    WbcHistWidget* wbcHistWidget;
    RbcHistWidget* rbcHistWidget;
    PltHistWidget* pltHistWidget;
};


#endif // _HIST_EDIT_DIALOG_H_