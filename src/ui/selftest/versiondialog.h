#ifndef _VERSION_DIALOG_H_
#define _VERSION_DIALOG_H_


#include "dialog.h"
#include "ui_versiondialog.h"


// ģʽ�༭�Ի���
class VersionDialog : public Dialog
{
    Q_OBJECT

public:
    VersionDialog(QWidget* parent = 0);
    virtual ~VersionDialog();

protected:
    // �����ַ���
    virtual void setWindowText();

private:
    // ���ذ汾��Ϣ
    void loadVersionInfo();

private:
    // ����
    Ui::VersionDialog ui;
};


#endif // _VERSION_DIALOG_H_