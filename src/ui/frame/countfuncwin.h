#ifndef _COUNT_FUNC_WIN_H_
#define _COUNT_FUNC_WIN_H_


#include "funcwin.h"
#include "sampleinfo.h"

class NextSampleTable;


// ֧�ּ����Ĺ��ܽ���
class CountFuncWin : public FuncWin
{
    Q_OBJECT

public:
    CountFuncWin(QWidget* parent = 0);
    virtual ~CountFuncWin();

    // ��һ������Ϣ
    SampleInfo getNextSampleInfo() const;
    void setNextSampleInfo(const SampleInfo& sampleInfo);

protected:
    // ����״̬��
    virtual void createStatusBar();

    // ����ʹ��
    virtual void enableWindow(bool enable);

    // ��ʾ��һ������Ϣ
    virtual void showNextSampleInfo(const SampleInfo& sampleInfo);

private slots:
    // ��ť���
    void onBtnModeClicked();
    void onBtnSpeciesClcked();

private:
    // �ײ�״̬��
    QPushButton* pbNextSpecies;
    QPushButton* pbNextSampleMode;

    // ��һ������Ϣ
    SampleInfo* nextSampleInfo;
    // ��һ�������ݱ�
    NextSampleTable* nextSampleTable;
};


#endif // _COUNT_FUNC_WIN_H_
