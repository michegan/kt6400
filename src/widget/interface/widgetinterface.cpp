#include "widgetinterface.h"


WidgetInterface::WidgetInterface(const QString& name, QObject* parent)
    : QObject(parent), className(name)
{

}

WidgetInterface::~WidgetInterface()
{

}

// �ؼ���Designer����ʾ��ͼ��
QIcon WidgetInterface::icon() const
{
    return QIcon();
}

// �ؼ���Designer����ʾ������
QString WidgetInterface::name() const
{
    return this->className;
}

// �ؼ���Designer�����ڵ�������
QString WidgetInterface::group() const
{
    return "Widgets";
}

// �ؼ���.ui�ļ��е�Ĭ������
QString WidgetInterface::domXml() const
{
    return QDesignerCustomWidgetInterface::domXml();
}

// �ؼ���Designer���������ʱ����ʾ��Ϣ
QString WidgetInterface::toolTip() const
{
    return "";
}

QString WidgetInterface::whatsThis() const
{
    return "";
}

// �ؼ��Ƿ���һ��������ؼ������԰��������ؼ�
bool WidgetInterface::isContainer() const
{
    return false;
}