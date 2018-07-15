#include "field.h"
#include "uivariants.h"
#include "ljqcfilewin.h"
#include "ljqcgraphwin.h"
#include "ljqcfiletable.h"


LJQcGraphWin::LJQcGraphWin(QWidget* parent)
    : FuncWin(parent), fileNo(0), lbFileNo(0), leFileNo(0), fileTable(new LJQcFileTable())
{
    ui.setupUi(this);

    // 文件号
    this->fileNo = UIVariants::intVariant(F_FILENO);

    // 创建状态条
    this->createStatusBar();

    // 窗口标识
    this->setWId("LJQcGraphWin");

    // 关联信号槽
    this->connect(ui.pbBack, SIGNAL(clicked()), this, SLOT(onBtnBackClicked()));
}

LJQcGraphWin::~LJQcGraphWin()
{
    // 文件表
    delete this->fileTable;
}

// 创建状态条
void LJQcGraphWin::createStatusBar()
{
    // 基类处理
    FuncWin::createStatusBar();

    // 子类处理
    this->lbFileNo = new QLabel(this);
    this->lbFileNo->setText("File No.");
    this->lbFileNo->setGeometry(0, 565, 120, 30);

    this->leFileNo = new QLabel(this);
    this->leFileNo->setText(LJQcInfo::fileDesc(this->fileNo));
    this->leFileNo->setGeometry(120, 565, 240, 30);
}

// 按钮点击
void LJQcGraphWin::onBtnBackClicked()
{
    this->switchToFuncWin(new LJQcFileWin());
}