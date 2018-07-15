#ifndef _FLAG_H_
#define _FLAG_H_


// 参数标识
enum PARA_FLAG
{
    PARA_NORMAL_FLAG = 0x00, // 正常标识
    PARA_STAR_FLAG = 0x01, // **标识
    PARA_IGNORE_FLAG = 0x04, // 空标识

    PARA_ALARM_FLAG = 0x10, // 报警标识（确定性，可疑性）

    PARA_H_FLAG = 0x100, // H标识
    PARA_L_FLAG = 0x200, // L标识
    PARA_DOULT_FLAG = 0x400, // R标识
};


#endif // _FLAG_H_