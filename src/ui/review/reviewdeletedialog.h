#ifndef _REVIEW_DELETE_DIALOG_H_
#define _REVIEW_DELETE_DIALOG_H_


#include "dialog.h"
#include "ui_reviewdeletedialog.h"


// ��һ�����༭�Ի���
class ReviewDeleteDialog : public Dialog
{
    Q_OBJECT

public:
    ReviewDeleteDialog(QWidget* parent = 0);
    virtual ~ReviewDeleteDialog();

    // ѡ��
    bool isDeleteAll() const;

protected:
    // �����ַ���
    virtual void setWindowText();

private:
    // ����
    Ui::ReviewDeleteDialog ui;
};


#endif // _REVIEW_DELETE_DIALOG_H_