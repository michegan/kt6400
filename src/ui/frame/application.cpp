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

// 初始化（初始化顺序比较重要，因为对象间有依赖关系，所以更改时要小心）
void Application::init()
{
    // LOG初始化
    this->logInit();

    // COMMON初始化
    this->commonInit();

    // CONFIG初始化
    this->configInit();

    // HAL初始化
    this->halInit();

    // TIMESEQ初始化
    this->timeseqInit();

    // LANGUAGE初始化
    this->languageInit();

    // DATABASE初始化
    this->databaseInit();

    // REAGENT初始化
    this->reagentInit();
}

// LOG初始化
void Application::logInit()
{
    // 日志文件名
    QString logFileName = "./log/app.log";
    // 日志文件上限
    int maxLogFileLen = (20 * 1024 * 1024);

    // 日志模块初始化
    Log::init(logFileName, maxLogFileLen);

    // 注册调试信息处理函数
    qInstallMsgHandler(Log::syncMessageOutput);
}

// HAL初始化
void Application::halInit()
{
    // 尽量不要调整下面代码调用顺序

    // FPGA通信
    HalFpga::init();

    // 数据采集
    HalDma::init();

    // 信号初始化
    HalSigno::init();

    // NETLINK通信
    HalNetlink::init_wh_sock();
    HalNetlink::create_lp_kernel_sock();

    // 下发增益
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

// CONFIG初始化
void Application::configInit()
{
    // 日期时间格式
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

    // 仪器配置
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

    // 校准系数
    {
        CalFactorXml xml;
        if (xml.load())
        {
            // 所有校准系数
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

    // 参考范围
    {
        RefRangeXml xml;
        if (xml.load())
        {
            // 所属物种
            QStringList keys1 = xml.keys1();
            foreach (QString key1, keys1)
            {
                QStringList keys2 = xml.keys2(key1);
                foreach (QString key2, keys2)
                {
                    // 提取参考范围信息
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

// TIMESEQ初始化
void Application::timeseqInit()
{
    // 时序初始化
    Timeseq::init();
}

// COMMON初始化
void Application::commonInit()
{
    // 程序根目录
    Path::setRootPath("./");

    // 项目代号
    Project::load();

    // 图片资源初始化
    Resource::init();
}

// REAGENT初始化
void Application::reagentInit()
{
    // 试剂列表
    QList<int> reagents = Reagent::reagents();
    foreach (int reagent, reagents)
    {
        // 从FPGA读取试剂信息
        float remain = HalReagent::remain(reagent);
        float volume = HalReagent::volume(reagent);

        Reagent::setRemain(reagent, remain);
        Reagent::setVolume(reagent, volume);
    }
}

// DATABASE初始化
void Application::databaseInit()
{
    // 打开数据库
    Database::open("./data/app.db");

    // 开机根据是否宠物机型，默认不同物种类型，相当于每次开机都指定了默认的物种类型，而覆盖了关机前的类型
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

// LANGUAGE初始化
void Application::languageInit()
{
    // 多语言
    QString fileName = Path::rootPath() + "language/String.txt";
    if (!Language::load(fileName))
    {
        qWarning() << "Application languageInit load fail" << fileName;
    }

    // 软键盘，输入法
    InputContext* inputContext = new InputContext();
    inputContext->setEnabled(true);
    inputContext->setLanguage("en-US");
    inputContext->setRootPath(Path::rootPath());

    this->setInputContext(inputContext);
}