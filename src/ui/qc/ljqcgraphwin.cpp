#include "field.h"
#include "uivariants.h"
#include "ljqcfilewin.h"
#include "ljqcgraphwin.h"
#include "ljqcfiletable.h"


LJQcGraphWin::LJQcGraphWin(QWidget* parent)
    : FuncWin(parent), fileNo(0), lbFileNo(0), leFileNo(0), fileTable(new LJQcFileTable())
{
    ui.setupUi(this);

    // �ļ���
    this->fileNo = UIVariants::intVariant(F_FILENO);

    // ����״̬��
    this->createStatusBar();

    // ���ڱ�ʶ
    this->setWId("LJQcGraphWin");

    // �����źŲ�
    this->connect(ui.pbBack, SIGNAL(clicked()), this, SLOT(onBtnBackClicked()));
}

LJQcGraphWin::~LJQcGraphWin()
{
    // �ļ���
    delete this->fileTable;
}

// ����״̬��
void LJQcGraphWin::createStatusBar()
{
    // ���ദ��
    FuncWin::createStatusBar();

    // ���ദ��
    this->lbFileNo = new QLabel(this);
    this->lbFileNo->setText("File No.");
    this->lbFileNo->setGeometry(0, 565, 120, 30);

    this->leFileNo = new QLabel(this);
    this->leFileNo->setText(LJQcInfo::fileDesc(this->fileNo));
    this->leFileNo->setGeometry(120, 565, 240, 30);
}

// ��ť���
void LJQcGraphWin::onBtnBackClicked()
{
    this->switchToFuncWin(new LJQcFileWin());
}