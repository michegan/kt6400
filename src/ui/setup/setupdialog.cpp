#include <QtDebug>

#include "messagebox.h"
#include "setupdialog.h"


SetupDialog::SetupDialog(QWidget* parent)
    : Dialog(parent)
{

}

SetupDialog::~SetupDialog()
{

}

// 按钮点击
void SetupDialog::onBtnOkClicked()
{
    // 从界面获取设置信息
    this->getSetupInfoFromUI();

    // 设置信息有效性检测（有效返回0，无效返回对应错误码）
    QString ret = this->isSetupInfoValid();
    qDebug() << "SetupDialog onBtnOkClicked" << ret;

    if (ret.isEmpty())
    {
        // 设置信息有效处理（保存设置信息）
        if (this->onSetupInfoValid())
        {
            // 保存成功，退出设置界面
            this->accept();
        }
        else
        {
            // 保存失败，提示用户
            MessageBox::warning(this, "Save failed.");
        }
    }
    else
    {
        // 设置信息无效处理（提示信息）
        QString text = this->onSetupInfoInvalidText(ret);
        MessageBox::warning(this, text);

        // 设置信息无效处理（无效控件）
        QWidget* widget = this->onSetupInfoInvalidWidget(ret);
        if (widget)
        {
            widget->setFocus();
        }
    }
}

void SetupDialog::onBtnCancelClicked()
{
    this->reject();
}