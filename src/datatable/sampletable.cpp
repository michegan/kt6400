#include <QtDebug>

#include "field.h"
#include "paras.h"
#include "paraname.h"
#include "paraunit.h"
#include "sampletable.h"


SampleTable::SampleTable(const QString& table)
    : DataTable(table)
{

}

SampleTable::~SampleTable()
{

}

// 参数列名
QString SampleTable::paraFieldName(const QString& para)
{
    static QMap<QString, QString> map;
    if (map.isEmpty())
    {
        map.insert(PARA_LYM_PER, "LYM_PER");
        map.insert(PARA_MID_PER, "MID_PER");
        map.insert(PARA_GRAN_PER, "GRAN_PER");
        map.insert(PARA_LYM_NUM, "LYM_NUM");
        map.insert(PARA_MID_NUM, "MID_NUM");
        map.insert(PARA_GRAN_NUM, "GRAN_NUM");

        map.insert(PARA_RDW_CV, "RDW_CV");
        map.insert(PARA_RDW_SD, "RDW_SD");
    }
    return map.value(para, para);
}

// 质控信息
void SampleTable::getLJQcInfo(LJQcInfo& qcInfo, const QSqlRecord& record)
{
    qcInfo.fileNo = record.value(F_FILENO).toInt();
    qcInfo.lotNo = record.value(F_LOTNO).toString();
    qcInfo.sampleId = record.value(F_SID).toString();
    qcInfo.isUsed = record.value(F_IS_USED).toInt();
    qcInfo.expTime = record.value(F_EXP_TIME).toDateTime();

    qcInfo.modes.workMode = record.value(F_WORKMODE).toInt();
    qcInfo.modes.sampleMode = record.value(F_SAMPLEMODE).toInt();
    qcInfo.modes.speciesMode = record.value(F_SPECIESMODE).toInt();
    qcInfo.modes.bloodMode = record.value(F_BLOODMODE).toInt();
    qcInfo.modes.analysisMode = record.value(F_ANALYSISMODE).toInt();
    qcInfo.modes.preprocessMode = record.value(F_PREPROCESSMODE).toInt();
}

void SampleTable::setLJQcInfo(QSqlRecord& record, const LJQcInfo& qcInfo)
{
    record.setValue(F_FILENO, qcInfo.fileNo);
    record.setValue(F_LOTNO, qcInfo.lotNo);
    record.setValue(F_SID, qcInfo.sampleId);
    record.setValue(F_IS_USED, qcInfo.isUsed);
    record.setValue(F_EXP_TIME, qcInfo.expTime);

    record.setValue(F_WORKMODE, qcInfo.modes.workMode);
    record.setValue(F_SAMPLEMODE, qcInfo.modes.sampleMode);
    record.setValue(F_SPECIESMODE, qcInfo.modes.speciesMode);
    record.setValue(F_BLOODMODE, qcInfo.modes.bloodMode);
    record.setValue(F_ANALYSISMODE, qcInfo.modes.analysisMode);
    record.setValue(F_PREPROCESSMODE, qcInfo.modes.preprocessMode);
    record.setValue(F_WORKMODE, qcInfo.modes.workMode);
}

// 样本信息
void SampleTable::getSampleInfo(SampleInfo& sampleInfo, const QSqlRecord& record)
{
    sampleInfo.sampleId = record.value(F_SID).toString();

    sampleInfo.modes.workMode = record.value(F_WORKMODE).toInt();
    sampleInfo.modes.sampleMode = record.value(F_SAMPLEMODE).toInt();
    sampleInfo.modes.speciesMode = record.value(F_SPECIESMODE).toInt();
    sampleInfo.modes.bloodMode = record.value(F_BLOODMODE).toInt();
    sampleInfo.modes.analysisMode = record.value(F_ANALYSISMODE).toInt();
    sampleInfo.modes.preprocessMode = record.value(F_PREPROCESSMODE).toInt();

    sampleInfo.sender = record.value(F_SENDER).toString();
    sampleInfo.sendTime = record.value(F_SEND_TIME).toDateTime();
    sampleInfo.tester = record.value(F_TESTER).toString();
    sampleInfo.testTime = record.value(F_TEST_TIME).toDateTime();
    sampleInfo.checker = record.value(F_CHECKER).toString();
    sampleInfo.checkTime = record.value(F_CHECK_TIME).toDateTime();

    sampleInfo.patientId = record.value(F_PID).toString();
    sampleInfo.name = record.value(F_NAME).toString();
    sampleInfo.gender = record.value(F_GENDER).toInt();
    sampleInfo.age = record.value(F_AGE).toString();
    sampleInfo.department = record.value(F_DEPARTMENT).toString();
    sampleInfo.bedNo = record.value(F_BED_NO).toString();
    sampleInfo.comment = record.value(F_COMMENT).toString();
}

void SampleTable::setSampleInfo(QSqlRecord& record, const SampleInfo& sampleInfo)
{
    record.setValue(F_SID, sampleInfo.sampleId);

    record.setValue(F_WORKMODE, sampleInfo.modes.workMode);
    record.setValue(F_SAMPLEMODE, sampleInfo.modes.sampleMode);
    record.setValue(F_SPECIESMODE, sampleInfo.modes.speciesMode);
    record.setValue(F_BLOODMODE, sampleInfo.modes.bloodMode);
    record.setValue(F_ANALYSISMODE, sampleInfo.modes.analysisMode);
    record.setValue(F_PREPROCESSMODE, sampleInfo.modes.preprocessMode);
    record.setValue(F_WORKMODE, sampleInfo.modes.workMode);

    record.setValue(F_SENDER, sampleInfo.sender);
    record.setValue(F_SEND_TIME, sampleInfo.sendTime);
    record.setValue(F_TESTER, sampleInfo.tester);
    record.setValue(F_TEST_TIME, sampleInfo.testTime);
    record.setValue(F_CHECKER, sampleInfo.checker);
    record.setValue(F_CHECK_TIME, sampleInfo.checkTime);

    record.setValue(F_PID, sampleInfo.patientId);
    record.setValue(F_NAME, sampleInfo.name);
    record.setValue(F_GENDER, sampleInfo.gender);
    record.setValue(F_AGE, sampleInfo.age);
    record.setValue(F_DEPARTMENT, sampleInfo.department);
    record.setValue(F_BED_NO, sampleInfo.bedNo);
    record.setValue(F_COMMENT, sampleInfo.comment);
}

