#include <QDir>

#include "path.h"
#include "seqfile.h"
#include "pulsewin.h"
#include "helpdialog.h"
#include "maintainwin.h"
#include "maintaindialog.h"


MaintainWin::MaintainWin(QWidget* parent)
    : FuncWin(parent), dialog(new MaintainDialog(this))
{
    ui.setupUi(this);

    // ����״̬��
    this->createStatusBar();

    // ���ڱ�ʶ
    this->setWId("MaintainWin");

    // �����źŲ�
    this->connect(ui.pbHelp, SIGNAL(clicked()), this, SLOT(onBtnHelpClicked()));

    this->connect(ui.pbInit, SIGNAL(clicked()), this, SLOT(onBtnInitClicked()));
    this->connect(ui.pbPrimeLyse, SIGNAL(clicked()), this, SLOT(onBtnPrimeLyseClicked()));
    this->connect(ui.pbPrimeDiluent, SIGNAL(clicked()), this, SLOT(onBtnPrimeDiluentClicked()));
    this->connect(ui.pbWholeFill, SIGNAL(clicked()), this, SLOT(onBtnWholeFillClicked()));
    this->connect(ui.pbClean, SIGNAL(clicked()), this, SLOT(onBtnCleanClicked()));
    this->connect(ui.pbEnhancedClean, SIGNAL(clicked()), this, SLOT(onBtnEnhancedCleanClicked()));
    this->connect(ui.pbFlush, SIGNAL(clicked()), this, SLOT(onBtnFlushClicked()));
    this->connect(ui.pbEnhancedFlush, SIGNAL(clicked()), this, SLOT(onBtnEnhancedFlushClicked()));
    this->connect(ui.pbPark, SIGNAL(clicked()), this, SLOT(onBtnParkClicked()));

    this->connect(ui.pbPulse, SIGNAL(clicked()), this, SLOT(onBtnPulseClicked()));
    this->connect(ui.pbTscalibrate, SIGNAL(clicked()), this, SLOT(onBtnTscalibrateClicked()));
}

MaintainWin::~MaintainWin()
{

}

// ��ť���
void MaintainWin::onBtnHelpClicked()
{
    HelpDialog dialog(this);
    dialog.exec();
}

void MaintainWin::onBtnInitClicked()
{
    this->onBtnMaintainClicked("Init", SeqFile::initSeqNo());
}

void MaintainWin::onBtnPrimeLyseClicked()
{
    this->onBtnMaintainClicked("Prime Lyse", SeqFile::lyseFillSeqNo());
}

void MaintainWin::onBtnPrimeDiluentClicked()
{
    this->onBtnMaintainClicked("Prime Diluent", SeqFile::diluentFillSeqNo());
}

void MaintainWin::onBtnCleanClicked()
{
    this->onBtnMaintainClicked("Cleaning", SeqFile::cleanSeqNo());
}

void MaintainWin::onBtnEnhancedCleanClicked()
{
    this->onBtnMaintainClicked("Cleaning", SeqFile::enhancedCleanSeqNo());
}

void MaintainWin::onBtnFlushClicked()
{
    this->onBtnMaintainClicked("Back Flush", SeqFile::backFlushSeqNo());
}

void MaintainWin::onBtnEnhancedFlushClicked()
{
    this->onBtnMaintainClicked("Enhanced Flush", SeqFile::enhancedFlushSeqNo());
}

void MaintainWin::onBtnParkClicked()
{
    this->onBtnMaintainClicked("Park", SeqFile::emptyPoolSeqNo());
}

void MaintainWin::onBtnWholeFillClicked()
{
    this->onBtnMaintainClicked("Prime", SeqFile::wholeFillSeqNo());
}

void MaintainWin::onBtnPulseClicked()
{
    this->switchToFuncWin(new PulseWin());
}

void MaintainWin::onBtnTscalibrateClicked()
{
    system("./tscalibrate.sh");
}

// ά����ť���
void MaintainWin::onBtnMaintainClicked(const QString& text, const QString& seqNo)
{
    // �û���ʾ
    this->dialog->setText(text);
    // ʱ���
    this->dialog->runTimeseq(seqNo);
}