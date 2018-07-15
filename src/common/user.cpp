#include <QtDebug>

#include "user.h"


User::User()
    : userName(""), password(""), userLevel(USER_NORMAL), fullName("")
{

}

User::~User(void)
{

}

// �Ƿ����Ա���ϼ���
bool User::isAdmin() const
{
    return (USER_ADMIN <= this->userLevel);
}

// �Ƿ��÷����ϼ���
bool User::isService() const
{
    return (USER_SERVICE <= this->userLevel);
}

// �Ƿ��������ϼ���
bool User::isManufactor() const
{
    return (USER_MANUFACTOR <= this->userLevel);
}

// �Ƿ��з����ϼ���
bool User::isDeveloper() const
{
    return (USER_DEVELOPER <= this->userLevel);
}

// �Ƿ��ض������û�
bool User::isLevelUer(int userLevel) const
{
    return (this->userLevel == userLevel);
}


// �����û��б�
QList<User> User::specialUsers()
{
    User user;
    QList<User> users;

    // �ͷ�
    user.userName = "Service";
    user.password = "service";
    user.userLevel = USER_SERVICE;
    users.append(user);

    // ����
    user.userName = "Product";
    user.password = "product";
    user.userLevel = USER_MANUFACTOR;
    users.append(user);

    // �з�
    user.userName = "Develop";
    user.password = "develop";
    user.userLevel = USER_DEVELOPER;
    users.append(user);

    return users;
}
