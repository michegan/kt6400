#include "widgetinterface.h"


WidgetInterface::WidgetInterface(const QString& name, QObject* parent)
    : QObject(parent), className(name)
{

}

WidgetInterface::~WidgetInterface()
{

}

// 控件在Designer中显示的图标
QIcon WidgetInterface::icon() const
{
    return QIcon();
}

// 控件在Designer中显示的名称
QString WidgetInterface::name() const
{
    return this->className;
}

// 控件在Designer中所在的组名称
QString WidgetInterface::group() const
{
    return "Widgets";
}

// 控件在.ui文件中的默认描述
QString WidgetInterface::domXml() const
{
    return QDesignerCustomWidgetInterface::domXml();
}

// 控件在Designer中鼠标悬浮时的提示信息
QString WidgetInterface::toolTip() const
{
    return "";
}

QString WidgetInterface::whatsThis() const
{
    return "";
}

// 控件是否是一个容器类控件，可以包容其他控件
bool WidgetInterface::isContainer() const
{
    return false;
}