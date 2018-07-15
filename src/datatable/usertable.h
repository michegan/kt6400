#ifndef _USER_TABLE_H_
#define _USER_TABLE_H_


#include "datatable.h"
#include "libdatatable.h"


// �û�������ݱ�
class DATATABLE_EXPORT UserTable : public DataTable
{
public:
    UserTable();
    virtual ~UserTable();

    // �û��б�
    QList<int> users();

    // �û���Ϣ
    QList<int> fids(const QString& userName);

    // �û���Ϣ
    bool user(int fid, QString& userName, QString& fullName, QString& password, int& level);

    // �����û�
    bool insertUser(int& fid, const QString& userName, const QString& fullName, const QString& password, int level);

    // ɾ���û�
    bool deleteUser(int fid);

    // �����û���Ϣ
    bool updateUser(int fid, const QString& userName, const QString& fullName, const QString& password, int level);
};


#endif // _USER_TABLE_H_