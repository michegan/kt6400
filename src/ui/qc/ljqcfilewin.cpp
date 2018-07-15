#include "field.h"
#include "uivariants.h"
#include "ljqcfilewin.h"
#include "ljqclistwin.h"
#include "ljqcgraphwin.h"
#include "ljqcsetupwin.h"
#include "ljqcfiletable.h"
#include "ljqcsampletable.h"
#include "ljqcfiletablewidget.h"


LJQcFileWin::LJQcFileWin(QWidget* parent)
    : FuncWin(parent), fileTable(new LJQcFileTable()), tableWidget(new LJQcFileTableWidget(this))
{
    ui.setupUi(this);

    // ����״̬��
    this->createStatusBar();

    // ���ڱ�ʶ
    this->setWId("LJQcFileWin");

    // �ļ����
    this->tableWidget->setLJQcFileTable(this->fileTable);

    this->onTableWidgetRowClicked(0, true);
    this->tableWidget->setGeometry(20, 70, 760, 400);

    // �����źŲ�
    this->connect(ui.pbList, SIGNAL(clicked()), this, SLOT(onBtnListClicked()));
    this->connect(ui.pbGraph, SIGNAL(clicked()), this, SLOT(onBtnGraphClicked()));
    this->connect(ui.pbSetup, SIGNAL(clicked()), this, SLOT(onBtnSetupClicked()));

    this->connect(this->tableWidget, SIGNAL(rowClicked(int, bool)), this, SLOT(onTableWidgetRowClicked(int, bool)));
}

LJQcFileWin::~LJQcFileWin()
{
    // �ļ���
    delete this->fileTable;
}

// ��ť���
void LJQcFileWin::onBtnListClicked()
{
    LJQcListWin* funcWin = new LJQcListWin();
    if (funcWin)
    {
        this->switchToFuncWin(funcWin);
    }
}

void LJQcFileWin::onBtnGraphClicked()
{
    LJQcGraphWin* funcWin = new LJQcGraphWin();
    if (funcWin)
    {
        this->switchToFuncWin(funcWin);
    }
}

void LJQcFileWin::onBtnSetupClicked()
{
    LJQcSetupWin* funcWin = new LJQcSetupWin();
    if (funcWin)
    {
        this->switchToFuncWin(funcWin);
    }
}

// ��ѡ��
void LJQcFileWin::onTableWidgetRowClicked(int row, bool selected)
{
    // ��¼�ļ���
    int fileNo = (row + 1);
    UIVariants::setVariant(F_FILENO, fileNo);

    // ѡ����
    this->tableWidget->setSelect(row, selected);
}