#ifndef _MODE_H_
#define _MODE_H_


#include <QList>
#include <QString>

#include <libcommon.h>


// 进样模式
enum SAMPLE_MODE
{
    OPEN_MODE = 0x01, // 开放进样
    AUTO_MODE = 0x02, // 自动进样
    CLOSE_MODE = 0x04, // 封闭进样
};

// 工作模式
enum WORK_MODE
{
    NORMAL_MODE = 0, // 正常计数
    QC_MODE, // 质控计数
    USER_CALIBRATE_MODE, // 校准计数（用户）
    FACTORY_CALIBRATE_MODE, // 校准计数（厂家）
    REPEAT_QC_MODE, // 重复性计数（质控）
    REPEAT_BLOOD_MODE, // 重复性计数（血样）
    AGING_MODE, // 老化计数
    SYS_BACKGROUND_MODE, // 本底计数（系统）
    USER_BACKGROUND_MODE, // 本底计数（用户）
    STANDARD_MODE, // 标粒模式
    GAIN_MODE, // 增益计数
    CARRYOVER_QC_MODE, // 携带污染计数（质控）
    CARRYOVER_BLOOD_MODE, // 携带污染计数（血样）
    CALIBRATE_CONFIRM_MODE, // 校准确认（质控）
    CAL_SCALING_MODE, // CRP标定

    WORK_MODE_RESERVE_1, // 保留
    WORK_MODE_RESERVE_2, // 保留
    WORK_MODE_RESERVE_3, // 保留
    WORK_MODE_RESERVE_4, // 保留
    WORK_MODE_RESERVE_5, // 保留
    WORK_MODE_RESERVE_6, // 保留
    WORK_MODE_RESERVE_7, // 保留
    WORK_MODE_RESERVE_8, // 保留
    WORK_MODE_RESERVE_9, // 保留
    WORK_MODE_RESERVE_10, // 保留
};

// 血样模式
enum BLOOD_MODE
{
    WHOLE_BLOOD_MODE = 0x01, // 全血模式
    PREDILUENT_MODE = 0x02, // 预稀释模式
    PERIPHERAL_MODE = 0x04, // 末梢血模式
};

// 分析模式
enum ANALYSIS_MODE
{
    CBC_MODE = 0x01, // CBC模式
    DIFF_MODE =0x02, // DIFF模式
    CRP_MODE = 0x04, // CRP 模式

    CBC_DIFF_MODE = (CBC_MODE | DIFF_MODE), // CBC-DIFF模式
    CBC_CRP_MODE = (CBC_MODE | CRP_MODE), // CBC_CRP模式
    CBC_DIFF_CRP_MODE = (CBC_DIFF_MODE | CRP_MODE), // CBC_DIFF_CRP模式
};


// 模式
namespace Mode
{
    // 是否包含CBC模式
    COMMON_EXPORT bool hasCbcMode(int am);

    // 是否包含DIFF模式
    COMMON_EXPORT bool hasDiffMode(int am);

    // 是否包含CRP模式
    COMMON_EXPORT bool hasCrpMode(int am);
};


#endif // _MODE_H_