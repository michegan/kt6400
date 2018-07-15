#include <QDir>
#include <QtDebug>

#include "path.h"
#include "project.h"
#include "utility.h"
#include "machinexml.h"
#include "messagebox.h"
#include "machinesetupdialog.h"


MachineSetupDialog::MachineSetupDialog(QWidget* parent, Qt::WFlags flags)
    : SetupDialog(parent)
{
    ui.setupUi(this);

    // ���л���
    QDir mdir(Path::rootPath() + "machine");
    QStringList machines = mdir.entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);

    ui.cbMachine->insertItems(0, machines);

    // ��������
    QDir ldir(Path::rootPath() + "language");
    QStringList languages = ldir.entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);

    ui.cbLanguage->insertItems(0, languages);

    // ��ǰ����
    this->machine1 = Project::project();
    ui.cbMachine->setCurrentIndex(machines.indexOf(this->machine1));

    // �����ٶ�
    QStringList speeds;
    speeds << "35" << "40" << "60";
    ui.cbTestSpeed->insertItems(0, speeds);

    // ϡ�ͱ�
    QStringList diluents;
    diluents << "100" << "130" << "150";
    ui.cbDiluent->insertItems(0, diluents);

    // ��Ѫ��������
    QStringList lyses;
    lyses << "100" << "120";
    ui.cbLyse->insertItems(0, lyses);

    // ��ǰ���кţ�����
    MachineXml xml;
    if (xml.load())
    {
        this->sn1 = xml.getTextValue2(KEY1_MACHINE, KEY2_SN);
        this->language1 = xml.getTextValue2(KEY1_MACHINE, KEY2_LANGUAGE);
        this->forPets1 = (int)xml.getFloatValue2(KEY1_MACHINE, KEY2_FOR_PETS);
        this->lyse1 = xml.getTextValue2(KEY1_MACHINE, KEY2_LYSE_VOLUME);
        this->diluent1 = xml.getTextValue2(KEY1_MACHINE, KEY2_DILUENT_FACTOR);
        this->testSpeed1 = xml.getTextValue2(KEY1_MACHINE, KEY2_TEST_SPEED);

        ui.leSn->setText(this->sn1);
        ui.cbForPets->setChecked(this->forPets1);
        ui.cbLyse->setCurrentIndex(lyses.indexOf(this->lyse1));
        ui.cbLanguage->setCurrentIndex(languages.indexOf(this->language1));
        ui.cbMachine->setCurrentIndex(machines.indexOf(this->machine1));
        ui.cbTestSpeed->setCurrentIndex(speeds.indexOf(this->testSpeed1));
        ui.cbDiluent->setCurrentIndex(diluents.indexOf(this->diluent1));
    }
    else
    {
        qWarning() << "MachineSetupDialog MachineSetupDialog load fail";
    }

    // �������
    this->sn2 = this->sn1;
    this->lyse2 = this->lyse1;
    this->diluent2 = this->diluent1;
    this->testSpeed2 = this->testSpeed1;
    this->forPets2 = this->forPets1;
    this->machine2 = this->machine1;
    this->language2 = this->language1;

    // �����źŲ�
    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(onBtnOkClicked()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));
}

MachineSetupDialog::~MachineSetupDialog()
{

}

// �ӽ����ȡ������Ϣ
void MachineSetupDialog::getSetupInfoFromUI()
{
    this->sn2 = ui.leSn->text();
    this->machine2 = ui.cbMachine->currentText();
    this->language2 = ui.cbLanguage->currentText();
    this->forPets2 = (ui.cbForPets->isChecked() ? 1 :0 );
    this->lyse2 = ui.cbLyse->currentText();
    this->diluent2 = ui.cbDiluent->currentText();
    this->testSpeed2 = ui.cbTestSpeed->currentText();
}

// ������Ϣ��Ч�Լ�⣨��Ч����0����Ч���ض�Ӧ�����룩
QString MachineSetupDialog::isSetupInfoValid()
{
    return QString();
}

