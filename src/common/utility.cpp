#include <QDir>
#include <QFile>
#include <QtDebug>
#include <QtGlobal>
#include <QProcess>
#include <QDateTime>
#include <QStringList>
#include <QtCore/qmath.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#include <errno.h>
#endif
#include "project.h"
#include "utility.h"


namespace Utility
{
    // 随机数
    int rand()
    {
        return qrand();
    }

    // 随机数播种
    void srand()
    {
        // 时间为种子
        QTime time(0, 0, 0);
        uint seed = time.msecsTo(QTime::currentTime());

        // 随机数播种
        Utility::srand(seed);
    }

    void srand(uint seed)
    {
        qsrand(seed);
    }

    // 生成GUID
    QString newGuid()
    {
        // 示例：20140226_132831_540
        QDateTime dateTime = QDateTime::currentDateTime();
        return dateTime.toString("yyyyMMdd_hhmmss_zzz");
    }

    // 浮点数格式化
    float format(float value, int dots)
    {
        float multi = qPow(10, dots + 1);

        // 转换为整形进行处理
        int nvalue = (int)(value * multi + 5);

        // 去掉尾数部分
        nvalue = (nvalue / 10) * 10;

        // 再回归到浮点数
        return nvalue / multi;
    }

    // 睡眠指定时间，屏蔽平台差异
    void ssleep(int secs)
    {
#ifdef _WIN32
        int msecs = 1000 * secs;
        Sleep(msecs);
#else
        sleep(secs);
#endif
    }

    // 睡眠指定时间，屏蔽平台差异
    void msleep(int msecs)
    {
#ifdef _WIN32
        Sleep(msecs);
#else
        usleep(msecs * 1000);
#endif
    }

    // 取指定字节
    quint8 lowerByte(qint16 value)
    {
        return (value & 0xFF);
    }

    quint8 lowerUByte(quint16 value)
    {
        return (value & 0xFF);
    }

    quint8 upperByte(qint16 value)
    {
        return ((value >> 8) & 0xFF);
    }

    quint8 upperUByte(quint16 value)
    {
        return ((value >> 8) & 0xFF);
    }

    quint8 getByte(int byte, qint32 value)
    {
        int offset = (4 - byte) * 8;
        return ((value >> offset) & 0xFF);
    }

    quint8 getUByte(int byte, quint32 value)
    {
        int offset = (4 - byte) * 8;
        return ((value >> offset) & 0xFF);
    }

    // 构造数值；
    quint16 toUShort(quint8 byte0, quint8 byte1)
    {
        return ((byte0 << 8) | byte1);
    }

    quint32 toUInt(quint8 byte0, quint8 byte1, quint8 byte2, quint8 byte3)
    {
        return ((byte0 << 24) | (byte1 << 16) | (byte2 << 8) | byte3);
    }

    // 计算校验和（所有数据按照int类型相加，如果溢出则让其溢出，如果长度非4的整数倍，则放弃后续多余字节）
    int checkSum(const char* dataBuffer, int dataLen)
    {
        int checkSum = 0;

        int size = dataLen / 4;
        int* p = (int*)dataBuffer;

        for (int i = 0; i < size; i++)
        {
            checkSum += *p;
            p++;
        }

        return checkSum;
    }

    // 读取文件数据
    char* getFileData(const QString& filename, int* fileLen)
    {
        QFile file(filename);
        char* dataBuffer = 0;

        do 
        {
            // 打开文件
            if (!file.open(QIODevice::ReadOnly))
            {
                break;
            }

            // 分配文件缓冲区，存储整个文件数据
            int size = file.size();
            dataBuffer = new char[size];
            if (0 == dataBuffer)
            {
                break;
            }
            memset(dataBuffer, 0, size);

            // 通过二进制流读取数据（脉冲粒子数+粒子数据）
            int len = file.read(dataBuffer, size);
            if (len != size)
            {
                break;
            }

            // 返回数据长度
            if (fileLen)
            {
                *fileLen = size;
            }
        } while (0);

        // 关闭文件
        file.close();

        return dataBuffer;
    }

    // 创建目录
    bool mkPath(const QString& path)
    {
        qDebug() << "Utility mkPath" << path;

        // 根据目录是否存在，创建目录
        QDir dir(path);
        return (dir.exists() ? true : dir.mkpath("."));
    }

