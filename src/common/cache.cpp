#include <QtDebug>
#include <QStringList>

#include "cache.h"


namespace Cache
{
    // ��ǰ�û�
    static User s_currentUser;

    // ��ǰ�û�
    static SysState s_sysState;

    // �����
    static bool s_forPets = true;

    // �ο���Χ
    static QMap<QString, ParaList> s_lowLimits;
    static QMap<QString, ParaList> s_highLimits;

    // У׼ϵ��
    static QMap<QString, QList<CalFactor> > s_calFactors;

    // �ϲ��ؼ���
    static QString key(const QString& key1, const QString& key2)
    {
        QStringList keys;
        keys << key1 << key2;
        return keys.join(":");
    }

    // ��ǰ�û�
    User* currentUser()
    {
        return &s_currentUser;
    }

    // ��ǰϵͳ״̬
    SysState* sysState()
    {
        return &s_sysState;
    }

    // �����������
    bool isForPets()
    {
        return s_forPets;
    }

    void setForPets(bool forPets)
    {
        qDebug() << "Cache setForPets" << forPets;
        s_forPets = forPets;
    }

    // У׼ϵ��
    float getCalFactor(const QList<CalFactor>& calFactors, const QString& para)
    {
        float value = 1;

        // ��ȡ�ؼ����£�������Ӧ��У׼ϵ��
        foreach (CalFactor calFactor, calFactors)
        {
            if (calFactor.id == para)
            {
                value = calFactor.value;
                break;
            }
        }

        return value;
    }

    float getCalFactor(const Modes& modes, const QString& para)
    {
        float factor = 1;

        // �������
        if (WORK_MODE_GAIN == modes.workMode)
        {
            // ����У׼�������κ�Ȩ�޶�������У׼ϵ����
            factor = 1;
        }
        // У׼����
        else if (WORK_MODE_CALIBRATE == modes.workMode)
        {
            if (Cache::currentUser()->isService())
            {
                // ����У׼����������Ҫ�κ�У׼ϵ����ֱ��ʹ��ԭʼֵ
                factor = 1;
            }
            else
            {
                // �û�У׼������ֻ��Ҫ���ǳ���У׼ϵ��
                QList<CalFactor> calFactors = Cache::getCalFactors("IDS_FACTORY", modes.ids());
                factor *= Cache::getCalFactor(calFactors, para);
            }
        }
        else
        {
            // ��У׼ģʽ����������Ҫͬʱ���ǳ���У׼�������û�У׼ϵ��
            QList<CalFactor> calFactors = Cache::getCalFactors("IDS_FACTORY", modes.ids());
            factor *= Cache::getCalFactor(calFactors, para);

            calFactors = Cache::getCalFactors("IDS_USER", modes.ids());
            factor *= Cache::getCalFactor(calFactors, para);
        }

        return factor;
    }

    QList<CalFactor> getCalFactors(const QString& key1, const QString& key2)
    {
        // ת��Ϊһ���ؼ���
        const QString key = Cache::key(key1, key2);
        return s_calFactors.value(key, QList<CalFactor>());
    }

    void setCalFactors(const QString& key1, const QString& key2, const QList<CalFactor>& calFactors)
    {
        // ת��Ϊһ���ؼ���
        const QString key = Cache::key(key1, key2);

        if (s_calFactors.contains(key))
        {
            s_calFactors[key] = calFactors;
        }
        else
        {
            s_calFactors.insert(key, calFactors);
        }
    }

    // �ο���Χ����
    QStringList refRangeKeys1()
    {
        QStringList keys1;

        QStringList keys = s_lowLimits.keys();
        foreach (QString key, keys)
        {
            QStringList list = key.split(":");
            if (0 < list.length())
            {
                keys1.append(list.at(0));
            }
        }

        return keys1;
    }

    QStringList refRangeKeys2(const QString& key1)
    {
        QStringList keys2;

        QStringList keys = s_lowLimits.keys();
        foreach (QString key, keys)
        {
            QStringList list = key.split(":");
            if (1 < list.length())
            {
                if (key1 == list.at(0))
                {
                    keys2.append(list.at(1));
                }
            }
        }

        return keys2;
    }

    bool refRange(const QString& key1, const QString& key2, ParaList& lowLimits, ParaList& highLimits)
    {
        // ת��Ϊһ���ؼ���
        const QString key = Cache::key(key1, key2);

        // ����
        bool ret1 = s_lowLimits.contains(key);
        if (ret1)
        {
            lowLimits = s_lowLimits.value(key);
        }

        // ����
        bool ret2 = s_highLimits.contains(key);
        if (ret1)
        {
            highLimits = s_highLimits.value(key);
        }

        return (ret1 && ret2);
    }

    void setRefRange(const QString& key1, const QString& key2, const ParaList& lowLimits, const ParaList& highLimits)
    {
        // ת��Ϊһ���ؼ���
        const QString key = Cache::key(key1, key2);

        // ����
        if (s_lowLimits.contains(key))
        {
            s_lowLimits[key] = lowLimits;
        }
        else
        {
            s_lowLimits.insert(key, lowLimits);
        }

        // ����
        if (s_highLimits.contains(key))
        {
            s_highLimits[key] = highLimits;
        }
        else
        {
            s_highLimits.insert(key, highLimits);
        }
    }
}