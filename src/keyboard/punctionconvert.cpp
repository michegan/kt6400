#include <QHash>

#include "punctionconvert.h"

namespace PunctionConvert
{
    // ���ȫ�Ƿ��Ŷ��չ�ϣ��
    QHash<int, QString> chinesePuncHash()
    {
        static QHash<int, QString> puncHash;
        if (puncHash.isEmpty())
        {
            puncHash.insert('~',  QChar(0xFF5E)); // ��
            puncHash.insert('`',  QChar(0xFF40)); // ��
            puncHash.insert('!',  QChar(0xFF01)); // ��
            puncHash.insert('@',  QChar(0xFF20)); // ��
            puncHash.insert('#',  QChar(0xFF03)); // ��
            puncHash.insert('$',  QChar(0xFFE5)); // ��
            puncHash.insert('%',  QChar(0xFF05)); // ��
            puncHash.insert('^',  QChar(0xFF3E)); // ��
            puncHash.insert('&',  QChar(0xFF06)); // ��
            puncHash.insert('*',  QChar(0xFF0A)); // ��
            puncHash.insert('(',  QChar(0xFF08)); // ��
            puncHash.insert(')',  QChar(0xFF09)); // ��
            puncHash.insert('_',  QChar(0xFF3F)); // ��
            puncHash.insert('+',  QChar(0xFF0B)); // ��
            puncHash.insert('-',  QChar(0xFF0D)); // ��
            puncHash.insert('=',  QChar(0xFF1D)); // ��
            puncHash.insert('\\', QChar(0xFF3C)); // ��
            puncHash.insert('|',  QChar(0xFF5C)); // ��
            puncHash.insert('[',  QChar(0x3010)); // ��
            puncHash.insert(']',  QChar(0x3011)); // ��
            puncHash.insert('{',  QChar(0xFF5B)); // ��
            puncHash.insert('}',  QChar(0xFF5D)); // ��
            puncHash.insert(';',  QChar(0xFF1B)); // ��
            puncHash.insert(':',  QChar(0xFF1A)); // ��
            puncHash.insert('<',  QChar(0xFF1C)); // ��
            puncHash.insert('>',  QChar(0xFF1E)); // ��
            puncHash.insert(',',  QChar(0xFF0C)); // ��
            puncHash.insert('.',  QChar(0x3002)); // ��
            puncHash.insert('?',  QChar(0xFF1F)); // ��
            puncHash.insert('/',  QChar(0xFF0F)); // ��

            QString strPunc = "";

            // ������
            strPunc.append(QChar(0x2018));
            strPunc.append(QChar(0x2019));
            puncHash.insert('\'',  strPunc); // ����
            strPunc.clear();

            // ˫����
            strPunc.append(QChar(0x201C));
            strPunc.append(QChar(0x201D));
            puncHash.insert('\"',  strPunc); // ����
            strPunc.clear();
        }

        return puncHash;
    }

    // �������뷨���ȫ�Ƿ���ת����ϣ��
    QHash<int, QString> specialChinesePuncHash()
    {
        static QHash<int, QString> specialPuncHash;
        if (specialPuncHash.isEmpty())
        {
            // �������뷨�����£�б�ߺͷ�б�߾�ת��Ϊ�ٺ�
            specialPuncHash.insert('/',  QChar(0x3001)); // ��
            specialPuncHash.insert('\\', QChar(0x3001)); // ��

            // �������뷨�����£����ں�С�ں����������
            specialPuncHash.insert('<',  QChar(0x300A)); // ��
            specialPuncHash.insert('>',  QChar(0x300B)); // ��

            QString strPunc = "";

            // ʡ�Ժ�
            strPunc.append(QChar(0x2026));
            strPunc.append(QChar(0x2026));
            specialPuncHash.insert('^',  strPunc); // ����
            strPunc.clear();

            // ���ۺ�
            strPunc.append(QChar(0x2014));
            strPunc.append(QChar(0x2014));
            specialPuncHash.insert('_',  strPunc); // ����
            strPunc.clear();
        }

        return specialPuncHash;
    }


    // ����Ƿ���ת��Ϊȫ�Ƿ��ţ��������뷨���棩
    bool convertToChinesePuncForPyInput(int srcPunc, QString& strDst)
    {
        QHash<int, QString> chinesePunc = chinesePuncHash();
        QHash<int, QString> specialPunc = specialChinesePuncHash();
        if (!chinesePunc.contains(srcPunc) && !specialPunc.contains(srcPunc))
        {
            return false;
        }

        // ����ִ�������������ת��
        if (specialPunc.contains(srcPunc))
        {
            strDst = specialPunc.value(srcPunc);
        }
        else if (chinesePunc.contains(srcPunc))
        {
            strDst = chinesePunc.value(srcPunc);
        }

        return true;
    }

    // ����Ƿ���ת��Ϊȫ�Ƿ��ţ�ȫ�Ƿ������뷨���棩
    bool convertToChinesePunc(int srcPunc, QString& strDst)
    {
        QHash<int, QString> chinesePunc = chinesePuncHash();
        if (!chinesePunc.contains(srcPunc))
        {
            return false;
        }

        strDst = chinesePunc.value(srcPunc);
        return true;
    }
}