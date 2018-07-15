#ifndef _LJ_QC_FILE_TABLE_H_
#define _LJ_QC_FILE_TABLE_H_


#include "sampletable.h"


// LJ质控文件数据表
class DATATABLE_EXPORT LJQcFileTable : public SampleTable
{
public:
    LJQcFileTable();
    virtual ~LJQcFileTable();

    // 读取文件
    bool getFile(int fid, LJQcInfo& qcInfo, ParaList& lowLimits, ParaList& highLimits);

    // 更新文件
    bool updateFile(int fid, const LJQcInfo& qcInfo, const ParaList& lowLimits, const ParaList& highLimits);

    // 清空文件
    bool clearFile(int fid);
};


#endif // _LJ_QC_FILE_TABLE_H_