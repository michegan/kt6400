#ifndef _LIB_TIMESEQ_H_
#define _LIB_TIMESEQ_H_


#include <QtCore/QtGlobal>


#ifdef TIMESEQ_LIB
    #define TIMESEQ_EXPORT Q_DECL_EXPORT
#else
    #define TIMESEQ_EXPORT Q_DECL_IMPORT
#endif


#endif // _LIB_TIMESEQ_H_