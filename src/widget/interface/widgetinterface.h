#ifndef _WIDGET_INTERFACE_H_
#define _WIDGET_INTERFACE_H_


#include <QDesignerCustomWidgetInterface>


// DM自定义控件
class WidgetInterface : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    WidgetInterface(const QString& className, QObject* parent = 0);
    virtual ~WidgetInterface();

    // 控件在Designer中显示的图标
    virtual QIcon icon() const;

    // 控件在Designer中显示的名称
    virtual QString name() const;

    // 控件在Designer中所在的组名称
    virtual QString group() const;

    // 控件在.ui文件中的默认描述
    virtual QString domXml() const;

    // 控件在Designer中鼠标悬浮时的提示信息
    virtual QString toolTip() const;
    virtual QString whatsThis() const;

    // 控件是否是一个容器类控件，可以包容其他控件
    virtual bool isContainer() const;

private:
    // 类名
    QString className;
};


// 生成控件接口类
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


// 实现控件接口类
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