#include "field.h"
#include "messagebox.h"
#include "uivariants.h"
#include "ljqcfilewin.h"
#include "ljqclistwin.h"
#include "ljqcfiletable.h"
#include "ljqcsampletable.h"
#include "ljqctablewidget.h"


LJQcListWin::LJQcListWin(QWidget* parent)
    : FuncWin(parent), fileNo(0), from(0), lbFileNo(0), leFileNo(0), fileTable(new LJQcFileTable()), 
      sampleTable(0), tableWidget(new LJQcTableWidget(this))
{
    ui.setupUi(this);

    // �ļ���
    this->fileNo = UIVariants::intVariant(F_FILENO);

    // ������
    this->sampleTable = new LJQcSampleTable(this->fileNo);
    this->allSamples = this->sampleTable->allSamples();

    // ����״̬��
    this->createStatusBar();

    // ���ڱ�ʶ
    this->setWId("LJQcListWin");

    // �ļ����
    this->tableWidget->setLJQcSampleTable(this->sampleTable);
    this->tableWidget->setGeometry(10, 90, 780, 460);

    // �ʿ��ļ���Ϣ
    LJQcInfo ljQcInfo;
    ParaList lowLimits;
    ParaList highLimits;

    if (this->fileTable->getFile(this->fileNo, ljQcInfo, lowLimits, highLimits))
    {
        // ����
        ui.leLotNo->setText(ljQcInfo.lotNo);

        // ��Ч��
        ui.leExpDate->setDate(ljQcInfo.expTime.date());
    }

    // ��ʾ��ǰҳ
    int samples = this->allSamples.length();
    int columns = this->tableWidget->columns();

    this->from = (columns < samples ? samples - columns : 0);

    this->onSelectSampleChanged(this->sampleTable->selectedRecords());

    // �����źŲ�
    this->connect(ui.pbBack, SIGNAL(clicked()), this, SLOT(onBtnBackClicked()));
    this->connect(ui.pbDelete, SIGNAL(clicked()), this, SLOT(onBtnDeleteClicked()));
    this->connect(ui.pbPrint, SIGNAL(clicked()), this, SLOT(onBtnPrintClicked()));
    this->connect(ui.pbPageUp, SIGNAL(clicked()), this, SLOT(onBtnPageUpClicked()));
    this->connect(ui.pbPageDown, SIGNAL(clicked()), this, SLOT(onBtnPageDownClicked()));

    this->connect(this->tableWidget, SIGNAL(columnClicked(int, bool)), this, SLOT(onColumnClicked(int, bool)));
    this->connect(this->sampleTable, SIGNAL(selectedRecordsChanged(const QList<int>&)), this, SLOT(onSelectSampleChanged(const QList<int>&)));
}

LJQcListWin::~LJQcListWin()
{
    // �ļ���
    delete this->fileTable;
    // ������
    delete this->sampleTable;
}

// ����״̬��
void LJQcListWin::createStatusBar()
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
void LJQcListWin::onBtnBackClicked()
{
    this->switchToFuncWin(new LJQcFileWin());
}

void LJQcListWin::onBtnPrintClicked()
{

}

void LJQcListWin::onBtnDeleteClicked()
{
    if (QMessageBox::Yes == MessageBox::question(this, "Delete samples ?"))
    {
        // ɾ��ѡ������
        this->sampleTable->deleteSelectSamples();
    }
}

void LJQcListWin::onBtnPageUpClicked()
{
    int columns = this->tableWidget->columns();

    // ҳ��ʼ
    int samples = this->allSamples.length();
    if (this->from + columns * 2 < samples)
    {
        this->from += columns;
    }
    else
    {
        this->from = samples - columns;
    }

    // ��ʾ��ǰҳ
    this->showCurrentPage();
}

void LJQcListWin::onBtnPageDownClicked()
{
    int columns = this->tableWidget->columns();

    // ҳ��ʼ
    if (columns < this->from)
    {
        this->from -= columns;
    }
    else
    {
        this->from = 0;
    }

    // ��ʾ��ǰҳ
    this->showCurrentPage();
}

// �����ѡ��
void LJQcListWin::onColumnClicked(int columnNo, bool selected)
{
    int index = this->from + columnNo;
    if (0 <= index && index < this->allSamples.length())
    {
        int fid = this->allSamples.at(index);
        if (0 < fid)
        {
            // �µĵ�ǰ����
            this->sampleTable->selectedRecord(fid, selected);
        }
    }
}

// ѡ�������仯
void LJQcListWin::onSelectSampleChanged(const QList<int>& fids)
{
    // ��ʾ��ǰҳ
    this->showCurrentPage();
}

// ��ʾ��ǰҳ
void LJQcListWin::showCurrentPage()
{
    int columns = this->tableWidget->columns();
    QList<int> selectSamples = this->sampleTable->selectedRecords();

    // ��ǰҳ
    for (int column = 0; column < columns; column++)
    {
        int index = this->from + column;
        if (0 <= index && index < this->allSamples.length())
        {
            int fid = this->allSamples.at(index);
            this->tableWidget->setSelect(column, selectSamples.contains(fid));
        }
    }
    this->tableWidget->setSamples(this->allSamples.mid(this->from, columns));

    // ��ť״̬
    ui.pbPageDown->setEnabled(0 < this->from);
    ui.pbPageUp->setEnabled(this->from + columns < this->allSamples.length());
}