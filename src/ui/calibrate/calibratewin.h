#ifndef _CALIBRATE_WIN_H_
#define _CALIBRATE_WIN_H_


#include "para.h"
#include "modes.h"
#include "countfuncwin.h"

#include "ui_calibratewin.h"

class Count;
class CalibrateTableWidget;


// ������
class CalibrateWin : public CountFuncWin
{
    Q_OBJECT

public:
    CalibrateWin(QWidget* parent = 0);
    virtual ~CalibrateWin();

    // ����������
    virtual void onAbsorbKeyDown();

protected:
    // �����ַ���
    virtual void setWindowText();

    // ����״̬��
    virtual void createStatusBar();

    // ����ʹ��
    virtual void enableWindow(bool enable);

    // �л������ܴ���
    virtual void switchToFuncWin(FuncWin* funcWin);

private slots:
    // ��ť���
    void onBtnClearClicked();
    void onBtnSetupClicked();

    // �㷨����
    void onCountAlgFinished();
    // ��������
    void onCountFinished(bool result);

private:
    // �Ƿ�У׼��
    bool isCalibrating() const;
    // �Ƿ�У׼ͨ��
    bool isCalibrateOk() const;
    // �Ƿ�У׼����
    bool isCalibrateSetted() const;
    // �Ƿ�У׼����
    bool isCalibrateFinished() const;

    // ����У׼���
    bool saveCalibrateResult();

    // ��ʾУ׼������Ϣ
    void showCalibrateInfo(const QString& lotNo);
    // ��ʾУ׼�����Ϣ
    void showCalibrateResult(const ParaList& targets, const QList<ParaList>& results);

private:
    Ui::CalibrateWin ui;

    // ��������
    Count* count;

    // У׼������Ϣ
    QString lotNo;
    ParaList targets;

    // У׼�������
    QList<ParaList> results;

    // ����ϵ��
    ParaList cvs;
    // У׼ϵ�����
    ParaList factors;

    // У׼���
    CalibrateTableWidget* tableWidget;
};


#endif // _CALIBRATE_WIN_H_
