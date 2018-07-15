#ifndef _LIB_SERIAL_H_
#define _LIB_SERIAL_H_


#include <QtCore/QtGlobal>


#ifdef QEXTSERIALPORT_LIB
    #define QEXTSERIALPORT_EXPORT Q_DECL_EXPORT
#else
    #define QEXTSERIALPORT_EXPORT Q_DECL_IMPORT
#endif


#endif // _LIB_SERIAL_H_