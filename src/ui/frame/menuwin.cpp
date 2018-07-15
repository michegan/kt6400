#include <QPainter>

#include "menuwin.h"
#include "countwin.h"
#include "loginwin.h"
#include "resource.h"
#include "setupwin.h"
#include "reviewwin.h"
#include "messagebox.h"
#include "maintainwin.h"
#include "ljqcfilewin.h"
#include "selftestwin.h"
#include "calibratewin.h"
#include "shutdowndialog.h"


MenuWin::MenuWin(QWidget* parent)
    : FuncWin(parent)
{
    ui.setupUi(this);

    // �����ַ���
    this->setWindowText();

    // ���ڱ�ʶ
    this->setWId("MenuWin");

    // �����źŲ�
    this->connect(ui.pbCount, SIGNAL(clicked()), this, SLOT(onBtnCountClicked()));
    this->connect(ui.pbReview, SIGNAL(clicked()), this, SLOT(onBtnReviewClicked()));
    this->connect(ui.pbQc, SIGNAL(clicked()), this, SLOT(onBtnQcClicked()));
    this->connect(ui.pbCalibrate, SIGNAL(clicked()), this, SLOT(onBtnCalibrateClicked()));
    this->connect(ui.pbMaintain, SIGNAL(clicked()), this, SLOT(onBtnMaintainClicked()));
    this->connect(ui.pbSelftest, SIGNAL(clicked()), this, SLOT(onBtnSelftestClicked()));
    this->connect(ui.pbSetup, SIGNAL(clicked()), this, SLOT(onBtnSetupClicked()));
    this->connect(ui.pbLogOff, SIGNAL(clicked()), this, SLOT(onBtnLogOffClicked()));
    this->connect(ui.pbShutdown, SIGNAL(clicked()), this, SLOT(onBtnShutdownClicked()));
}

MenuWin::~MenuWin()
{

}

// �����ַ���
void MenuWin::setWindowText()
{
    // ���ദ��
    // FuncWin::setWindowText();

    // ���ദ��
    this->setText(ui.pbCount, "IDS_COUNT");
    this->setText(ui.pbReview, "IDS_REVIEW");
    this->setText(ui.pbQc, "IDS_QC");
    this->setText(ui.pbCalibrate, "IDS_CALIBRATE");
    this->setText(ui.pbMaintain, "IDS_MAINTAIN");
    this->setText(ui.pbSelftest, "IDS_SELFTEST");
    this->setText(ui.pbSetup, "IDS_SETUP");
    this->setText(ui.pbLogOff, "IDS_LOGOFF");
    this->setText(ui.pbShutdown, "IDS_SHUTDOWN");
}

// �¼�����
void MenuWin::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    // ���Ʊ���ͼ
    const QImage* image = Resource::image("big_logo");
    if (image)
    {
        painter.drawImage(150, 0, *image);
    }

    // ���ദ��
    FuncWin::paintEvent(event);
}

// ��ť���
void MenuWin::onBtnCountClicked()
{
    this->switchToFuncWin(new CountWin());
}

void MenuWin::onBtnReviewClicked()
{
    this->switchToFuncWin(new ReviewWin());
}

void MenuWin::onBtnQcClicked()
{
    this->switchToFuncWin(new LJQcFileWin());
}

void MenuWin::onBtnCalibrateClicked()
{
    this->switchToFuncWin(new CalibrateWin());
}

void MenuWin::onBtnMaintainClicked()
{
    this->switchToFuncWin(new MaintainWin());
}

void MenuWin::onBtnSelftestClicked()
{
    this->switchToFuncWin(new SelftestWin());
}

void MenuWin::onBtnSetupClicked()
{
    this->switchToFuncWin(new SetupWin());
}

void MenuWin::onBtnLogOffClicked()
{
    QMessageBox::StandardButton button = MessageBox::questionIds(this, "IDS_LOGOFF_Q");
    if (QMessageBox::Yes == button)
    {
        this->switchToFuncWin(new LoginWin());
    }
}

void MenuWin::onBtnShutdownClicked()
{
    QMessageBox::StandardButton button = MessageBox::questionIds(this, "IDS_SHUTDOWN_MACHINE");
    if (QMessageBox::Yes == button)
    {
        ShutDownDialog dialog(this);
        dialog.exec();
    }
}