#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_


#include <QTimer>
#include <QDialog>

class FuncWin;


// ������
class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = 0);
    virtual ~MainWindow();

protected:
    // ������Ӧ
    virtual void keyPressEvent(QKeyEvent* event);

private slots:
    // ��ʱ����ʱ
    void onTimerOut();

    // �л������ܴ���
    void onSwitchToFuncWin(FuncWin* funcWin);

private:
    // �Ƿ���Ӧ������
    bool isAbsorbKeyEnabled() const;

private:
    // ��ʱ��
    QTimer* timer;

    // ���ܴ���
    FuncWin* funcWin;
};


#endif // _MAIN_WINDOW_H_
