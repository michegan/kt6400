#include <QtDebug>

#include "field.h"
#include "usertable.h"


UserTable::UserTable()
    : DataTable("T_USER")
{

}

UserTable::~UserTable()
{

}

// 用户列表
QList<int> UserTable::users()
{
    QList<int> fids;

    // 查询条件
    this->clearConditions();

    // 删除
    QSqlQuery query = this->selectRecord();
    while (query.next())
    {
        // 提取所需要的字段
        QSqlRecord record = query.record();
        fids.append(record.value(F_ID).toInt());
    }

    return fids;
}

// 用户信息
QList<int> UserTable::fids(const QString& userName)
{
    QList<int> fids;

    // 查询条件
    this->clearConditions();
    this->addAndCondition(F_USERNAME, userName);

    // 删除
    QSqlQuery query = this->selectRecord();
    while (query.next())
    {
        // 提取所需要的字段
        QSqlRecord record = query.record();

        int fid = record.value(F_ID).toInt();
        fids.append(fid);
    }

    return fids;
}

// 用户信息
bool UserTable::user(int fid, QString& userName, QString& fullName, QString& password, int& level)
{
    bool ret = false;

    // 查询上述条件记录（只应该查询到1条记录）
    QSqlQuery query = this->selectRecord(fid);
    if (query.next())
    {
        // 提取所需要的字段
        QSqlRecord record = query.record();

        userName = record.value(F_USERNAME).toString();
        fullName = record.value(F_FULLNAME).toString();
        password = record.value(F_PASSWORD).toString();
        level = record.value(F_USERLEVEL).toInt();

        ret = true;
    }

    return ret;
}

// 新增用户
bool UserTable::insertUser(int& fid, const QString& userName, const QString& fullName, const QString& password, int level)
{
    bool ret = false;

    do 
    {
        // 下一F_ID
        int nid = this->nextFid();
        if (nid <= 0)
        {
            break;
        }

        // 表对应记录
        QSqlRecord record = this->record();
        record.clearValues();

        // 更新需要更新的字段
        record.setValue(F_ID, nid);
        record.setValue(F_USERNAME, userName);
        record.setValue(F_FULLNAME, fullName);
        record.setValue(F_PASSWORD, password);
        record.setValue(F_USERLEVEL, level);

        // 执行对应SQL操作
        if (!this->insertRecord(record))
        {
            break;
        }

        ret = true;
        fid = nid;
    } while (0);

    return ret;
}

// 删除用户
bool UserTable::deleteUser(int fid)
{
    // 查询条件
    this->clearConditions();
    this->addAndCondition(F_ID, fid);

    // 删除记录
    return this->deleteRecord();
}

// 更改用户信息
bool UserTable::updateUser(int fid, const QString& userName, const QString& fullName, const QString& password, int level)
{
    bool ret = false;

    // 查询上述条件记录（只应该查询到1条记录）
    QSqlQuery query = this->selectRecord(fid);
    if (query.next())
    {
        // 更新需要更新的字段
        QSqlRecord record = query.record();

        record.setValue(F_USERNAME, userName);
        record.setValue(F_FULLNAME, fullName);
        record.setValue(F_PASSWORD, password);
        record.setValue(F_USERLEVEL, level);

        // 执行对应SQL操作
        ret = this->updateRecord(record);
    }

    return ret;
}