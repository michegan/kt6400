#include "udisk.h"
#include "utility.h"


// U��
namespace UDisk
{
    // ����
    bool mount()
    {
        return Utility::runAppScript("script/mountUdisk.sh");
    }

    // ж��
    bool unmount()
    {
        return Utility::runAppScript("script/umountUdisk.sh");;
    }
}