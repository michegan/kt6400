#ifndef _LJ_QC_FILE_TABLE_H_
#define _LJ_QC_FILE_TABLE_H_


#include "sampletable.h"


// LJ�ʿ��ļ����ݱ�
class DATATABLE_EXPORT LJQcFileTable : public SampleTable
{
public:
    LJQcFileTable();
    virtual ~LJQcFileTable();

    // ��ȡ�ļ�
    bool getFile(int fid, LJQcInfo& qcInfo, ParaList& lowLimits, ParaList& highLimits);

    // �����ļ�
    bool updateFile(int fid, const LJQcInfo& qcInfo, const ParaList& lowLimits, const ParaList& highLimits);

    // ����ļ�
    bool clearFile(int fid);
};


#endif // _LJ_QC_FILE_TABLE_H_