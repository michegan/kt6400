#include "mode.h"


namespace Mode
{
    // �Ƿ����CBCģʽ
    bool hasCbcMode(int am)
    {
        return (am & CBC_MODE);
    }

    // �Ƿ����DIFFģʽ
    bool hasDiffMode(int am)
    {
        return (am & DIFF_MODE);
    }

    // �Ƿ����CRPģʽ
    bool hasCrpMode(int am)
    {
        return (am & CRP_MODE);
    }
}
