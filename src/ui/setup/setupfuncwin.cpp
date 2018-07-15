#include <QtDebug>
#include <QMessageBox>

#include "setupfuncwin.h"


SetupFuncWin::SetupFuncWin(QWidget* parent)
    : FuncWin(parent)
{
    // 创建状态条
    this->createStatusBar();
}

SetupFuncWin::~SetupFuncWin()
{

}

// 切换到功能窗口
void SetupFuncWin::switchToFuncWin(FuncWin* funcWin)
{
    // 从界面获取设置信息
    this->getSetupInfoFromUI();

    // 设置信息是否变化
    if (this->isSetupInfoChanged())
    {
        QMessageBox::StandardButton button = QMessageBox::question(this, "Confirm", "Save or not?", 
                                                                    QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, QMessageBox::Yes);
        if (QMessageBox::Yes == button)
        {
            // 设置信息有效性检测（有效返回0，无效返回对应错误码）
            QString ret = this->isSetupInfoValid();
            qDebug() << "SetupFuncWin switchToFuncWin" << ret;

            if (ret.isEmpty())
            {
                // 设置信息有效处理（保存设置信息）
                if (this->onSetupInfoValid())
                {
                    // 保存成功，退出设置界面
                    FuncWin::switchToFuncWin(funcWin);
                }
                else
                {
                    // 保存失败，提示用户
                    QMessageBox::warning(this, "Warning", "Save failed");
                }
            }
            else
            {
                // 设置信息无效处理（提示信息）
                QString text = this->onSetupInfoInvalidText(ret);
                QMessageBox::warning(this, "Warning", text);

                // 设置信息无效处理（无效控件）
                QWidget* widget = this->onSetupInfoInvalidWidget(ret);
                if (widget)
                {
                    widget->setFocus();
                }
            }
        }
        else if (QMessageBox::No == button)
        {
            // 不保存，退出设置界面
            FuncWin::switchToFuncWin(funcWin);
        }
        else
        {
            // 取消，停留在设置界面
        }
    }
    else
    {
        // 设置信息未变化，可直接切换
        FuncWin::switchToFuncWin(funcWin);
    }
}