#ifndef _LJ_QC_SETUP_WIN_
#define _LJ_QC_SETUP_WIN_


#include "para.h"
#include "ljqcinfo.h"
#include "setupfuncwin.h"
#include "ui_ljqcsetupwin.h"

class LJQcFileTable;


// LJ�ʿ����ý���
class LJQcSetupWin : public SetupFuncWin
{
    Q_OBJECT

public:
    LJQcSetupWin(QWidget* parent = 0);
    virtual ~LJQcSetupWin();

protected:
    // ����״̬��
    virtual void createStatusBar();

protected:
    // �ӽ����ȡ������Ϣ
    virtual void getSetupInfoFromUI();

    // ������Ϣ�Ƿ�仯
    virtual bool isSetupInfoChanged();

    // ������Ϣ��Ч�Լ�⣨��Ч����0����Ч���ض�Ӧ�����룩
    virtual QString isSetupInfoValid();

    // ������Ϣ��Ч������ʾ��Ϣ��
    virtual QString onSetupInfoInvalidText(const QString& ret);
    virtual QWidget* onSetupInfoInvalidWidget(const QString& ret);

    // ������Ϣ��Ч��������������Ϣ��
    virtual bool onSetupInfoValid();

private slots:
    // ��ť���
    void onBtnBackClicked();

private:
    // �ļ���
    int fileNo;

    // �ʿ���Ϣ
    LJQcInfo ljQcInfoPre;
    LJQcInfo ljQcInfoPost;

    // �ʿ�������
    ParaList lowLimitsPre;
    ParaList highLimitsPre;

    ParaList lowLimitsPost;
    ParaList highLimitsPost;

    // �ײ�״̬��
    QLabel* lbFileNo;
    QLabel* leFileNo;

    Ui::LJQcSetupWin ui;

    // �ļ���
    LJQcFileTable* fileTable;

    // �༭��
    QMap<QString, DigitLineEdit*> lowEdits;
    QMap<QString, DigitLineEdit*> highEdits;
};


#endif // _LJ_QC_SETUP_WIN_
