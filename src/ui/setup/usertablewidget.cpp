#include <QPainter>

#include "language.h"
#include "usertablewidget.h"


UserTableWidget::UserTableWidget(QWidget* parent)
    : TableWidget(TableWidget::RowMode, parent)
{
    // 行列数
    this->setRows(20);
    this->setColumns(3);
}

UserTableWidget::~UserTableWidget()
{

}

// 用户列表
void UserTableWidget::setUsers(const QList<User>& users)
{
    this->users = users;

    // 刷新
    this->update();
}

// 获取表头内容
QStringList UserTableWidget::headText() const
{
    QStringList idses;
    idses << "IDS_USER_NAME" << "IDS_FULL_NAME" << "IDS_ADMINISTRATOR";

    QStringList heads;
    foreach (QString ids, idses)
    {
        heads.append(Language::getString(ids));
    }

    return heads;
}

// 获取表格内容
int UserTableWidget::numOfItems()
{
    return this->users.length();
}

QStringList UserTableWidget::rowText(int row)
{
    QStringList rowText;

    if (0 <= row && row < this->users.length())
    {
        const User& user = this->users[row];

        rowText.append(user.userName);
        rowText.append(user.fullName);

        QString ids = (user.isAdmin() ? "IDS_YES" : "IDS_NO");
        rowText.append(Language::getString(ids));
    }

    return rowText;
}