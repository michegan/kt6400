#ifndef _LIB_LANGUAGE_H_
#define _LIB_LANGUAGE_H_


#include <QtCore/QtGlobal>


#ifdef LANGUAGE_LIB
    #define LANGUAGE_EXPORT Q_DECL_EXPORT
#else
    #define LANGUAGE_EXPORT Q_DECL_IMPORT
#endif


#endif // _LIB_LANGUAGE_H_