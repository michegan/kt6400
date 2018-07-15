#ifndef _USER_H_
#define _USER_H_


#include <QString>

#include "libcommon.h"


// ����ģʽ
enum USER_LEVEL
{
    USER_NORMAL = 1,      // ��ͨ�û�
    USER_ADMIN,           // ����Ա
    USER_SERVICE,         // �÷�
    USER_MANUFACTOR,      // ���� 
    USER_DEVELOPER,       // �з�
};


// �û�
class COMMON_EXPORT User
{
public:
    User();
    virtual ~User();

    // �Ƿ����Ա���ϼ���
    bool isAdmin() const;

    // �Ƿ��÷����ϼ���
    bool isService() const;

    // �Ƿ��������ϼ���
    bool isManufactor() const;

    // �Ƿ��з����ϼ���
    bool isDeveloper() const;

    // �Ƿ��ض������û�
    bool isLevelUer(int userLevel) const;

public:
    // �����û��б�
    static QList<User> specialUsers();

public:
    // �û���
    QString userName;

    // ����
    QString password;

    // �û�����
    QString fullName;

    // �û�����
    int userLevel;
};


#endif // _USER_H_