#include <QtDebug>
#include <QApplication>

#include "mainwindow.h"
#include "application.h"
#include "reviewsampletable.h"


int main(int argc, char *argv[])
{
    Application app(argc, argv);
    app.init();

    // 创建回顾样本表单键
    ReviewSampleTable::createInstance();

    // 主界面
    MainWindow mainWindow;
    mainWindow.show();

    // 消息循环
    return app.exec();
}
