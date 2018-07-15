#ifndef _APPLICATION_H_
#define _APPLICATION_H_


#include <QApplication>


// Ӧ�ó���
class Application : public QApplication
{
    Q_OBJECT

public:
    Application(int& argc, char** argv);
    ~Application();

    // ��ʼ��
    void init();

private:
    // LOG��ʼ��
    void logInit();

    // HAL��ʼ��
    void halInit();

    // CONFIG��ʼ��
    void configInit();

    // TIMESEQ��ʼ��
    void timeseqInit();

    // COMMON��ʼ��
    void commonInit();

    // REAGENT��ʼ��
    void reagentInit();

    // DATABASE��ʼ��
    void databaseInit();

    // LANGUAGE��ʼ��
    void languageInit();
};


#endif // _APPLICATION_H_