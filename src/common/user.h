#ifndef _USER_H_
#define _USER_H_


#include <QString>

#include "libcommon.h"


// 进样模式
enum USER_LEVEL
{
    USER_NORMAL = 1,      // 普通用户
    USER_ADMIN,           // 管理员
    USER_SERVICE,         // 用服
    USER_MANUFACTOR,      // 生产 
    USER_DEVELOPER,       // 研发
};


// 用户
class COMMON_EXPORT User
{
public:
    User();
    virtual ~User();

    // 是否管理员以上级别
    bool isAdmin() const;

    // 是否用服以上级别
    bool isService() const;

    // 是否生产以上级别
    bool isManufactor() const;

    // 是否研发以上级别
    bool isDeveloper() const;

    // 是否特定级别用户
    bool isLevelUer(int userLevel) const;

public:
    // 特殊用户列表
    static QList<User> specialUsers();

public:
    // 用户名
    QString userName;

    // 密码
    QString password;

    // 用户姓名
    QString fullName;

    // 用户级别
    int userLevel;
};


#endif // _USER_H_