#ifndef _APPLICATION_H_
#define _APPLICATION_H_


#include <QApplication>


// 应用程序
class Application : public QApplication
{
    Q_OBJECT

public:
    Application(int& argc, char** argv);
    ~Application();

    // 初始化
    void init();

private:
    // LOG初始化
    void logInit();

    // HAL初始化
    void halInit();

    // CONFIG初始化
    void configInit();

    // TIMESEQ初始化
    void timeseqInit();

    // COMMON初始化
    void commonInit();

    // REAGENT初始化
    void reagentInit();

    // DATABASE初始化
    void databaseInit();

    // LANGUAGE初始化
    void languageInit();
};


#endif // _APPLICATION_H_