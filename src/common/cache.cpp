#include <QtDebug>
#include <QStringList>

#include "cache.h"


namespace Cache
{
    // 当前用户
    static User s_currentUser;

    // 当前用户
    static SysState s_sysState;

    // 宠物版
    static bool s_forPets = true;

    // 参考范围
    static QMap<QString, ParaList> s_lowLimits;
    static QMap<QString, ParaList> s_highLimits;

    // 校准系数
    static QMap<QString, QList<CalFactor> > s_calFactors;

    // 合并关键字
    static QString key(const QString& key1, const QString& key2)
    {
        QStringList keys;
        keys << key1 << key2;
        return keys.join(":");
    }

    // 当前用户
    User* currentUser()
    {
        return &s_currentUser;
    }

    // 当前系统状态
    SysState* sysState()
    {
        return &s_sysState;
    }

    // 仪器相关配置
    bool isForPets()
    {
        return s_forPets;
    }

    void setForPets(bool forPets)
    {
        qDebug() << "Cache setForPets" << forPets;
        s_forPets = forPets;
    }

    // 校准系数
    float getCalFactor(const QList<CalFactor>& calFactors, const QString& para)
    {
        float value = 1;

        // 获取关键字下，参数对应的校准系数
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

        // 增益计数
        if (WORK_MODE_GAIN == modes.workMode)
        {
            // 增益校准是无论任何权限都不乘以校准系数的
            factor = 1;
        }
        // 校准计数
        else if (WORK_MODE_CALIBRATE == modes.workMode)
        {
            if (Cache::currentUser()->isService())
            {
                // 厂家校准计数，则不需要任何校准系数，直接使用原始值
                factor = 1;
            }
            else
            {
                // 用户校准计数，只需要考虑厂家校准系数
                QList<CalFactor> calFactors = Cache::getCalFactors("IDS_FACTORY", modes.ids());
                factor *= Cache::getCalFactor(calFactors, para);
            }
        }
        else
        {
            // 非校准模式计数，则需要同时考虑厂家校准计数和用户校准系数
            QList<CalFactor> calFactors = Cache::getCalFactors("IDS_FACTORY", modes.ids());
            factor *= Cache::getCalFactor(calFactors, para);

            calFactors = Cache::getCalFactors("IDS_USER", modes.ids());
            factor *= Cache::getCalFactor(calFactors, para);
        }

        return factor;
    }

    QList<CalFactor> getCalFactors(const QString& key1, const QString& key2)
    {
        // 转换为一个关键字
        const QString key = Cache::key(key1, key2);
        return s_calFactors.value(key, QList<CalFactor>());
    }

    void setCalFactors(const QString& key1, const QString& key2, const QList<CalFactor>& calFactors)
    {
        // 转换为一个关键字
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

    // 参考范围缓存
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
        // 转换为一个关键字
        const QString key = Cache::key(key1, key2);

        // 下限
        bool ret1 = s_lowLimits.contains(key);
        if (ret1)
        {
            lowLimits = s_lowLimits.value(key);
        }

        // 上限
        bool ret2 = s_highLimits.contains(key);
        if (ret1)
        {
            highLimits = s_highLimits.value(key);
        }

        return (ret1 && ret2);
    }

    void setRefRange(const QString& key1, const QString& key2, const ParaList& lowLimits, const ParaList& highLimits)
    {
        // 转换为一个关键字
        const QString key = Cache::key(key1, key2);

        // 下限
        if (s_lowLimits.contains(key))
        {
            s_lowLimits[key] = lowLimits;
        }
        else
        {
            s_lowLimits.insert(key, lowLimits);
        }

        // 上限
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