    // 删除目录（含目录自身）
    bool rmPath(const QString& path)
    {
        // 清空目录（不删除目录自身）
        if (Utility::clearPath(path))
        {
            // 删除目录自身
            QDir dir(path);
            QString dirName = dir.dirName();

            dir.cdUp();
            return dir.rmdir(dirName);
        }
        else
        {
            return false;
        }
    }

    // 清空目录（不删除目录自身）
    bool clearPath(const QString& path)
    {
        qDebug() << "Utility clearPath" << path;

        QDir dir(path);
        if (!dir.exists())
        {
            return false;
        }

        // 删除所有子目录及子文件
        QFileInfoList fileInfoList = dir.entryInfoList();
        foreach(QFileInfo fileInfo, fileInfoList)
        {
            if (fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            {
                continue;
            }

            // 删除子目录
            if (fileInfo.isDir())
            {
                // 递归删除子目录
                QString subPath = path + fileInfo.fileName() + ("/");
                if (!Utility::clearPath(subPath))
                {
                    return false;
                }

                // 删除子目录
                if (!dir.rmdir(fileInfo.fileName()))
                {
                    return false;
                }
            }
            // 删除子文件
            else if(fileInfo.isFile())
            {
                if (!dir.remove(fileInfo.fileName()))
                {
                    return false;
                }
            }
            else
            {
                // 不做任何处理
            }
        }

        return true;
    }

    // 拷贝目录
    bool cpPath(const QString& srcPath, const QString& destPath)
    {
        QDir srcDir(srcPath);
        QDir destDir(destPath);

        qDebug() << "Utility cpPath" << srcPath << destPath;

        // 目录是否存在检测
        if (!srcDir.exists() || !destDir.exists())
        {
            qWarning() << "Utility cpPath no dir";
            return false;
        }

        // 拷贝所有子文件
        QStringList files = srcDir.entryList(QDir::Files, QDir::Name);
        foreach (QString file, files)
        {
            // 取绝对路径
            QString srcFileName = srcDir.absoluteFilePath(file);
            QString destFileName = destDir.absoluteFilePath(file);

            // 删除原文件
            QFile::remove(destFileName);

            // 拷贝文件
            if (!QFile::copy(srcFileName, destFileName))
            {
                qWarning() << "Utility cpPath copy fail" << file;
                return false;
            }
        }

        return true;
    }

    // 文件拷贝
    bool fileCopy(const QString& srcFileName, const QString& destFileName)
    {
        qDebug() << "Utility fileCopy" << srcFileName << destFileName;

        // 如果文件存在，则删除文件；
        QFile::remove(destFileName);

        // 文件覆盖
        return QFile::copy(srcFileName, destFileName);
    }

    bool fileCopy(const QString& fileName, const QString& srcFilePath, const QString& destFilePath)
    {
        // 文件拷贝
        return Utility::fileCopy(srcFilePath + fileName, destFilePath + fileName);
    }

    // 运行脚本（通用）
    bool runScript(const QString& script, bool print)
    {
        if (print)
        {
            qDebug() << "Utility runScript" << script;
        }

#ifdef _WIN32
        return true;
#else
        // 执行脚本
        QString command = "sh " + script;
        int ret = system(command.toAscii().constData());

        if (0 != ret)
        {
            qDebug() << "Utility runScript fail, ret " << ret << " strerror " << strerror(errno); 
        }

        return (0 == ret);
#endif
    }

    // 运行脚本（相对/dymind/app/DM_****/script下的脚本）
    bool runAppScript(const QString& script)
    {
        QString projectNo = Project::project();
        qDebug() << "Utility runAppScript the projectNo is : " << projectNo << projectNo.length();

        if (projectNo.length() > 6)
        {
            return Utility::runScript("/dymind/app/" + projectNo + "/" + script);
        }
        else
        {
            return Utility::runScript("/dymind/app/DM_" + projectNo + "/" + script);
        }

    }

    // 抓包
    void dump(const QByteArray& byteArray)
    {
        Utility::dump(byteArray.constData(), byteArray.length());
    }

    void dump(const char* dataBuffer, int dataLen)
    {
        // 格式化
        QString text;
        for (int i = 0; i < dataLen; i++)
        {
            text += QString("%1").arg(*(dataBuffer + i), 2, 16, QChar('0'));
            text += " ";
        }
        text += "\n";

        // 输出
        qDebug() << text;
    }

    // 版本比较（版本格式：0.1.0.9885 -> 0.2.0.1000）
    int compareNonAppVersion(const QString& version)
    {
        QString key = "->";
        int index = version.indexOf(key);

        // 取版本
        QString srcVersion = version.left(index).trimmed();
        QString destVersion = version.mid(index + key.length()).trimmed();

        // 版本比较（版本格式：0.1.0.9885和0.2.0.1000）
        return Utility::compareNonAppVersion(srcVersion, destVersion);
    }

    // 版本比较（版本格式：0.1.0.9885和0.2.0.1000）
    int compareNonAppVersion(const QString& version1, const QString& version2)
    {
        int ret = 0;
        QStringList versions1 = version1.split(".");
        QStringList versions2 = version2.split(".");

        // 如果版本信息两段长度不一致，则默认就不一致
        if (versions1.size() != versions2.size())
        {
            return -1;
        }

        for (int i = 0; i < versions1.size() && i < versions2.size(); i++)
        {
            int v1 = versions1.at(i).toInt();
            int v2 = versions2.at(i).toInt();

            if (v1 > v2)
            {
                ret = -1;
                break;
            }
            else if (v1 < v2)
            {
                ret = 1;
                break;
            }
        }

        return ret;
    }

    // 版本比较（版本格式：0.1.0.9885 -> 0.2.0.1000）
    int compareAppVersion(const QString& version)
    {
        QString key = "->";
        int index = version.indexOf(key);

        // 取版本
        QString srcVersion = version.left(index).trimmed();
        QString destVersion = version.mid(index + key.length()).trimmed();

        // 版本比较（版本格式：0.1.0.9885和0.2.0.1000）
        return Utility::compareAppVersion(srcVersion, destVersion);
    }

    // 版本比较（版本格式：0.1.0.9885和0.2.0.1000）
    int compareAppVersion(const QString& version1, const QString& version2)
    {
        int ret = 0;

        // 版本号分段
        QStringList versions1 = version1.split(".");
        QStringList versions2 = version2.split(".");

        // 最后一位版本号
        int v1 = versions1.last().toInt();
        int v2 = versions2.last().toInt();

        if (v1 > v2)
        {
            ret = -1;
        }
        else if (v1 < v2)
        {
            ret = 1;
        }

        return ret;
    }


    // 压缩tar.bz2文件
    bool tarBz2File7z(const QString& fileName)
    {
        qDebug() << "Utility tarBz2File7z" << fileName;

        if (fileName.endsWith(".tar"))
        {
            QString program = ("7z.exe a -tbzip2 " + fileName + ".bz2 " + fileName);
            return (0 <= QProcess::execute(program));
        }
        else
        {
            return false;
        }
    }

    bool tarBz2FileBzip2(const QString& fileName)
    {
        qDebug() << "Utility tarBz2FileBzip2" << fileName;

        if (fileName.endsWith(".tar"))
        {
            QString program = ("bzip2.exe " + fileName);
            return (0 <= QProcess::execute(program));
        }
        else
        {
            return false;
        }
    }

    // 压缩tar文件
    bool tarFile7z(const QString& path, const QString& fileName)
    {
        qDebug() << "Utility tarFile7z" << path << fileName;

        // 文件名检测
        if (fileName.endsWith(".tar"))
        {
            // 直接打包为tar
            QString program = ("7z.exe a -ttar " + fileName + " " + path);
            return (0 <= QProcess::execute(program));
        }
        else
        {
            return false;
        }
    }

    // 解压缩tar.bz2文件
    bool extractTarBz2File7z(const QString& fileName)
    {
        qDebug() << "Utility extractTarBz2File7z" << fileName;

        if (fileName.endsWith(".tar.bz2"))
        {
            QFileInfo fileInfo(fileName);

            QString program = ("7z.exe x " + fileName + " -y -aos -o" + fileInfo.path());
            return (0 <= QProcess::execute(program));
        }
        else
        {
            return false;
        }
    }

    bool extractTarBz2FileBunzip2(const QString& fileName)
    {
        qDebug() << "Utility extractTarBz2FileBunzip2" << fileName;

        if (fileName.endsWith(".tar.bz2"))
        {
            QString program = ("bunzip2.exe " + fileName);
            return (0 <= QProcess::execute(program));
        }
        else
        {
            return false;
        }
    }

    // 解压缩tar文件
    bool extractTarFile7z(const QString& destPath, const QString& fileName)
    {
        qDebug() << "Utility extractTarFile7z" << fileName;

        if (fileName.endsWith(".tar"))
        {
            QString program = ("7z.exe x " + fileName + " -y -aos -o" + destPath);
            return (0 <= QProcess::execute(program));
        }
        else
        {
            return false;
        }
    }
}
