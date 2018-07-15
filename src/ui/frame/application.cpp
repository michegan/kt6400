#include <QtDebug>
#include <QtGlobal>

#include "hal.h"
#include "log.h"
#include "path.h"
#include "cache.h"
#include "haldma.h"
#include "halfpga.h"
#include "project.h"
#include "gainxml.h"
#include "project.h"
#include "reagent.h"
#include "timeseq.h"
#include "database.h"
#include "datetime.h"
#include "halsigno.h"
#include "language.h"
#include "libinter.h"
#include "resource.h"
#include "halnetlink.h"
#include "halreagent.h"
#include "machinexml.h"
#include "sampleinfo.h"
#include "application.h"
#include "languagexml.h"
#include "refrangexml.h"
#include "calfactorxml.h"
#include "inputcontext.h"
#include "nextsampletable.h"


Application::Application(int& argc, char** argv)
    : QApplication(argc, argv)
{

}

Application::~Application()
{

}

// ��ʼ������ʼ��˳��Ƚ���Ҫ����Ϊ�������������ϵ�����Ը���ʱҪС�ģ�
void Application::init()
{
    // LOG��ʼ��
    this->logInit();

    // COMMON��ʼ��
    this->commonInit();

    // CONFIG��ʼ��
    this->configInit();

    // HAL��ʼ��
    this->halInit();

    // TIMESEQ��ʼ��
    this->timeseqInit();

    // LANGUAGE��ʼ��
    this->languageInit();

    // DATABASE��ʼ��
    this->databaseInit();

    // REAGENT��ʼ��
    this->reagentInit();
}

// LOG��ʼ��
void Application::logInit()
{
    // ��־�ļ���
    QString logFileName = "./log/app.log";
    // ��־�ļ�����
    int maxLogFileLen = (20 * 1024 * 1024);

    // ��־ģ���ʼ��
    Log::init(logFileName, maxLogFileLen);

    // ע�������Ϣ������
    qInstallMsgHandler(Log::syncMessageOutput);
}

// HAL��ʼ��
void Application::halInit()
{
    // ������Ҫ��������������˳��

    // FPGAͨ��
    HalFpga::init();

    // ���ݲɼ�
    HalDma::init();

    // �źų�ʼ��
    HalSigno::init();

    // NETLINKͨ��
    HalNetlink::init_wh_sock();
    HalNetlink::create_lp_kernel_sock();

    // �·�����
    {
        GainXml xml;
        if (xml.load())
        {
            QString value = xml.getTextValue2(KEY1_GAIN, KEY2_WBC);
            HalFpga::write_addr(WBC_GAIN, value.toInt());

            value = xml.getTextValue2(KEY1_GAIN, KEY2_RBC);
            HalFpga::write_addr(RBC_GAIN, value.toInt());

            value = xml.getTextValue2(KEY1_GAIN, KEY2_HGB);
            HalFpga::write_addr(HGB_GAIN, value.toInt());
        }
    }

    {

    }

#ifndef _WIN32
    // LIBINTER
    SysEventInit();
    SysTaskInit();
    InitSysEnv();
    InitAlarmSet();
#endif
}

