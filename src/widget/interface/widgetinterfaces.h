#ifndef _WIDGET_INTERFACES_H_
#define _WIDGET_INTERFACES_H_


#include <QDesignerCustomWidgetCollectionInterface>


// 自定义控件
class WidgetInterfaces : public QObject, public QDesignerCustomWidgetCollectionInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)

public:
    WidgetInterfaces(QObject *parent = 0);
    virtual ~WidgetInterfaces();

    virtual QList<QDesignerCustomWidgetInterface*> customWidgets() const;

private:
    QList<QDesignerCustomWidgetInterface*> widgets;
};


#endif // _WIDGET_INTERFACES_H_