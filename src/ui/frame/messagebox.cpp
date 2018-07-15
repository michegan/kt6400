#include "language.h"
#include "messagebox.h"
#include "msgboxdialog.h"


// 消息框
namespace MessageBox
{
    // 提示（NONE）
    QMessageBox::StandardButton exclamation(QWidget* parent, const QString& text)
    {
        MsgBoxDialog dialog(text, QMessageBox::NoButton, QMessageBox::NoButton, parent);
        dialog.exec();
        return dialog.select();
    }

    QMessageBox::StandardButton exclamationIds(QWidget* parent, const QString& ids)
    {
        return MessageBox::exclamation(parent, Language::getString(ids));
    }

    // 提示（OK）
    QMessageBox::StandardButton information(QWidget* parent, const QString& text)
    {
        MsgBoxDialog dialog(text, QMessageBox::Ok, QMessageBox::NoButton, parent);
        dialog.exec();
        return dialog.select();
    }

    QMessageBox::StandardButton informationIds(QWidget* parent, const QString& ids)
    {
        return MessageBox::information(parent, Language::getString(ids));
    }

    // 询问（YES/NO）
    QMessageBox::StandardButton question(QWidget* parent, const QString& text)
    {
        MsgBoxDialog dialog(text, QMessageBox::Yes, QMessageBox::No, parent);
        dialog.exec();
        return dialog.select();
    }

    QMessageBox::StandardButton questionIds(QWidget* parent, const QString& ids)
    {
        return MessageBox::question(parent, Language::getString(ids));
    }

    // 警告（OK）
    QMessageBox::StandardButton warning(QWidget* parent, const QString& text)
    {
        MsgBoxDialog dialog(text, QMessageBox::Ok, QMessageBox::NoButton, parent);
        dialog.exec();
        return dialog.select();
    }

    QMessageBox::StandardButton warningIds(QWidget* parent, const QString& ids)
    {
        return MessageBox::warning(parent, Language::getString(ids));
    }
}