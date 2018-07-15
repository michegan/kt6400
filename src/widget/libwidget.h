#ifndef _LIB_WIDGET_H_
#define _LIB_WIDGET_H_


#include <QtCore/QtGlobal>


#ifdef WIDGET_LIB
    #define WIDGET_EXPORT Q_DECL_EXPORT
#else
    #define WIDGET_EXPORT Q_DECL_IMPORT
#endif


#endif // _LIB_WIDGET_H_