// ������Ϣ��Ч������ʾ��Ϣ��
QString MachineSetupDialog::onSetupInfoInvalidText(const QString& ret)
{
    return QString();
}

QWidget* MachineSetupDialog::onSetupInfoInvalidWidget(const QString& ret)
{
    return 0;
}

// ������Ϣ��Ч��������������Ϣ��
bool MachineSetupDialog::onSetupInfoValid()
{
    bool ret = false;
    bool reboot = false;

    do 
    {
        // ���кţ�ϡ�ͱȣ���Ѫ�������������ٶ�
        if (this->sn1 != this->sn2 || this->lyse1 != this->lyse2 || this->diluent1 != this->diluent2 || this->testSpeed1 != this->testSpeed2)
        {
            MachineXml xml;
            if (!xml.load())
            {
                qWarning() << "MachineSetupDialog onSetupInfoValid machineXml load fail";
                break;
            }

            xml.setTextValue2(KEY1_MACHINE, KEY2_SN, this->sn2);
            xml.setTextValue2(KEY1_MACHINE, KEY2_LYSE_VOLUME, this->lyse2);
            xml.setTextValue2(KEY1_MACHINE, KEY2_TEST_SPEED, this->testSpeed2);
            xml.setTextValue2(KEY1_MACHINE, KEY2_DILUENT_FACTOR, this->diluent2);

            if (!xml.save())
            {
                qWarning() << "MachineSetupDialog onSetupInfoValid machineXml save fail";
                break;
            }
        }

        // ����
        if (this->machine1 != this->machine2)
        {
            QString srcPath = Path::rootPath() + "machine/" + this->machine2 + "/config";
            QString destPath = Path::rootPath() + "config";

            if (!Utility::cpPath(srcPath, destPath))
            {
                qWarning() << "MachineSetupDialog onSetupInfoValid cpPath fail" << srcPath << destPath;
                break;
            }

            srcPath = Path::rootPath() + "machine/" + this->machine2 + "/image";
            destPath = Path::rootPath() + "image";

            if (!Utility::cpPath(srcPath, destPath))
            {
                qWarning() << "MachineSetupDialog onSetupInfoValid cpPath fail" << srcPath << destPath;
                break;
            }

            reboot = true;
        }

        // ����
        if (this->language1 != this->language2)
        {
            MachineXml xml;
            if (!xml.load())
            {
                qWarning() << "MachineSetupDialog onSetupInfoValid machineXml load fail";
                break;
            }

            xml.setTextValue2(KEY1_MACHINE, KEY2_LANGUAGE, this->language2);

            if (!xml.save())
            {
                qWarning() << "MachineSetupDialog onSetupInfoValid machineXml save fail";
                break;
            }

            QString srcPath = Path::rootPath() + "language/" + this->language2 + "/";
            QString destPath = Path::rootPath() + "language/";

            if (!Utility::fileCopy("language.xml", srcPath, destPath))
            {
                qWarning() << "MachineSetupDialog onSetupInfoValid cpPath fail" << srcPath << destPath;
                break;
            }
            if (!Utility::fileCopy("String.txt", srcPath, destPath))
            {
                qWarning() << "MachineSetupDialog onSetupInfoValid cpPath fail" << srcPath << destPath;
                break;
            }

            reboot = true;
        }

        // �����
        if (this->forPets1 != this->forPets2)
        {
            MachineXml xml;
            if (!xml.load())
            {
                qWarning() << "MachineSetupDialog onSetupInfoValid machineXml load fail";
                break;
            }

            xml.setFloatValue2(KEY1_MACHINE, KEY2_FOR_PETS, (int)this->forPets2);

            if (!xml.save())
            {
                qWarning() << "MachineSetupDialog onSetupInfoValid machineXml save fail";
                break;
            }

            reboot = true;
        }

        if (reboot)
        {
            MessageBox::exclamation(this, "Please shutdown and reboot the machine");
        }

        ret = true;
    } while (0);

    return ret;
}