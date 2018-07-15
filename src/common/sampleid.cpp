#include "define.h"
#include "sampleid.h"


// �������
namespace SampleId
{
    // �����������
    QString background()
    {
        return "background";
    }

    // ��������Ƿ���Ч
    bool isValid(const QString& sampleId)
    {
        bool ret = false;

        do 
        {
            int length = sampleId.length();

            // �ǿ�
            if (0 == length)
            {
                break;
            }

            // δ����
            if (MAX_SID_LEN < length)
            {
                break;
            }

            // ȫ������
            ret = true;

            for (int i = 0; i < length; i++)
            {
                QChar chr = sampleId.at(i);
                if (!(Qt::Key_0 <= chr && chr <= Qt::Key_9))
                {
                    ret = false;
                    break;
                }
            }
        } while (0);

        return ret;
    }

    // ��������Զ�����
    QString autoInc(const QString& sampleId)
    {
        int length = sampleId.length();

        // ����9�ĸ���
        int count = 0;
        for (int i = length - 1; i >= 0;i--)
        {
            if (sampleId.at(i) == Qt::Key_9)
            {
                count ++;
            }
            else
            {
                break;
            }
        }
        
        if (count == MAX_SID_LEN)
        {
            // ��󳤶�ȫ��9�������ٵ������ָ���1
            return "1";
        }
        else if (count == length)
        {
            // ����󳤶�ȫ��9�������Լ�������
            QString id;
            id.fill(Qt::Key_0, count);

            return QString("1%1").arg(id);
        }
        else
        {
            // ǰ�벿�ַ�9����벿��9�������Լ�������
            QString id;
            id.fill(Qt::Key_0, count);

            int remain = (length - count - 1);
            int number = sampleId.at(remain).toAscii() + 1;

            return (sampleId.left(remain) + QChar(number) + id);
        }        
    }
}