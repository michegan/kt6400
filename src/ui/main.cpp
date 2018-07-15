#include <QtDebug>
#include <QApplication>

#include "mainwindow.h"
#include "application.h"
#include "reviewsampletable.h"


int main(int argc, char *argv[])
{
    Application app(argc, argv);
    app.init();

    // �����ع���������
    ReviewSampleTable::createInstance();

    // ������
    MainWindow mainWindow;
    mainWindow.show();

    // ��Ϣѭ��
    return app.exec();
}
