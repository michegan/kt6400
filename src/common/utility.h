#ifndef _UTILITY_H_
#define _UTILITY_H_


#include <QString>

#include "libcommon.h"


// ���߼�
namespace Utility
{
    // �����
    COMMON_EXPORT int rand();

    // ���������
    COMMON_EXPORT void srand();
    COMMON_EXPORT void srand(uint seed);

    // ����GUID
    COMMON_EXPORT QString newGuid();

    // ��������ʽ��
    COMMON_EXPORT float format(float value, int dots);

    // ˯��ָ��ʱ�䣬����ƽ̨����
    COMMON_EXPORT void ssleep(int secs);
    COMMON_EXPORT void msleep(int msecs);

    // ȡָ���ֽڣ�byte���ֽ�����ֵ��ȡֵ��Χ[1��2��3��4]��
    COMMON_EXPORT quint8 lowerByte(qint16 value);
    COMMON_EXPORT quint8 lowerUByte(quint16 value);

    COMMON_EXPORT quint8 upperByte(qint16 value);
    COMMON_EXPORT quint8 upperUByte(quint16 value);

    COMMON_EXPORT quint8 getByte(int byte, qint32 value);
    COMMON_EXPORT quint8 getUByte(int byte, quint32 value);

    // ������ֵ
    COMMON_EXPORT quint16 toUShort(quint8 byte0, quint8 byte1);
    COMMON_EXPORT quint32 toUInt(quint8 byte0, quint8 byte1, quint8 byte2, quint8 byte3);

    // ����У��ͣ��������ݰ���int������ӣ������������������������ȷ�4������������������������ֽڣ�
    COMMON_EXPORT int checkSum(const char* dataBuffer, int dataLen);

    // ��ȡ�ļ����ݣ������ļ���
    COMMON_EXPORT char* getFileData(const QString& filename, int* fileLen = 0);

    // ����Ŀ¼
    COMMON_EXPORT bool mkPath(const QString& path);
    // ɾ��Ŀ¼����Ŀ¼����
    COMMON_EXPORT bool rmPath(const QString& path);
    // ���Ŀ¼����ɾ��Ŀ¼����
    COMMON_EXPORT bool clearPath(const QString& path);
    // ����Ŀ¼
    COMMON_EXPORT bool cpPath(const QString& srcPath, const QString& destPath);

    // �ļ�����
    COMMON_EXPORT bool fileCopy(const QString& srcFileName, const QString& destFileName);
    COMMON_EXPORT bool fileCopy(const QString& fileName, const QString& srcFilePath, const QString& destFilePath);

    // ���нű���ͨ�ã�
    COMMON_EXPORT bool runScript(const QString& script, bool print = true);
    // ���нű������/dymind/app/DM_****/script�µĽű���
    COMMON_EXPORT bool runAppScript(const QString& script);

    // ץ��
    COMMON_EXPORT void dump(const QByteArray& byteArray);
    COMMON_EXPORT void dump(const char* dataBuffer, int dataLen);


    // �汾�Ƚϣ��汾��ʽ��0.1.0.9885 -> 0.2.0.1000��
    COMMON_EXPORT int compareNonAppVersion(const QString& version);
    // �汾�Ƚϣ��汾��ʽ��0.1.0.9885��0.2.0.1000��
    COMMON_EXPORT int compareNonAppVersion(const QString& version1, const QString& version2);

    // �汾�Ƚϣ��汾��ʽ��0.1.0.9885 -> 0.2.0.1000��
    COMMON_EXPORT int compareAppVersion(const QString& version);
    // �汾�Ƚϣ��汾��ʽ��0.1.0.9885��0.2.0.1000��
    COMMON_EXPORT int compareAppVersion(const QString& version1, const QString& version2);


    // ѹ��tar.bz2�ļ�
    COMMON_EXPORT bool tarBz2File7z(const QString& fileName);
    COMMON_EXPORT bool tarBz2FileBzip2(const QString& fileName);
    // ѹ��tar�ļ�
    COMMON_EXPORT bool tarFile7z(const QString& path, const QString& fileName);

    // ��ѹ��tar.bz2�ļ�
    COMMON_EXPORT bool extractTarBz2File7z(const QString& fileName);
    COMMON_EXPORT bool extractTarBz2FileBunzip2(const QString& fileName);
    // ��ѹ��tar�ļ�
    COMMON_EXPORT bool extractTarFile7z(const QString& destPath, const QString& fileName);
}


#endif // _UTILITY_H_
