#ifndef _LIB_DATABASE_H_
#define _LIB_DATABASE_H_


#include <QtCore/QtGlobal>


#ifdef DATABASE_LIB
    #define DATABASE_EXPORT Q_DECL_EXPORT
#else
    #define DATABASE_EXPORT Q_DECL_IMPORT
#endif


#endif // _LIB_DATABASE_H_