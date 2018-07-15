#include "dialog.h"
#include "language.h"


Dialog::Dialog(QWidget* parent)
    : QDialog(parent, Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint)
{
    // http://www.qtcn.org/bbs/read-htm-tid-45344.html
    // ���qt���뷨 qinputcontent ��qdialog��û��Ӧ������
    // ��QT�����ֲ᣺
    // int QDialog::exec() [slot]
    // Shows the dialog as a modal dialog, blocking until the user closes it .The function returns a DialogCode result.
    // if the dialog is application modal,users cannot interact with any other window in the same applicatio until they close the dialog. 
    // if the dialog is window modal,only interaction with the parent window is blocked while the dialog is open. 
    // By default, the dialog is application modal.
    this->setWindowModality(Qt::WindowModal);
}

Dialog::~Dialog()
{

}

// �����ַ���
void Dialog::setWindowText()
{

}

// ����ʹ��
void Dialog::enableWindow(bool enable)
{

}

// �����ַ���
QString Dialog::getString(const QString& ids)
{
    return Language::getString(ids);
}

void Dialog::setText(QLabel* widget, const QString& ids)
{
    QString text = this->getString(ids);
    widget->setText(text);
}

void Dialog::setText(QLineEdit* widget, const QString& ids)
{
    QString text = this->getString(ids);
    widget->setText(text);
}

void Dialog::setText(QAbstractButton* widget, const QString& ids)
{
    QString text = this->getString(ids);
    widget->setText(text);
}

void Dialog::setItems(QComboBox* widget, const QString& ids, const QStringList& idses)
{
    // ���
    widget->clear();

    // ���ӱ�ѡ��
    for (int i = idses.length() - 1; i >= 0; i--)
    {
        widget->insertItem(0, this->getString(idses.at(i)));
    }

    // �趨��ǰѡ��
    widget->setCurrentIndex(idses.indexOf(ids));
}