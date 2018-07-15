#include "proxystyle.h"


ProxyStyle::ProxyStyle()
{

}

ProxyStyle::~ProxyStyle()
{

}

// ��ʽ����
int ProxyStyle::styleHint(StyleHint hint, const QStyleOption* option, const QWidget* widget, QStyleHintReturn* returnData) const
{
    if (QStyle::SH_RequestSoftwareInputPanel == hint)
    {
        return QStyle::RSIP_OnMouseClick;
    }
    else
    {
        return QProxyStyle::styleHint(hint, option, widget, returnData);
    }
}