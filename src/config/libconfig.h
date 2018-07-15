#ifndef _LIB_CONFIG_H_
#define _LIB_CONFIG_H_


#include <QtCore/QtGlobal>


#ifdef CONFIG_LIB
    #define CONFIG_EXPORT Q_DECL_EXPORT
#else
    #define CONFIG_EXPORT Q_DECL_IMPORT
#endif


#endif // _LIB_CONFIG_H_