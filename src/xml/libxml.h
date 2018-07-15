#ifndef _LIB_XML_H_
#define _LIB_XML_H_


#include <QtCore/QtGlobal>


#ifdef XML_LIB
    #define XML_EXPORT Q_DECL_EXPORT
#else
    #define XML_EXPORT Q_DECL_IMPORT
#endif


#endif // _LIB_XML_H_