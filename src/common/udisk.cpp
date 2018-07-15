#include "udisk.h"
#include "utility.h"


// Uел
namespace UDisk
{
    // ╧рть
    bool mount()
    {
        return Utility::runAppScript("script/mountUdisk.sh");
    }

    // п╤ть
    bool unmount()
    {
        return Utility::runAppScript("script/umountUdisk.sh");;
    }
}