// CONFIG��ʼ��
void Application::configInit()
{
    // ����ʱ���ʽ
    {
        LanguageXml xml;
        if (xml.load())
        {
            QString dateFormat = xml.getTextValue2(KEY1_LANGUAGE, KEY2_DATE_FORMAT);
            DateTime::setDateFormat(dateFormat);
        }
        else
        {
            qWarning() << "Application configInit LanguageXml load fail";
        }
    }

    // ��������
    {
        MachineXml xml;
        if (xml.load())
        {
            QString forPets = xml.getTextValue2(KEY1_MACHINE, KEY2_FOR_PETS);
            Cache::setForPets("0" != forPets);
        }
        else
        {
            qWarning() << "Application configInit MachineXml load fail";
        }
    }

    // У׼ϵ��
    {
        CalFactorXml xml;
        if (xml.load())
        {
            // ����У׼ϵ��
            QStringList keys1;
            keys1 << KEY1_USER << KEY1_FACTORY;

            QStringList keys2;
            keys2 << KEY2_WHOLE_BLOOD << KEY2_PERIPHERAL << KEY2_PREDILUENT;

            foreach (QString key1, keys1)
            {
                foreach (QString key2, keys2)
                {
                    QList<CalFactor> calFactors = xml.getCalFactors(key1, key2);
                    Cache::setCalFactors(key1, key2, calFactors);
                }
            }
        }
        else
        {
            qWarning() << "Application configInit CalFactorXml load fail";
        }
    }

    // �ο���Χ
    {
        RefRangeXml xml;
        if (xml.load())
        {
            // ��������
            QStringList keys1 = xml.keys1();
            foreach (QString key1, keys1)
            {
                QStringList keys2 = xml.keys2(key1);
                foreach (QString key2, keys2)
                {
                    // ��ȡ�ο���Χ��Ϣ
                    ParaList lowLimits;
                    ParaList highLimits;
                    if (xml.refRange(key1, key2, lowLimits, highLimits))
                    {
                        Cache::setRefRange(key1, key2, lowLimits, highLimits);
                    }
                    else
                    {
                        qWarning() << "Application configInit refRange fail";
                    }
            }
        } while (0);
        }
        else
        {
            qWarning() << "Application configInit RefRangeXml load fail";
        }
    }

    // void setUserCalFactors(const QList<CalFactor>& factors);

    // void setFactoryCalFactors(const QList<CalFactor>& factors);
}

// TIMESEQ��ʼ��
void Application::timeseqInit()
{
    // ʱ���ʼ��
    Timeseq::init();
}

// COMMON��ʼ��
void Application::commonInit()
{
    // �����Ŀ¼
    Path::setRootPath("./");

    // ��Ŀ����
    Project::load();

    // ͼƬ��Դ��ʼ��
    Resource::init();
}

// REAGENT��ʼ��
void Application::reagentInit()
{
    // �Լ��б�
    QList<int> reagents = Reagent::reagents();
    foreach (int reagent, reagents)
    {
        // ��FPGA��ȡ�Լ���Ϣ
        float remain = HalReagent::remain(reagent);
        float volume = HalReagent::volume(reagent);

        Reagent::setRemain(reagent, remain);
        Reagent::setVolume(reagent, volume);
    }
}

// DATABASE��ʼ��
void Application::databaseInit()
{
    // �����ݿ�
    Database::open("./data/app.db");

    // ���������Ƿ������ͣ�Ĭ�ϲ�ͬ�������ͣ��൱��ÿ�ο�����ָ����Ĭ�ϵ��������ͣ��������˹ػ�ǰ������
    SampleInfo nextSampleInfo;
    NextSampleTable nextSampleTable;

    if (nextSampleTable.nextSampleInfo(nextSampleInfo))
    {
        int speciesMode = (Cache::isForPets() ? SPECIES_MODE_DOG : SPECIES_MODE_HUMAN);

        nextSampleInfo.modes.speciesMode = speciesMode;
        if (nextSampleTable.setNextSampleInfo(nextSampleInfo))
        {
            qDebug() << "Application databaseInit setNextSampleInfo" << speciesMode;
        }
        else
        {
            qWarning() << "Application databaseInit setNextSampleInfo fail";
        }
    }
    else
    {
        qWarning() << "Application databaseInit nextSampleInfo fail";
    }
}

// LANGUAGE��ʼ��
void Application::languageInit()
{
    // ������
    QString fileName = Path::rootPath() + "language/String.txt";
    if (!Language::load(fileName))
    {
        qWarning() << "Application languageInit load fail" << fileName;
    }

    // ����̣����뷨
    InputContext* inputContext = new InputContext();
    inputContext->setEnabled(true);
    inputContext->setLanguage("en-US");
    inputContext->setRootPath(Path::rootPath());

    this->setInputContext(inputContext);
}