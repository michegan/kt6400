#include "define.h"
#include "gender.h"
#include "datetime.h"
#include "nextpeteditdialog.h"


NextPetEditDialog::NextPetEditDialog(QWidget* parent)
    : Dialog(parent), sampleInfo(SampleInfo())
{
    ui.setupUi(this);

    // 最大长度
    ui.leSampleId->setMaxLength(MAX_SID_LEN);
    ui.leName->setMaxLength(MAX_NAME_LEN);

    // 关联信号槽
    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(onBtnOkClicked()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));
}

NextPetEditDialog::~NextPetEditDialog()
{

}

// 样本信息
SampleInfo NextPetEditDialog::getSampleInfo()
{
    return this->sampleInfo;
}

void NextPetEditDialog::setSampleInfo(const SampleInfo& sampleInfo)
{
    // 样本信息
    this->sampleInfo = sampleInfo;

    // 界面显示
    ui.leSampleId->setText(sampleInfo.sampleId);
    this->setText(ui.leMode, sampleInfo.modes.ids());

    ui.leName->setText(sampleInfo.name);

    ui.rbMale->setChecked(GENDER_FEMALE != sampleInfo.gender);
    ui.rbFemale->setChecked(GENDER_FEMALE == sampleInfo.gender);

    QPixmap pixmap("./image/" + sampleInfo.modes.speciesImage());
    pixmap = pixmap.scaled(ui.leSpecies->height(), ui.leSpecies->height());
    ui.leSpecies->setPixmap(pixmap);

    ui.leSendDate->setDate(sampleInfo.sendTime.date());
    ui.leSendTime->setTime(sampleInfo.sendTime.time());

    ui.teComment->setText(sampleInfo.comment);
}

// 按钮点击
void NextPetEditDialog::onBtnOkClicked()
{
    // 获取样本信息
    this->sampleInfo.sampleId = ui.leSampleId->text();

    this->sampleInfo.name = ui.leName->text();

    this->sampleInfo.gender = (ui.rbFemale->isChecked() ? GENDER_FEMALE : GENDER_MALE);

    this->sampleInfo.sendTime = QDateTime(ui.leSendDate->date(), ui.leSendTime->time());

    this->sampleInfo.comment = ui.teComment->toPlainText();

    // 关闭对话框
    this->accept();
}

void NextPetEditDialog::onBtnCancelClicked()
{
    this->reject();
}