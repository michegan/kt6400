
#ifndef _QEXTSERIALPORT_H_
#define _QEXTSERIALPORT_H_

/*MS WINDOWS CODE*/
#ifdef _WIN32
#include "win_qextserialport.h"
#define QextBaseType Win_QextSerialPort
/*POSIX CODE*/
#else
#include "posix_qextserialport.h"
#define QextBaseType Posix_QextSerialPort
#endif

class QEXTSERIALPORT_EXPORT QextSerialPort: public QextBaseType {
public:
    QextSerialPort();
    QextSerialPort(const QString & name);
    QextSerialPort(PortSettings const& s);
    QextSerialPort(const QString & name, PortSettings const& s);
    QextSerialPort(const QextSerialPort& s);
    QextSerialPort& operator=(const QextSerialPort&);
    virtual ~QextSerialPort();
};

#endif
