#ifndef _LIB_TRANSMIT_H_
#define _LIB_TRANSMIT_H_


#include <QtCore/QtGlobal>


#ifdef TRANSMIT_LIB
    #define TRANSMIT_EXPORT Q_DECL_EXPORT
#else
    #define TRANSMIT_EXPORT Q_DECL_IMPORT
#endif


#endif // _LIB_TRANSMIT_H_