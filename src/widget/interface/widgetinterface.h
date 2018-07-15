#ifndef _WIDGET_INTERFACE_H_
#define _WIDGET_INTERFACE_H_


#include <QDesignerCustomWidgetInterface>


// DM�Զ���ؼ�
class WidgetInterface : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    WidgetInterface(const QString& className, QObject* parent = 0);
    virtual ~WidgetInterface();

    // �ؼ���Designer����ʾ��ͼ��
    virtual QIcon icon() const;

    // �ؼ���Designer����ʾ������
    virtual QString name() const;

    // �ؼ���Designer�����ڵ�������
    virtual QString group() const;

    // �ؼ���.ui�ļ��е�Ĭ������
    virtual QString domXml() const;

    // �ؼ���Designer���������ʱ����ʾ��Ϣ
    virtual QString toolTip() const;
    virtual QString whatsThis() const;

    // �ؼ��Ƿ���һ��������ؼ������԰��������ؼ�
    virtual bool isContainer() const;

private:
    // ����
    QString className;
};


// ���ɿؼ��ӿ���
#define DECLARE_WIDGET_INTERFACE(WidgetName) \
\
class WidgetName##Interface : public WidgetInterface \
{ \
    Q_INTERFACES(QDesignerCustomWidgetInterface) \
\
public: \
    WidgetName##Interface(QObject* parent = 0); \
    virtual ~WidgetName##Interface(); \
\
    virtual QString includeFile() const; \
\
    virtual QWidget* createWidget(QWidget* parent); \
};


// ʵ�ֿؼ��ӿ���
#define IMPLEMENT_WIDGET_INTERFACE(WidgetName, IncludeFile) \
\
WidgetName##Interface::WidgetName##Interface(QObject* parent) : WidgetInterface(#WidgetName, parent) \
{ \
\
} \
\
WidgetName##Interface::~WidgetName##Interface() \
{ \
    \
} \
\
QString WidgetName##Interface::includeFile() const \
{ \
    return (IncludeFile); \
} \
\
QWidget* WidgetName##Interface::createWidget(QWidget* parent) \
{ \
    return new WidgetName(parent); \
}


#endif // _WIDGET_INTERFACE_H_