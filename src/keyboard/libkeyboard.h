#ifndef _LIB_KEYBOARD_H_
#define _LIB_KEYBOARD_H_


#include <QtCore/QtGlobal>


#ifdef KEYBOARD_LIB
    #define KEYBOARD_EXPORT Q_DECL_EXPORT
#else
    #define KEYBOARD_EXPORT Q_DECL_IMPORT
#endif


#endif // _LIB_KEYBOARD_H_