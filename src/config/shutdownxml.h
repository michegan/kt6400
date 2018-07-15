#ifndef _SHUTDOWN_XML_H_
#define _SHUTDOWN_XML_H_


#include <QDateTime>

#include "xml.h"
#include "libconfig.h"


// KEY1�ؼ���
#define KEY1_SHUTDOWN               ("SHUTDOWN")

// KEY2�ؼ���
#define KEY2_SHUTDOWN_TYPE          ("SHUTDOWN_TYPE")
#define KEY2_SHUTDOWN_TIME          ("SHUTDOWN_TIME")

#define VALUE_SHUTDOWN_NORMAL       ("SHUTDOWN_NORMAL")
#define VALUE_SHUTDOWN_ABNORMAL     ("SHUTDOWN_ABNORMAL")
#define VALUE_SHUTDOWN_PACKAGE      ("SHUTDOWN_PACKAGE")


// �ػ���Ϣ�����ļ�����
class CONFIG_EXPORT ShutdownXml : public Xml
{
public:
    ShutdownXml();
    ShutdownXml(const QString& fileName);
    ~ShutdownXml();

    // �ػ�ʱ��
    QDateTime getShutdownTime();
    bool setShutdownTime(const QDateTime& datetime);

private:
    // ����ʱ���ʽ
    QString datetimeFormat();
};


#endif // _SHUTDOWN_XML_H_