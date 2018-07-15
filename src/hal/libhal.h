#ifndef _LIB_HAL_H_
#define _LIB_HAL_H_


#include <QtCore/QtGlobal>


#ifdef HAL_LIB
    #define HAL_EXPORT Q_DECL_EXPORT
#else
    #define HAL_EXPORT Q_DECL_IMPORT
#endif


#endif // _LIB_HAL_H_