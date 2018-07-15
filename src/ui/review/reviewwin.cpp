#include <QtDebug>

#include "field.h"
#include "refrange.h"
#include "transmit.h"
#include "reviewwin.h"
#include "messagebox.h"
#include "reviewsampletable.h"
#include "reviewtablewidget.h"
#include "reviewdeletedialog.h"
#include "reviewsearchdialog.h"


ReviewWin::ReviewWin(QWidget* parent)
    : FuncWin(parent), from(0), lbPos(0), lbSelected(0), sampleTable(ReviewSampleTable::instance()), tableWidget(new ReviewTableWidget(this))
{
    ui.setupUi(this);

    // ���ڱ�ʶ
    this->setWId("ReviewWin");

    // ����״̬��
    this->createStatusBar();

    // �����ַ���
    this->setWindowText();

    // �б�
    this->tableWidget->setGeometry(2, 45, 796, 515);
    this->tableWidget->setReviewSampleTable(this->sampleTable);

    // ��ʾ��ǰҳ
    this->onDataChanged();

    // �����źŲ�
    this->connect(ui.pbSearch, SIGNAL(clicked()), this, SLOT(onBtnSearchClicked()));
    this->connect(ui.pbDelete, SIGNAL(clicked()), this, SLOT(onBtnDeleteClicked()));
    this->connect(ui.pbPrint, SIGNAL(clicked()), this, SLOT(onBtnPrintClicked()));
    this->connect(ui.pbPageUp, SIGNAL(clicked()), this, SLOT(onBtnPageUpClicked()));
    this->connect(ui.pbPageDown, SIGNAL(clicked()), this, SLOT(onBtnPageDownClicked()));
    this->connect(ui.pbTransmit, SIGNAL(clicked()), this, SLOT(onBtnTransmitClicked()));

    this->connect(this->tableWidget, SIGNAL(columnClicked(int, bool)), this, SLOT(onColumnClicked(int, bool)));

    this->connect(this->sampleTable, SIGNAL(dataChanged()), this, SLOT(onDataChanged()));
    this->connect(this->sampleTable, SIGNAL(selectedRecordsChanged(const QList<int>&)), this, SLOT(onSelectSampleChanged(const QList<int>&)));
    this->connect(this->sampleTable, SIGNAL(currentSampleChanged(int, const QList<int>&)), this, SLOT(onCurrentSampleChanged(int, const QList<int>&)));
}

ReviewWin::~ReviewWin()
{

}

// �����ַ���
void ReviewWin::setWindowText()
{
    // ���ദ��
    FuncWin::setWindowText();

    // ���ദ��
    this->setText(ui.pbDelete, "IDS_DELETE");
    this->setText(ui.pbTransmit, "IDS_TRANSMIT");
    this->setText(ui.pbPrint, "IDS_PRINT");
    this->setText(ui.pbSearch, "IDS_SEARCH");
    this->setText(ui.pbPageDown, "IDS_PAGE_DOWN");
    this->setText(ui.pbPageUp, "IDS_PAGE_UP");

    this->setText(this->lbPos, "IDS_POS");
    this->setText(this->lbSelected, "IDS_SELECTED");
}

// ����״̬��
void ReviewWin::createStatusBar()
{
    // ���ദ��
    FuncWin::createStatusBar();

    // ���ദ��
    this->lbPos = new QLabel(this);
    this->lbPos->setGeometry(0, 565, 240, 32);

    this->lbSelected = new QLabel(this);
    this->lbSelected->setGeometry(240, 565, 240, 32);
}

// ��ť��
void ReviewWin::onBtnSearchClicked()
{
    ReviewSearchDialog dialog(this);
    dialog.exec();

    QString condition = dialog.condition();
    qDebug() << "ReviewWin onBtnSearchClicked" << condition;

    this->sampleTable->clearConditions();
    if (!condition.isEmpty())
    {
        this->sampleTable->addWhereCondition(condition);
    }
    this->sampleTable->selectSamples();
}

void ReviewWin::onBtnDeleteClicked()
{
    ReviewDeleteDialog dialog(this);
    if (QDialog::Accepted == dialog.exec())
    {
        bool deleteAll = dialog.isDeleteAll();
        if (deleteAll)
        {
            // ɾ��ȫ������������������ɾ��ȫ����
            this->sampleTable->deleteAllSamples();
        }
        else
        {
            // ɾ��ѡ������
            this->sampleTable->deleteSelectSamples();
        }
    }
}

void ReviewWin::onBtnPrintClicked()
{

}

void ReviewWin::onBtnPageUpClicked()
{
    int columns = this->tableWidget->columns();
    QList<int> allSamples = this->sampleTable->allSamples();

    // ҳ��ʼ
    if (this->from + columns * 2 < allSamples.length())
    {
        this->from += columns;
    }
    else
    {
        this->from = allSamples.length() - columns;
    }

    // ��ʾ��ǰҳ
    this->showCurrentPage();
}

