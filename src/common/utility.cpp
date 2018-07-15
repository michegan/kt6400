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
    // �����
    int rand()
    {
        return qrand();
    }

    // ���������
    void srand()
    {
        // ʱ��Ϊ����
        QTime time(0, 0, 0);
        uint seed = time.msecsTo(QTime::currentTime());

        // ���������
        Utility::srand(seed);
    }

    void srand(uint seed)
    {
        qsrand(seed);
    }

    // ����GUID
    QString newGuid()
    {
        // ʾ����20140226_132831_540
        QDateTime dateTime = QDateTime::currentDateTime();
        return dateTime.toString("yyyyMMdd_hhmmss_zzz");
    }

    // ��������ʽ��
    float format(float value, int dots)
    {
        float multi = qPow(10, dots + 1);

        // ת��Ϊ���ν��д���
        int nvalue = (int)(value * multi + 5);

        // ȥ��β������
        nvalue = (nvalue / 10) * 10;

        // �ٻع鵽������
        return nvalue / multi;
    }

    // ˯��ָ��ʱ�䣬����ƽ̨����
    void ssleep(int secs)
    {
#ifdef _WIN32
        int msecs = 1000 * secs;
        Sleep(msecs);
#else
        sleep(secs);
#endif
    }

    // ˯��ָ��ʱ�䣬����ƽ̨����
    void msleep(int msecs)
    {
#ifdef _WIN32
        Sleep(msecs);
#else
        usleep(msecs * 1000);
#endif
    }

    // ȡָ���ֽ�
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

    // ������ֵ��
    quint16 toUShort(quint8 byte0, quint8 byte1)
    {
        return ((byte0 << 8) | byte1);
    }

    quint32 toUInt(quint8 byte0, quint8 byte1, quint8 byte2, quint8 byte3)
    {
        return ((byte0 << 24) | (byte1 << 16) | (byte2 << 8) | byte3);
    }

    // ����У��ͣ��������ݰ���int������ӣ������������������������ȷ�4������������������������ֽڣ�
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

    // ��ȡ�ļ�����
    char* getFileData(const QString& filename, int* fileLen)
    {
        QFile file(filename);
        char* dataBuffer = 0;

        do 
        {
            // ���ļ�
            if (!file.open(QIODevice::ReadOnly))
            {
                break;
            }

            // �����ļ����������洢�����ļ�����
            int size = file.size();
            dataBuffer = new char[size];
            if (0 == dataBuffer)
            {
                break;
            }
            memset(dataBuffer, 0, size);

            // ͨ������������ȡ���ݣ�����������+�������ݣ�
            int len = file.read(dataBuffer, size);
            if (len != size)
            {
                break;
            }

            // �������ݳ���
            if (fileLen)
            {
                *fileLen = size;
            }
        } while (0);

        // �ر��ļ�
        file.close();

        return dataBuffer;
    }

    // ����Ŀ¼
    bool mkPath(const QString& path)
    {
        qDebug() << "Utility mkPath" << path;

        // ����Ŀ¼�Ƿ���ڣ�����Ŀ¼
        QDir dir(path);
        return (dir.exists() ? true : dir.mkpath("."));
    }

    // ɾ��Ŀ¼����Ŀ¼����
    bool rmPath(const QString& path)
    {
        // ���Ŀ¼����ɾ��Ŀ¼����
        if (Utility::clearPath(path))
        {
            // ɾ��Ŀ¼����
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

    // ���Ŀ¼����ɾ��Ŀ¼����
    bool clearPath(const QString& path)
    {
        qDebug() << "Utility clearPath" << path;

        QDir dir(path);
        if (!dir.exists())
        {
            return false;
        }

        // ɾ��������Ŀ¼�����ļ�
        QFileInfoList fileInfoList = dir.entryInfoList();
        foreach(QFileInfo fileInfo, fileInfoList)
        {
            if (fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            {
                continue;
            }

            // ɾ����Ŀ¼
            if (fileInfo.isDir())
            {
                // �ݹ�ɾ����Ŀ¼
                QString subPath = path + fileInfo.fileName() + ("/");
                if (!Utility::clearPath(subPath))
                {
                    return false;
                }

                // ɾ����Ŀ¼
                if (!dir.rmdir(fileInfo.fileName()))
                {
                    return false;
                }
            }
            // ɾ�����ļ�
            else if(fileInfo.isFile())
            {
                if (!dir.remove(fileInfo.fileName()))
                {
                    return false;
                }
            }
            else
            {
                // �����κδ���
            }
        }

        return true;
    }

    // ����Ŀ¼
    bool cpPath(const QString& srcPath, const QString& destPath)
    {
        QDir srcDir(srcPath);
        QDir destDir(destPath);

        qDebug() << "Utility cpPath" << srcPath << destPath;

        // Ŀ¼�Ƿ���ڼ��
        if (!srcDir.exists() || !destDir.exists())
        {
            qWarning() << "Utility cpPath no dir";
            return false;
        }

        // �����������ļ�
        QStringList files = srcDir.entryList(QDir::Files, QDir::Name);
        foreach (QString file, files)
        {
            // ȡ����·��
            QString srcFileName = srcDir.absoluteFilePath(file);
            QString destFileName = destDir.absoluteFilePath(file);

            // ɾ��ԭ�ļ�
            QFile::remove(destFileName);

            // �����ļ�
            if (!QFile::copy(srcFileName, destFileName))
            {
                qWarning() << "Utility cpPath copy fail" << file;
                return false;
            }
        }

        return true;
    }

    // �ļ�����
    bool fileCopy(const QString& srcFileName, const QString& destFileName)
    {
        qDebug() << "Utility fileCopy" << srcFileName << destFileName;

        // ����ļ����ڣ���ɾ���ļ���
        QFile::remove(destFileName);

        // �ļ�����
        return QFile::copy(srcFileName, destFileName);
    }

    bool fileCopy(const QString& fileName, const QString& srcFilePath, const QString& destFilePath)
    {
        // �ļ�����
        return Utility::fileCopy(srcFilePath + fileName, destFilePath + fileName);
    }

    // ���нű���ͨ�ã�
    bool runScript(const QString& script, bool print)
    {
        if (print)
        {
            qDebug() << "Utility runScript" << script;
        }

#ifdef _WIN32
        return true;
#else
        // ִ�нű�
        QString command = "sh " + script;
        int ret = system(command.toAscii().constData());

        if (0 != ret)
        {
            qDebug() << "Utility runScript fail, ret " << ret << " strerror " << strerror(errno); 
        }

        return (0 == ret);
#endif
    }

    // ���нű������/dymind/app/DM_****/script�µĽű���
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

    // ץ��
    void dump(const QByteArray& byteArray)
    {
        Utility::dump(byteArray.constData(), byteArray.length());
    }

    void dump(const char* dataBuffer, int dataLen)
    {
        // ��ʽ��
        QString text;
        for (int i = 0; i < dataLen; i++)
        {
            text += QString("%1").arg(*(dataBuffer + i), 2, 16, QChar('0'));
            text += " ";
        }
        text += "\n";

        // ���
        qDebug() << text;
    }

    // �汾�Ƚϣ��汾��ʽ��0.1.0.9885 -> 0.2.0.1000��
    int compareNonAppVersion(const QString& version)
    {
        QString key = "->";
        int index = version.indexOf(key);

        // ȡ�汾
        QString srcVersion = version.left(index).trimmed();
        QString destVersion = version.mid(index + key.length()).trimmed();

        // �汾�Ƚϣ��汾��ʽ��0.1.0.9885��0.2.0.1000��
        return Utility::compareNonAppVersion(srcVersion, destVersion);
    }

    // �汾�Ƚϣ��汾��ʽ��0.1.0.9885��0.2.0.1000��
    int compareNonAppVersion(const QString& version1, const QString& version2)
    {
        int ret = 0;
        QStringList versions1 = version1.split(".");
        QStringList versions2 = version2.split(".");

        // ����汾��Ϣ���γ��Ȳ�һ�£���Ĭ�ϾͲ�һ��
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

    // �汾�Ƚϣ��汾��ʽ��0.1.0.9885 -> 0.2.0.1000��
    int compareAppVersion(const QString& version)
    {
        QString key = "->";
        int index = version.indexOf(key);

        // ȡ�汾
        QString srcVersion = version.left(index).trimmed();
        QString destVersion = version.mid(index + key.length()).trimmed();

        // �汾�Ƚϣ��汾��ʽ��0.1.0.9885��0.2.0.1000��
        return Utility::compareAppVersion(srcVersion, destVersion);
    }

    // �汾�Ƚϣ��汾��ʽ��0.1.0.9885��0.2.0.1000��
    int compareAppVersion(const QString& version1, const QString& version2)
    {
        int ret = 0;

        // �汾�ŷֶ�
        QStringList versions1 = version1.split(".");
        QStringList versions2 = version2.split(".");

        // ���һλ�汾��
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


    // ѹ��tar.bz2�ļ�
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

    // ѹ��tar�ļ�
    bool tarFile7z(const QString& path, const QString& fileName)
    {
        qDebug() << "Utility tarFile7z" << path << fileName;

        // �ļ������
        if (fileName.endsWith(".tar"))
        {
            // ֱ�Ӵ��Ϊtar
            QString program = ("7z.exe a -ttar " + fileName + " " + path);
            return (0 <= QProcess::execute(program));
        }
        else
        {
            return false;
        }
    }

    // ��ѹ��tar.bz2�ļ�
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

    // ��ѹ��tar�ļ�
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
