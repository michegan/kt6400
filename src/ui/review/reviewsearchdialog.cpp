#include "field.h"
#include "gender.h"
#include "datetime.h"
#include "sampleinfo.h"
#include "reviewsearchdialog.h"


ReviewSearchDialog::ReviewSearchDialog(QWidget* parent)
    : Dialog(parent), scondition("")
{
    ui.setupUi(this);

    // 界面字符串
    this->setWindowText();

    // 关联信号槽
    connect(ui.pbAll, SIGNAL(clicked()), this, SLOT(onBtnAllClicked()));
    connect(ui.pbSearch, SIGNAL(clicked()), this, SLOT(onBtnSearchClicked()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));
}

ReviewSearchDialog::~ReviewSearchDialog()
{

}

// 查询条件
QString ReviewSearchDialog::condition() const
{
    return this->scondition;
}

// 界面字符串
void ReviewSearchDialog::setWindowText()
{
    // 基类处理
    Dialog::setWindowText();

    // 子类处理
    this->setText(ui.lbSampleId, "IDS_SAMPLE_ID");
    this->setText(ui.lbGender, "IDS_GENDER");
    this->setText(ui.rbMale, "IDS_MALE");
    this->setText(ui.rbFemale, "IDS_FEMALE");
    this->setText(ui.lbPatientId, "IDS_PATIENT_ID");
    this->setText(ui.lbName, "IDS_NAME");
    this->setText(ui.lbSender, "IDS_SENDER");
    this->setText(ui.lbSendDate, "IDS_SEND_TIME");
    this->setText(ui.pbSearch, "IDS_SEARCH");
    this->setText(ui.pbCancel, "IDS_CANCEL");
}

// 按钮点击
void ReviewSearchDialog::onBtnAllClicked()
{
    // 无条件
    this->scondition.clear();

    // 关闭对话框
    this->accept();
}

void ReviewSearchDialog::onBtnSearchClicked()
{
    // 所有条件值
    QString sampleId = ui.leSampleId->text();
    QString patientId = ui.lePatientId->text();
    QString name = ui.leName->text();
    QString sender = ui.cbSender->currentText();
    QDate sendDate = ui.leSendDate->date();

    // 所有条件组成的列表
    QStringList conditions;
    if (!sampleId.isEmpty())
    {
        QString condition = QString("%1 LIKE '%%2%'").arg(F_SID).arg(sampleId);
        conditions.append(condition);
    }

    if (!patientId.isEmpty())
    {
        QString condition = QString("%1 LIKE '%%2%'").arg(F_PID).arg(patientId);
        conditions.append(condition);
    }

    if (!name.isEmpty())
    {
        QString condition = QString("%1 LIKE '%%2%'").arg(F_NAME).arg(name);
        conditions.append(condition);
    }

    if (!sender.isEmpty())
    {
        QString condition = QString("%1 LIKE '%%2%'").arg(F_SENDER).arg(sender);
        conditions.append(condition);
    }

    if (sendDate.isValid())
    {
        const QString format = "yyyy-MM-dd";
        QString condition = QString("'%1 '= %2").arg(F_SEND_TIME).arg(sendDate.toString(format));
        conditions.append(condition);
    }

    // 所有条件列表组成一个完整的条件
    this->scondition.clear();
    for (int i = 0; i < conditions.length(); i++)
    {
        scondition.append(conditions.at(i));
        if (i < conditions.length() - 1)
        {
            scondition += QString(" AND ");
        }
    }

    // 关闭对话框
    this->accept();
}

void ReviewSearchDialog::onBtnCancelClicked()
{
    this->reject();
}