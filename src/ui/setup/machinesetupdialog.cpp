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

    // 所有机型
    QDir mdir(Path::rootPath() + "machine");
    QStringList machines = mdir.entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);

    ui.cbMachine->insertItems(0, machines);

    // 所有语言
    QDir ldir(Path::rootPath() + "language");
    QStringList languages = ldir.entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);

    ui.cbLanguage->insertItems(0, languages);

    // 当前机型
    this->machine1 = Project::project();
    ui.cbMachine->setCurrentIndex(machines.indexOf(this->machine1));

    // 测试速度
    QStringList speeds;
    speeds << "35" << "40" << "60";
    ui.cbTestSpeed->insertItems(0, speeds);

    // 稀释比
    QStringList diluents;
    diluents << "100" << "130" << "150";
    ui.cbDiluent->insertItems(0, diluents);

    // 溶血剂消耗量
    QStringList lyses;
    lyses << "100" << "120";
    ui.cbLyse->insertItems(0, lyses);

    // 当前序列号，语言
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

    // 保存变量
    this->sn2 = this->sn1;
    this->lyse2 = this->lyse1;
    this->diluent2 = this->diluent1;
    this->testSpeed2 = this->testSpeed1;
    this->forPets2 = this->forPets1;
    this->machine2 = this->machine1;
    this->language2 = this->language1;

    // 关联信号槽
    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(onBtnOkClicked()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));
}

MachineSetupDialog::~MachineSetupDialog()
{

}

// 从界面获取设置信息
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

// 设置信息有效性检测（有效返回0，无效返回对应错误码）
QString MachineSetupDialog::isSetupInfoValid()
{
    return QString();
}

// 设置信息无效处理（提示信息）
QString MachineSetupDialog::onSetupInfoInvalidText(const QString& ret)
{
    return QString();
}

QWidget* MachineSetupDialog::onSetupInfoInvalidWidget(const QString& ret)
{
    return 0;
}

// 设置信息有效处理（保存设置信息）
bool MachineSetupDialog::onSetupInfoValid()
{
    bool ret = false;
    bool reboot = false;

    do 
    {
        // 序列号，稀释比，溶血剂耗量，测试速度
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

        // 机型
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

        // 语言
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

        // 宠物版
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