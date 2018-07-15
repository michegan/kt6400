#ifndef _MESSAGE_BOX_H_
#define _MESSAGE_BOX_H_


#include <QMessageBox>


// ��Ϣ��
namespace MessageBox
{
    // ��ʾ��NONE��
    QMessageBox::StandardButton exclamation(QWidget* parent, const QString& text);
    QMessageBox::StandardButton exclamationIds(QWidget* parent, const QString& ids);

    // ��ʾ��OK��
    QMessageBox::StandardButton information(QWidget* parent, const QString& text);
    QMessageBox::StandardButton informationIds(QWidget* parent, const QString& ids);

    // ѯ�ʣ�YES/NO��
    QMessageBox::StandardButton question(QWidget* parent, const QString& text);
    QMessageBox::StandardButton questionIds(QWidget* parent, const QString& ids);
 
    // ���棨OK��
    QMessageBox::StandardButton warning(QWidget* parent, const QString& text);
    QMessageBox::StandardButton warningIds(QWidget* parent, const QString& ids);
};


#endif // _MESSAGE_BOX_H_