void ReviewWin::onBtnPageDownClicked()
{
    int columns = this->tableWidget->columns();
    QList<int> allSamples = this->sampleTable->allSamples();

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

void ReviewWin::onBtnTransmitClicked()
{
    // �������
    if (0 == this->sampleTable)
    {
        qWarning() << "ReviewWin onBtnTransmitClicked no sampleTable";
        return;
    }

    // ����ѡ������
    QList<int> selectSamples = this->sampleTable->selectedRecords();
    if (selectSamples.isEmpty())
    {
        qDebug() << "ReviewWin onBtnTransmitClicked no selectedRecords";
        return;
    }

    // ���ͨ��
    int sended = 0;
    foreach (int fid, selectSamples)
    {
        // ��ȡ����
        HistInfo wbcHist;
        HistInfo rbcHist;
        HistInfo pltHist;
        ParaList paraResult;
        SampleInfo sampleInfo;

        if (!this->sampleTable->getSample(fid, sampleInfo, paraResult) || !this->sampleTable->getSample(fid, wbcHist, rbcHist, pltHist))
        {
            qWarning() << "ReviewWin onBtnTransmitClicked getSample" << fid;
            break;
        }

        // ��Ӧ�ο���Χ
        ParaList lowLimits;
        ParaList highLimits;
        if (!RefRange::getLimits(sampleInfo, lowLimits, highLimits))
        {
            qWarning() << "ReviewWin onBtnTransmitClicked no selectedRecords" << fid;
            break;
        }

        // ��������
        paraResult.setLimits(lowLimits, highLimits);
        if (!Transmit::sendSample(sampleInfo, paraResult, wbcHist, rbcHist, pltHist))
        {
            qWarning() << "ReviewWin onBtnTransmitClicked sendSample fail" << fid;
            break;
        }

        // ����������+1
        sended++;
    }

    // ��ʾ�û�
    MessageBox::information(this, QString("Transmit %1 records of %2").arg(sended).arg(selectSamples.length()));
}

// �����ѡ��
void ReviewWin::onColumnClicked(int columnNo, bool selected)
{
    int index = this->from + columnNo;

    int fid = this->sampleTable->fid(index);
    if (0 < fid)
    {
        // �µĵ�ǰ����
        this->sampleTable->setCurrentIndex(index);
        this->sampleTable->selectedRecord(fid, selected);
    }
}

// ���ݱ仯
void ReviewWin::onDataChanged()
{
    int columns = this->tableWidget->columns();
    int current = this->sampleTable->currentIndex();

    this->from = (columns < current ? current - columns + 1 : 0);

    this->onSelectSampleChanged(this->sampleTable->selectedRecords());
    this->onCurrentSampleChanged(current, this->sampleTable->allSamples());
}

// ѡ�������仯
void ReviewWin::onSelectSampleChanged(const QList<int>& fids)
{
    // ��ʾ��ǰҳ
    this->showCurrentPage();
}

// ��ǰ�����仯
void ReviewWin::onCurrentSampleChanged(int index, const QList<int>& fids)
{
    int from = this->from;
    int length = fids.length();
    int columns = this->tableWidget->columns();

    // �����µ���ʼ�У��������㹻���򲻸�����ʼ�У�
    if (from + columns <= length)
    {
        this->from = from;
    }
    else
    {
        this->from = (columns < length ? length - columns : 0);
    }

    // ��ʾ��ǰҳ
    this->showCurrentPage();
}

// ˢ��״̬��
void ReviewWin::updateStatusBar()
{
    const int samples = sampleTable->allSamples().length();

    const int current = sampleTable->currentIndex() + 1;
    this->lbPos->setText(QString("%1 : %2 / %3").arg(this->getString("IDS_POS")).arg(current).arg(samples));

    const int selects = sampleTable->selectedRecords().length();
    this->lbSelected->setText(QString("%1 : %2").arg(this->getString("IDS_SELECTED")).arg(selects));
}

// ��ʾ��ǰҳ
void ReviewWin::showCurrentPage()
{
    int columns = this->tableWidget->columns();
    int currentIndex = this->sampleTable->currentIndex();
    QList<int> allSamples = this->sampleTable->allSamples();
    QList<int> selectSamples = this->sampleTable->selectedRecords();

    // ��ǰҳ
    this->tableWidget->clearColors();

    for (int column = 0; column < columns; column++)
    {
        int fid = this->sampleTable->fid(this->from + column);
        this->tableWidget->setSelect(column, selectSamples.contains(fid));
    }

    this->tableWidget->setFrom(this->from);
    this->tableWidget->setCurrent(currentIndex - this->from);
    this->tableWidget->setSamples(allSamples.mid(this->from, columns));

    // ��ť״̬
    ui.pbPageDown->setEnabled(0 < this->from);
    ui.pbPageUp->setEnabled(this->from + columns < allSamples.length());

    // ˢ��״̬��
    this->updateStatusBar();
}