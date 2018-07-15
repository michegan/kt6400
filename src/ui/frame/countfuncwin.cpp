#include <QtDebug>

#include "cache.h"
#include "countfuncwin.h"
#include "modeeditdialog.h"
#include "nextsampletable.h"
#include "specieseditdialog.h"


CountFuncWin::CountFuncWin(QWidget* parent)
    : FuncWin(parent), nextSampleInfo(new SampleInfo()), nextSampleTable(new NextSampleTable())
{
    // ���ڱ�ʶ
    this->setWId("CountFuncWin");

    // ����״̬��
    this->createStatusBar();

    // ����ģʽ��ť����������Ϳɼ�
    this->pbNextSpecies->setVisible(Cache::isForPets());

    // ��ȡ��һ������Ϣ
    this->nextSampleTable->nextSampleInfo(*this->nextSampleInfo);

    // �����źŲ�
    connect(this->pbNextSpecies, SIGNAL(clicked()), this, SLOT(onBtnSpeciesClcked()));
    connect(this->pbNextSampleMode, SIGNAL(clicked()), this, SLOT(onBtnModeClicked()));
}

CountFuncWin::~CountFuncWin()
{
    // ��һ������Ϣ
    delete this->nextSampleInfo;

    // ��һ�������ݱ�
    delete this->nextSampleTable;
}

// ��һ������Ϣ
SampleInfo CountFuncWin::getNextSampleInfo() const
{
    return *this->nextSampleInfo;
}

void CountFuncWin::setNextSampleInfo(const SampleInfo& sampleInfo)
{
    // ������Ϣ
    if (this->nextSampleTable->setNextSampleInfo(sampleInfo))
    {
        *this->nextSampleInfo = sampleInfo;

        // ��ʾ��һ������Ϣ
        this->showNextSampleInfo(sampleInfo);
    }
    else
    {
        qWarning() << "CountFuncWin setNextSampleInfo setNextSampleInfo fail";
    }
}

// ����״̬��
void CountFuncWin::createStatusBar()
{
    // ���ദ��
    FuncWin::createStatusBar();

    // ���ദ��
    this->pbNextSpecies = new QPushButton(this);
    this->pbNextSpecies->setFlat(true);
    this->pbNextSpecies->setGeometry(320, 565, 40, 32);
    this->pbNextSpecies->setStyleSheet("margin: 1px; border: 1px; padding: 1px;");

    this->pbNextSampleMode = new QPushButton(this);
    this->pbNextSampleMode->setFlat(true);
    this->pbNextSampleMode->setGeometry(360, 565, 120, 32);
}

// ����ʹ��
void CountFuncWin::enableWindow(bool enable)
{
    // ���ദ��
    FuncWin::enableWindow(enable);

    // ���ദ��
    this->pbNextSpecies->setEnabled(enable);
    this->pbNextSampleMode->setEnabled(enable);
}

// ��ʾ��һ������Ϣ
void CountFuncWin::showNextSampleInfo(const SampleInfo& sampleInfo)
{
    QIcon icon;
    icon.addFile("./image/" + sampleInfo.modes.speciesImage(), QSize(32, 32));
    this->pbNextSpecies->setIcon(icon);
    this->pbNextSpecies->setWindowOpacity(0);

    this->setText(this->pbNextSampleMode, sampleInfo.modes.ids());
}

// ��ť���
void CountFuncWin::onBtnModeClicked()
{
    // ��һ������Ϣ
    SampleInfo* sampleInfo = this->nextSampleInfo;

    // ģʽ�Ի���
    ModeEditDialog dialog(this);
    dialog.setModes(sampleInfo->modes);

    if (QDialog::Accepted == dialog.exec())
    {
        // �ӶԻ����ȡģʽ��Ϣ
        sampleInfo->modes = dialog.getModes();

        // �������ݿ�
        if (this->nextSampleTable->setNextSampleInfo(*sampleInfo))
        {
            this->showNextSampleInfo(*sampleInfo);
        }
        else
        {
            qWarning() << "CountFuncWin onBtnModeClicked setNextSampleInfo fail";
        }
    }
}

void CountFuncWin::onBtnSpeciesClcked()
{
    // ��һ������Ϣ
    SampleInfo* sampleInfo = this->nextSampleInfo;

    // ģʽ�Ի���
    SpeciesEditDialog dialog(this);
    dialog.setSpeciesMode(sampleInfo->modes.speciesMode);

    if (QDialog::Accepted == dialog.exec())
    {
        // �ӶԻ����ȡģʽ��Ϣ
        sampleInfo->modes.speciesMode = dialog.speciesMode();

        // �������ݿ�
        if (this->nextSampleTable->setNextSampleInfo(*sampleInfo))
        {
            this->showNextSampleInfo(*sampleInfo);
        }
        else
        {
            qWarning() << "CountFuncWin onBtnSpeciesClcked setNextSampleInfo fail";
        }
    }
}