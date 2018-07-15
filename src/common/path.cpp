#include "path.h"


namespace Path
{
    // 根目录
    static QString s_rootPath = "./";

    QString rootPath()
    {
        return s_rootPath;
    }

    void setRootPath(const QString& path)
    {
        s_rootPath = path;
    }

    // 算法文件路径
    QString algFilePath()
    {
        return rootPath() + "alg/";
    }

    // 数据文件路径
    QString datFilePath()
    {
        return rootPath() + "dat/";
    }

    // 故障文件路径
    QString faultFilePath()
    {
        return rootPath() + "fault/";
    }

    // 配置文件路径
    QString configFilePath()
    {
        return rootPath() + "config/";
    }

    // 默认文件路径
    QString defaultFilePath()
    {
        return rootPath() + "default/";
    }

    QString defaultDatFilePath()
    {
        return defaultFilePath() + "dat/";
    }

    QString defaultConfigFilePath()
    {
        return defaultFilePath() + "config/";
    }

    // 出厂默认文件路径
    QString factoryFilePath()
    {
        return rootPath() + "factory/";
    }

    QString factoryDatFilePath()
    {
        return factoryFilePath() + "dat/";
    }

    QString factoryConfigFilePath()
    {
        return factoryFilePath() + "config/";
    }

    // 时序文件路径
    QString timeseqFilePath()
    {
        return rootPath() + "timeseq/";
    }
}
