#include <QtCore/QtPlugin>

#include "widgetinterfaces.h"
#include "lineeditinterface.h"


WidgetInterfaces::WidgetInterfaces(QObject* parent)
    : QObject(parent)
{
    // ±à¼­¿ò
    this->widgets.append(new LineEditInterface(this));
    this->widgets.append(new IpLineEditInterface(this));
    this->widgets.append(new DateLineEditInterface(this));
    this->widgets.append(new TimeLineEditInterface(this));
    this->widgets.append(new DigitLineEditInterface(this));
    this->widgets.append(new SampleIdLineEditInterface(this));
}

WidgetInterfaces::~WidgetInterfaces()
{

}

// ¿Ø¼þÁÐ±í
QList<QDesignerCustomWidgetInterface*> WidgetInterfaces::customWidgets() const
{
    return this->widgets;
}


Q_EXPORT_PLUGIN(WidgetInterfaces)