#include <QtDebug>

#include "paraname.h"
#include "calibratesetupdialog.h"


CalibrateSetupDialog::CalibrateSetupDialog(QWidget* parent, Qt::WFlags flags)
    : SetupDialog(parent)
{
    ui.setupUi(this);

    // �����ַ���
    this->setWindowText();

    // ����ؼ�
    this->valueEdits.insert(PARA_WBC, ui.leWbc);
    this->valueEdits.insert(PARA_RBC, ui.leRbc);
    this->valueEdits.insert(PARA_PLT, ui.lePlt);
    this->valueEdits.insert(PARA_HGB, ui.leHgb);
    this->valueEdits.insert(PARA_MCV, ui.leMcv);

    // �����źŲ�
    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(onBtnOkClicked()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));
}

CalibrateSetupDialog::~CalibrateSetupDialog()
{

}

// У׼��Ϣ�����ţ�
QString CalibrateSetupDialog::lotNo() const
{
    return this->slotNo;
}

void CalibrateSetupDialog::setLotNo(const QString& lotNo)
{
    ui.leLotNo->setText(lotNo);
}

// У׼��Ϣ����ֵ��������У׼������ͨ��FLAG���֣�
// PARA_IGNORE_FLAG����У׼�˲�����PARA_NORMAL_FLAG��У׼�˲�����
ParaList CalibrateSetupDialog::targets() const
{
    return this->stargets;
}

void CalibrateSetupDialog::setTargets(const ParaList& targets)
{
    for (QMap<QString, DigitLineEdit*>::iterator iter = this->valueEdits.begin(); iter != this->valueEdits.end(); iter++)
    {
        QString key = iter.key();
        DigitLineEdit* lineEdit = this->valueEdits.value(key);

        if (0 <= targets.indexOfPara(key))
        {
            Para para = targets.para(key);
            if (PARA_NORMAL_FLAG == para.flag)
            {
                lineEdit->setValue(para.value);
            }
            else
            {
                lineEdit->clear();
            }
        }
        else
        {
            lineEdit->clear();
        }
    }
}

// �����ַ���
void CalibrateSetupDialog::setWindowText()
{
    // ���ദ��
    Dialog::setWindowText();

    // ���ദ��
    ui.leWbc->setText(PARA_WBC);
    ui.leRbc->setText(PARA_WBC);
    ui.lePlt->setText(PARA_WBC);
    ui.leHgb->setText(PARA_WBC);
    ui.leMcv->setText(PARA_WBC);

    this->setText(ui.lbLotNo, "IDS_LOT_NO");
    this->setText(ui.pbOk, "IDS_OK");
    this->setText(ui.pbCancel, "IDS_CANCEL");
}

// �ӽ����ȡ������Ϣ
void CalibrateSetupDialog::getSetupInfoFromUI()
{
    // У׼��Ϣ�����ţ�
    this->slotNo = ui.leLotNo->text();
    
    // У׼��Ϣ����ֵ��������У׼������ͨ��FLAG���֣�
    // PARA_IGNORE_FLAG����У׼�˲�����PARA_NORMAL_FLAG��У׼�˲�������Ч��PARA_ALARM_FLAG��У׼�˲�������Ч��
    this->stargets.clear();
    for (QMap<QString, DigitLineEdit*>::iterator iter = this->valueEdits.begin(); iter != this->valueEdits.end(); iter++)
    {
        QString key = iter.key();
        DigitLineEdit* lineEdit = this->valueEdits.value(key);

        if (lineEdit->isValid())
        {
            float value = lineEdit->value();
            if (0 < value)
            {
                this->stargets.appendPara(key, lineEdit->value());
            }
            else
            {
                this->stargets.appendPara(key, lineEdit->value(), PARA_IGNORE_FLAG);
            }
        }
        else
        {
            this->stargets.appendPara(key, lineEdit->value(), PARA_ALARM_FLAG);
        }
    }
}

// ������Ϣ��Ч�Լ�⣨��Ч����0����Ч���ض�Ӧ�����룩
QString CalibrateSetupDialog::isSetupInfoValid()
{
    foreach (Para para, this->stargets)
    {
        if (PARA_ALARM_FLAG == para.flag)
        {
            return para.name;
        }
    }
    return QString();
}

// ������Ϣ��Ч������ʾ��Ϣ��
QString CalibrateSetupDialog::onSetupInfoInvalidText(const QString& ret)
{
    return ("Invalid para");
}

QWidget* CalibrateSetupDialog::onSetupInfoInvalidWidget(const QString& ret)
{
    return this->valueEdits.value(ret, 0);
}

// ������Ϣ��Ч��������������Ϣ��
bool CalibrateSetupDialog::onSetupInfoValid()
{
    return true;
}