#include <QMap>

#include "modes.h"


Modes::Modes()
    : workMode(WORK_MODE_NORMAL), sampleMode(SAMPLE_MODE_OPEN), speciesMode(SPECIES_MODE_HUMAN), 
      bloodMode(BLOOD_MODE_WHOLE_BLOOD), analysisMode(ANALYSIS_MODE_CBC), preprocessMode(PREPROCESS_MODE_NONE)
{

}

Modes::~Modes()
{

}

// 格式化
QString Modes::ids() const
{
    if (BLOOD_MODE_PERIPHERAL == this->bloodMode)
    {
        if (PREPROCESS_MODE_PREDILUENT == this->preprocessMode)
        {
            return "IDS_PREDILUENT";
        }
        else
        {
            return "IDS_PERIPHERAL";
        }
    }
    else
    {
        if (PREPROCESS_MODE_PREDILUENT == this->preprocessMode)
        {
            return "IDS_PREDILUENT";
        }
        else
        {
            return "IDS_WHOLE_BLOOD";
        }
    }
}

// 物种模式格式化
QString Modes::specimodeIds() const
{
    QMap<int, QString> maps;

    maps.insert(SPECIES_MODE_DOG, "IDS_DOG");
    maps.insert(SPECIES_MODE_CAT, "IDS_CAT");
    maps.insert(SPECIES_MODE_MOUSE, "IDS_MOUSE");
    maps.insert(SPECIES_MODE_RABBIT, "IDS_RABBIT");

    return maps.value(this->speciesMode, "IDS_HUMAN");
}

QString Modes::speciesImage() const
{
    QMap<int, QString> maps;

    maps.insert(SPECIES_MODE_DOG, "dog.png");
    maps.insert(SPECIES_MODE_CAT, "cat.png");
    maps.insert(SPECIES_MODE_MOUSE, "mouse.png");
    maps.insert(SPECIES_MODE_RABBIT, "rabbit.png");

    return maps.value(this->speciesMode, "");
}