#ifndef _LIB_DATATABLE_H_
#define _LIB_DATATABLE_H_


#include <QtCore/QtGlobal>


#ifdef DATATABLE_LIB
    #define DATATABLE_EXPORT Q_DECL_EXPORT
#else
    #define DATATABLE_EXPORT Q_DECL_IMPORT
#endif


#endif // _LIB_DATATABLE_H_