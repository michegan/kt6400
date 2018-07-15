#include "define.h"
#include "sampleid.h"


// 样本编号
namespace SampleId
{
    // 本底样本编号
    QString background()
    {
        return "background";
    }

    // 样本编号是否有效
    bool isValid(const QString& sampleId)
    {
        bool ret = false;

        do 
        {
            int length = sampleId.length();

            // 非空
            if (0 == length)
            {
                break;
            }

            // 未超长
            if (MAX_SID_LEN < length)
            {
                break;
            }

            // 全部数字
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

    // 样本编号自动递增
    QString autoInc(const QString& sampleId)
    {
        int length = sampleId.length();

        // 倒数9的个数
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
            // 最大长度全部9，不能再递增，恢复到1
            return "1";
        }
        else if (count == length)
        {
            // 非最大长度全部9，还可以继续递增
            QString id;
            id.fill(Qt::Key_0, count);

            return QString("1%1").arg(id);
        }
        else
        {
            // 前半部分非9，后半部分9，还可以继续递增
            QString id;
            id.fill(Qt::Key_0, count);

            int remain = (length - count - 1);
            int number = sampleId.at(remain).toAscii() + 1;

            return (sampleId.left(remain) + QChar(number) + id);
        }        
    }
}