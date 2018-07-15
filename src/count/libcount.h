#ifndef _LIB_COUNT_H_
#define _LIB_COUNT_H_


#include <QtCore/QtGlobal>


#ifdef COUNT_LIB
    #define COUNT_EXPORT Q_DECL_EXPORT
#else
    #define COUNT_EXPORT Q_DECL_IMPORT
#endif


#endif // _LIB_COUNT_H_