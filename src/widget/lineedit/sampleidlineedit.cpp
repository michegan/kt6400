#include <QKeyEvent>

#include "sampleidlineedit.h"


class SampleIdLineEditPrivate
{
public:
    SampleIdLineEditPrivate();
    ~SampleIdLineEditPrivate();

public:
    // 内容有效字符集
    QList<QChar> chars;
    // 其他输入有效字符集
    QList<QChar> others;
};

SampleIdLineEditPrivate::SampleIdLineEditPrivate()
{
    // 内容有效字符集：字母
    this->chars.append(Qt::Key_A);
    this->chars.append(Qt::Key_B);
    this->chars.append(Qt::Key_C);
    this->chars.append(Qt::Key_D);
    this->chars.append(Qt::Key_E);
    this->chars.append(Qt::Key_F);
    this->chars.append(Qt::Key_G);

    this->chars.append(Qt::Key_H);
    this->chars.append(Qt::Key_I);
    this->chars.append(Qt::Key_J);
    this->chars.append(Qt::Key_K);
    this->chars.append(Qt::Key_L);
    this->chars.append(Qt::Key_M);
    this->chars.append(Qt::Key_N);

    this->chars.append(Qt::Key_O);
    this->chars.append(Qt::Key_P);
    this->chars.append(Qt::Key_Q);
    this->chars.append(Qt::Key_R);
    this->chars.append(Qt::Key_S);
    this->chars.append(Qt::Key_T);

    this->chars.append(Qt::Key_U);
    this->chars.append(Qt::Key_V);
    this->chars.append(Qt::Key_W);
    this->chars.append(Qt::Key_X);
    this->chars.append(Qt::Key_Y);
    this->chars.append(Qt::Key_Z);

    // 内容有效字符集：数字
    this->chars.append(Qt::Key_0);
    this->chars.append(Qt::Key_1);
    this->chars.append(Qt::Key_2);
    this->chars.append(Qt::Key_3);
    this->chars.append(Qt::Key_4);
    this->chars.append(Qt::Key_5);
    this->chars.append(Qt::Key_6);
    this->chars.append(Qt::Key_7);
    this->chars.append(Qt::Key_8);
    this->chars.append(Qt::Key_9);

    // 内容有效字符集：横线
    this->chars.append(Qt::Key_Minus);
    // 内容有效字符集：下划线
    this->chars.append(Qt::Key_Underscore);

    // 其他输入有效字符集：
    this->chars.append(Qt::Key_Delete);
    this->chars.append(Qt::Key_Backspace);
    this->chars.append(Qt::Key_Left);
    this->chars.append(Qt::Key_Right);
    this->chars.append(Qt::Key_Home);
    this->chars.append(Qt::Key_End);
}

SampleIdLineEditPrivate::~SampleIdLineEditPrivate()
{

}


SampleIdLineEdit::SampleIdLineEdit(QWidget* parent)
    : LineEdit(parent), d(new SampleIdLineEditPrivate())
{
    // 默认尺寸
    this->resize(100, 30);
}

SampleIdLineEdit::~SampleIdLineEdit()
{
    delete d;
}

// 是否有效
bool SampleIdLineEdit::isValid()
{
    bool ret = true;
    QString text = this->text();

    for (int i = 0; i < text.length(); i++)
    {
        QChar chr = text.at(i);
        if (!d->chars.contains(chr))
        {
            ret = false;
            break;
        }
    }

    return ret;
}

// 按键响应
void SampleIdLineEdit::keyPressEvent(QKeyEvent* event)
{
    int key = event->key();

    // 根据是否有效进行不同处理
    if (d->chars.contains(key) || d->others.contains(key))
    {
        LineEdit::keyPressEvent(event);
    }
    else
    {
        event->accept();
    }
}