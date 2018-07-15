#ifndef _USER_TABLE_H_
#define _USER_TABLE_H_


#include "datatable.h"
#include "libdatatable.h"


// 用户相关数据表
class DATATABLE_EXPORT UserTable : public DataTable
{
public:
    UserTable();
    virtual ~UserTable();

    // 用户列表
    QList<int> users();

    // 用户信息
    QList<int> fids(const QString& userName);

    // 用户信息
    bool user(int fid, QString& userName, QString& fullName, QString& password, int& level);

    // 新增用户
    bool insertUser(int& fid, const QString& userName, const QString& fullName, const QString& password, int level);

    // 删除用户
    bool deleteUser(int fid);

    // 更改用户信息
    bool updateUser(int fid, const QString& userName, const QString& fullName, const QString& password, int level);
};


#endif // _USER_TABLE_H_