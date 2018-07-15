#ifndef _LIB_COMMON_H_
#define _LIB_COMMON_H_


#include <QtCore/QtGlobal>


#ifdef COMMON_LIB
    #define COMMON_EXPORT Q_DECL_EXPORT
#else
    #define COMMON_EXPORT Q_DECL_IMPORT
#endif


#endif // _LIB_COMMON_H_