// 参数结果
void SampleTable::getParaResult(ParaList& paraResult, const QSqlRecord& record)
{
    QStringList paraNames = Paras::reportParaNames();
    foreach (QString paraName, paraNames)
    {
        QString field = "F_" + this->paraFieldName(paraName);

        float value = record.value(field).toFloat();
        int flag = record.value(field + "_FLAG").toInt();
        QString unit = ParaUnit::paraUnit(paraName);

        paraResult.appendPara(paraName, value, flag, unit);
    }
}

void SampleTable::setParaResult(QSqlRecord& record, const ParaList& paraResult)
{
    QStringList paraNames = Paras::reportParaNames();
    foreach (QString paraName, paraNames)
    {
        Para para = paraResult.para(paraName);
        QString field = "F_" + this->paraFieldName(paraName);

        record.setValue(field, para.value);
        record.setValue(field + "_FLAG", para.flag);
    }
}

// 参考范围下限
void SampleTable::getLowLimit(ParaList& lowLimits, const QSqlRecord& record)
{
    QStringList paras = Paras::reportParaNames();
    foreach (QString para, paras)
    {
        QString field = "F_" + this->paraFieldName(para) + "_LOW";
        lowLimits.appendPara(para, record.value(field).toFloat(), PARA_NORMAL_FLAG, ParaUnit::paraUnit(para));
    }
}

void SampleTable::setLowLimit(QSqlRecord& record, const ParaList& lowLimits)
{
    QStringList paras = Paras::reportParaNames();
    foreach (QString para, paras)
    {
        QString field = "F_" + this->paraFieldName(para) + "_LOW";
        record.setValue(field, lowLimits.paraValue(para));
    }
}

// 参考范围上限
void SampleTable::getHighLimit(ParaList& highLimits, const QSqlRecord& record)
{
    QStringList paras = Paras::reportParaNames();
    foreach (QString para, paras)
    {
        QString field = "F_" + this->paraFieldName(para) + "_HIGH";
        highLimits.appendPara(para, record.value(field).toFloat(), PARA_NORMAL_FLAG, ParaUnit::paraUnit(para));
    }
}

void SampleTable::setHighLimit(QSqlRecord& record, const ParaList& highLimits)
{
    QStringList paras = Paras::reportParaNames();
    foreach (QString para, paras)
    {
        QString field = "F_" + this->paraFieldName(para) + "_HIGH";
        record.setValue(field, highLimits.paraValue(para));
    }
}

// 直方图数据
void SampleTable::getHistInfo(HistInfo& wbcHist, HistInfo& rbcHist, HistInfo& pltHist, const QSqlRecord& record)
{
    // WBC直方图数据
    {
        wbcHist.clear();

        // 直方图
        QByteArray byteArray = record.value(F_WBC_HIST).toByteArray();

        wbcHist.dataLen = qMin<int>(byteArray.length(), Max_Hist_DataLen);
        for (int i = 0; i < wbcHist.dataLen; i++)
        {
            wbcHist.datas[i] = (unsigned char)byteArray.at(i);
        }

        // 分类线
        byteArray = record.value(F_WBC_LINE).toByteArray();

        wbcHist.lineLen = qMin<int>(byteArray.length(), Max_Hist_LineLen);
        for (int i = 0; i < wbcHist.lineLen; i++)
        {
            wbcHist.lines[i] = (unsigned char)byteArray.at(i);
        }
    }

    // RBC直方图数据
    {
        rbcHist.clear();

        // 直方图
        QByteArray byteArray = record.value(F_RBC_HIST).toByteArray();

        rbcHist.dataLen = qMin<int>(byteArray.length(), Max_Hist_DataLen);
        for (int i = 0; i < rbcHist.dataLen; i++)
        {
            rbcHist.datas[i] = (unsigned char)byteArray.at(i);
        }

        // 分类线
        byteArray = record.value(F_RBC_LINE).toByteArray();

        rbcHist.lineLen = qMin<int>(byteArray.length(), Max_Hist_LineLen);
        for (int i = 0; i < rbcHist.lineLen; i++)
        {
            rbcHist.lines[i] = (unsigned char)byteArray.at(i);
        }
    }

    // PLT直方图数据
    {
        pltHist.clear();

        // 直方图
        QByteArray byteArray = record.value(F_PLT_HIST).toByteArray();

        pltHist.dataLen = qMin<int>(byteArray.length(), Max_Hist_DataLen);
        for (int i = 0; i < pltHist.dataLen; i++)
        {
            pltHist.datas[i] = (unsigned char)byteArray.at(i);
        }

        // 分类线
        byteArray = record.value(F_PLT_LINE).toByteArray();

        pltHist.lineLen = qMin<int>(byteArray.length(), Max_Hist_LineLen);
        for (int i = 0; i < pltHist.lineLen; i++)
        {
            pltHist.lines[i] = (unsigned char)byteArray.at(i);
        }
    }
}
