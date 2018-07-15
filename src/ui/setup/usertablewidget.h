#ifndef _USER_TABLE_WIDGET_H_
#define _USER_TABLE_WIDGET_H_


#include "user.h"
#include "tablewidget.h"


// �û����ؼ�
class UserTableWidget : public TableWidget
{
    Q_OBJECT

public:
    UserTableWidget(QWidget* parent = 0);
    virtual ~UserTableWidget();

    // �û��б�
    void setUsers(const QList<User>& users);

protected:
    // ��ȡ��ͷ����
    virtual QStringList headText() const;

    // ��ȡ�������
    virtual int numOfItems();
    virtual QStringList rowText(int row);

private:    
    // �û��б�
    QList<User> users;
};


#endif // _USER_TABLE_WIDGET_H_