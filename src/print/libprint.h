#ifndef _LIB_PRINT_H_
#define _LIB_PRINT_H_


#include <QtCore/QtGlobal>


#ifdef PRINT_LIB
    #define PRINT_EXPORT Q_DECL_EXPORT
#else
    #define PRINT_EXPORT Q_DECL_IMPORT
#endif


#endif // _LIB_PRINT_H_