#ifndef _LIB_ALG_H_
#define _LIB_ALG_H_


#include <QtCore/QtGlobal>


#ifdef ALG_LIB
    #define ALG_EXPORT Q_DECL_EXPORT
#else
    #define ALG_EXPORT Q_DECL_IMPORT
#endif


#endif // _LIB_ALG_H_