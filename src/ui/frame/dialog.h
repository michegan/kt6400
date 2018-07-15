#ifndef _DIALOG_H_
#define _DIALOG_H_


#include <QLabel>
#include <QDialog>
#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>


// �Ի���
class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget* parent = 0);
    virtual ~Dialog();

protected:
    // �����ַ���
    virtual void setWindowText();

    // ����ʹ��
    virtual void enableWindow(bool enable);

protected:
    // �����ַ���
    virtual QString getString(const QString& ids);

    virtual void setText(QLabel* widget, const QString& ids);
    virtual void setText(QLineEdit* widget, const QString& ids);
    virtual void setText(QAbstractButton* widget, const QString& ids);

    virtual void setItems(QComboBox* widget, const QString& ids, const QStringList& idses);
};


#endif // _DIALOG_H_