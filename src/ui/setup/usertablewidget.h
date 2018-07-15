#ifndef _USER_TABLE_WIDGET_H_
#define _USER_TABLE_WIDGET_H_


#include "user.h"
#include "tablewidget.h"


// 用户表格控件
class UserTableWidget : public TableWidget
{
    Q_OBJECT

public:
    UserTableWidget(QWidget* parent = 0);
    virtual ~UserTableWidget();

    // 用户列表
    void setUsers(const QList<User>& users);

protected:
    // 获取表头内容
    virtual QStringList headText() const;

    // 获取表格内容
    virtual int numOfItems();
    virtual QStringList rowText(int row);

private:    
    // 用户列表
    QList<User> users;
};


#endif // _USER_TABLE_WIDGET_H_