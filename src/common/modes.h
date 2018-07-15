#ifndef _MODES_H_
#define _MODES_H_


#include <QList>
#include <QStringList>

#include <libcommon.h>


// 工作模式（在什么场景下进行的计数）
// 4 Bits（支持15种）
enum WORK_MODES
{
    WORK_MODE_NORMAL = 1, // 正常计数
    WORK_MODE_QC = 2, // 质控计数
    WORK_MODE_CALIBRATE = 3, // 校准计数
    WORK_MODE_AGING = 6, // 老化计数
    WORK_MODE_BACKGROUND = 7, // 本底计数
    WORK_MODE_GAIN = 10, // 增益计数

    MAX_WORK_MODE = 15, // 保留位
};

// 进样模式（样本进样方式）
// 3 Bits（支持7种）
enum SAMPLE_MODES
{
    SAMPLE_MODE_OPEN = 1, // 开放进样

    MAX_SAMPLE_MODE = 7, // 保留位
};

// 物种模式（测量对象所述物种）
// 5 Bits（支持31种）
enum SPECIES_MODES
{
    SPECIES_MODE_UNKNOWN = 1, // 未知
    SPECIES_MODE_HUMAN = 2, // 人
    SPECIES_MODE_CAT = 3, // 猫
    SPECIES_MODE_DOG = 4, // 狗
    SPECIES_MODE_MOUSE = 5, // 鼠
    SPECIES_MODE_RABBIT = 6, // 兔

    MAX_SPECIES_MODE = 31, // 保留位
};

// 血样模式（测量的对象是什么）
// 4 Bits（支持15种）
enum BLOOD_MODES
{
    BLOOD_MODE_WHOLE_BLOOD = 1, // 静脉全血
    BLOOD_MODE_PERIPHERAL = 2, // 末梢全血
    BLOOD_MODE_QC = 3, // 质控物
    BLOOD_MODE_CALIBRATE = 4, // 校准物
    BLOOD_MODE_BACKGROUND = 6, // 本底

    MAX_BLOOD_MODE = 15, // 保留位
};

// 分析模式（需要输出哪些参数）
// 8 Bits（或，支持255种）
enum ANALYSIS_MODES
{
    ANALYSIS_MODE_CBC = 0x01, // CBC模式
};

// 预处理方式
// 2 Bits（支持3种）
enum PREPROCESS_MODES
{
    PREPROCESS_MODE_NONE = 0, // 无预处理
    PREPROCESS_MODE_PREDILUENT = 1, // 机外预稀释

    MAX_PREPROCESS_MODE = 3, // 保留位
};

// 预留模式
// 6 Bits


// 模式
class COMMON_EXPORT Modes
{
public:
    Modes();
    virtual ~Modes();

    // 格式化
    QString ids() const;

    // 物种模式格式化
    QString specimodeIds() const;
    QString speciesImage() const;

public:
    // 工作模式
    quint8 workMode;
    // 进样模式
    quint8 sampleMode;
    // 物种模式
    quint8 speciesMode;
    // 血样模式
    quint8 bloodMode;
    // 分析模式
    quint8 analysisMode;
    // 预处理模式
    quint8 preprocessMode;
};


#endif // _MODES_H_