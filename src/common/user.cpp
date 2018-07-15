#include <QtDebug>

#include "user.h"


User::User()
    : userName(""), password(""), userLevel(USER_NORMAL), fullName("")
{

}

User::~User(void)
{

}

// 是否管理员以上级别
bool User::isAdmin() const
{
    return (USER_ADMIN <= this->userLevel);
}

// 是否用服以上级别
bool User::isService() const
{
    return (USER_SERVICE <= this->userLevel);
}

// 是否生产以上级别
bool User::isManufactor() const
{
    return (USER_MANUFACTOR <= this->userLevel);
}

// 是否研发以上级别
bool User::isDeveloper() const
{
    return (USER_DEVELOPER <= this->userLevel);
}

// 是否特定级别用户
bool User::isLevelUer(int userLevel) const
{
    return (this->userLevel == userLevel);
}


// 特殊用户列表
QList<User> User::specialUsers()
{
    User user;
    QList<User> users;

    // 客服
    user.userName = "Service";
    user.password = "service";
    user.userLevel = USER_SERVICE;
    users.append(user);

    // 生产
    user.userName = "Product";
    user.password = "product";
    user.userLevel = USER_MANUFACTOR;
    users.append(user);

    // 研发
    user.userName = "Develop";
    user.password = "develop";
    user.userLevel = USER_DEVELOPER;
    users.append(user);

    return users;
}
