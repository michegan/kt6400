#ifndef _LIB_LOG_H_
#define _LIB_LOG_H_


#include <QtCore/QtGlobal>


#ifdef LOG_LIB
    #define LOG_EXPORT Q_DECL_EXPORT
#else
    #define LOG_EXPORT Q_DECL_IMPORT
#endif


#endif // _LIB_LOG_H_