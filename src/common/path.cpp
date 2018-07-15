#include "path.h"


namespace Path
{
    // ��Ŀ¼
    static QString s_rootPath = "./";

    QString rootPath()
    {
        return s_rootPath;
    }

    void setRootPath(const QString& path)
    {
        s_rootPath = path;
    }

    // �㷨�ļ�·��
    QString algFilePath()
    {
        return rootPath() + "alg/";
    }

    // �����ļ�·��
    QString datFilePath()
    {
        return rootPath() + "dat/";
    }

    // �����ļ�·��
    QString faultFilePath()
    {
        return rootPath() + "fault/";
    }

    // �����ļ�·��
    QString configFilePath()
    {
        return rootPath() + "config/";
    }

    // Ĭ���ļ�·��
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

    // ����Ĭ���ļ�·��
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

    // ʱ���ļ�·��
    QString timeseqFilePath()
    {
        return rootPath() + "timeseq/";
    }
}
