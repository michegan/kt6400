#ifndef _PROXY_STYPE_H_
#define _PROXY_STYPE_H_


#include <QProxyStyle>


// ί����ʽ
class ProxyStyle : public QProxyStyle
{
public:
    ProxyStyle();
    virtual ~ProxyStyle();

    // ��ʽ����
    virtual int styleHint(StyleHint hint, const QStyleOption* option = 0, const QWidget* widget = 0, QStyleHintReturn* returnData = 0) const;
};


#endif // _PROXY_STYPE_H_