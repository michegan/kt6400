#ifndef _MESSAGE_BOX_H_
#define _MESSAGE_BOX_H_


#include <QMessageBox>


// 消息框
namespace MessageBox
{
    // 提示（NONE）
    QMessageBox::StandardButton exclamation(QWidget* parent, const QString& text);
    QMessageBox::StandardButton exclamationIds(QWidget* parent, const QString& ids);

    // 提示（OK）
    QMessageBox::StandardButton information(QWidget* parent, const QString& text);
    QMessageBox::StandardButton informationIds(QWidget* parent, const QString& ids);

    // 询问（YES/NO）
    QMessageBox::StandardButton question(QWidget* parent, const QString& text);
    QMessageBox::StandardButton questionIds(QWidget* parent, const QString& ids);
 
    // 警告（OK）
    QMessageBox::StandardButton warning(QWidget* parent, const QString& text);
    QMessageBox::StandardButton warningIds(QWidget* parent, const QString& ids);
};


#endif // _MESSAGE_BOX_H_