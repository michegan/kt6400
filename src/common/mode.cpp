#include "mode.h"


namespace Mode
{
    // 是否包含CBC模式
    bool hasCbcMode(int am)
    {
        return (am & CBC_MODE);
    }

    // 是否包含DIFF模式
    bool hasDiffMode(int am)
    {
        return (am & DIFF_MODE);
    }

    // 是否包含CRP模式
    bool hasCrpMode(int am)
    {
        return (am & CRP_MODE);
    }
}
