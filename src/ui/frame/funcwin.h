#ifndef _FUNC_WIN_H_
#define _FUNC_WIN_H_


#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class ReagentWidget;


// ���ܽ��棨�������в����ײ�״̬����
class FuncWin : public QWidget
{
    Q_OBJECT

public:
    FuncWin(QWidget* parent = 0);
    virtual ~FuncWin();

    // ���ڱ�ʶ
    QString wId() const;
    void setWId(const QString& wId);

    // ����������
    virtual void onAbsorbKeyDown();

signals:
    // �л������ܴ���
    void toFuncWin(FuncWin* funcWin);

protected:
    // �����ַ���
    virtual void setWindowText();

    // ����״̬��
    virtual void createStatusBar();

    // ����ʹ��
    virtual void enableWindow(bool enable);
    // ������ʹ��
    virtual void enableAbsorbKey(bool enable);

    // ����ʱ��ʧ�ܴ���
    virtual void onRunTimeseqFail(int ret);

    // �л������ܴ���
    virtual void switchToFuncWin(FuncWin* funcWin);

protected:
    // �����ַ���
    virtual QString getString(const QString& ids);

    virtual void setText(QLabel* widget, const QString& ids);
    virtual void setText(QLineEdit* widget, const QString& ids);
    virtual void setText(QAbstractButton* widget, const QString& ids);

private slots:
    // ��ť���
    void onBtnMenuClicked();
    void onBtnFaultClicked();
    void onReagentWidgetClicked();

    // ���ϱ仯
    void onFaultChanged(const QList<int>& faults);

protected:
    // ���ڱ�ʶ
    QString winId;

    // ����״̬��
    QLabel* lbLogo; // LOGO��ǩ
    QPushButton* pbMenu; // �˵���ť

    // �ײ�״̬��
    QPushButton* pbFault; // ��ǰ����
    ReagentWidget* reagentWidget; // �Լ�״̬
};


#endif // _FUNC_WIN_H_
