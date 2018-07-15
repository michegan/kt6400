#ifndef _REVIEW_SEARCH_DIALOG_H_
#define _REVIEW_SEARCH_DIALOG_H_


#include "dialog.h"
#include "ui_reviewsearchdialog.h"


// ��һ�����༭�Ի���
class ReviewSearchDialog : public Dialog
{
    Q_OBJECT

public:
    ReviewSearchDialog(QWidget* parent = 0);
    virtual ~ReviewSearchDialog();

    // ��ѯ����
    QString condition() const;

protected:
    // �����ַ���
    virtual void setWindowText();

private slots:
    // ��ť���
    virtual void onBtnAllClicked();
    virtual void onBtnSearchClicked();
    virtual void onBtnCancelClicked();

private:
    // ��ѯ����
    QString scondition;

    // �ͼ���
    QStringList senders;

    // ����
    Ui::ReviewSearchDialog ui;
};


#endif // _REVIEW_SEARCH_DIALOG_H_