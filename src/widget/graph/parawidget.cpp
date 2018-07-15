#include <QFont>
#include <QPainter>

#include "uicolor.h"
#include "paraunit.h"
#include "parawidget.h"


// �и�
#define HEAD_HEIGHT                  (38)
#define CONTENT_HEIGHT               (29)


ParaWidget::ParaWidget(QWidget* parent)
    : QWidget(parent), rows(8), backgroundHead(QColor(68, 112, 149)), 
      backgroundContent1(QColor(255, 255, 255)), backgroundContent2(QColor(207, 223, 249)), 
      foregroundHead(QColor(255, 255, 255)), foregroundContent(QColor(0, 0, 0))
{

}

ParaWidget::~ParaWidget()
{

}

// ����
void ParaWidget::setRows(int rows)
{
    this->rows = rows;

    // ˢ��
    this->update();
}

// ���
void ParaWidget::clear()
{
    this->setParaList(ParaList());
}

// ���������б�
void ParaWidget::setParas(const QStringList& paras)
{
    this->paras = paras;
}

void ParaWidget::setParaList(const ParaList& paraList)
{
    this->paraList = paraList;

    // ˢ��
    this->update();
}

// �����¼�
void ParaWidget::paintEvent(QPaintEvent* event)
{
    // ���Ʊ���
    this->drawBackground();

    // ��������
    this->drawContent();
}

// ��������
void ParaWidget::drawContent()
{
    QPainter painter(this);
    QFont font = painter.font();

    // ÿ�еı�����4�У�����߾�Ԥ��4%��
    const int NumOfColumns = 4;
    float scales[NumOfColumns] = { 0.3f, 0.08f, 0.3f, 0.28f };

    // ��ͷ
    painter.setPen(this->foregroundHead);

    QString heads[NumOfColumns] = { "Name", "", "Result", "Unit" };

    float x = (this->width() * 0.02);
    for (int column = 0; column < NumOfColumns; column ++)
    {
        font.setBold(true);
        painter.setFont(font);

        int columtWidth = (this->width() * scales[column]);

        QRect rect(x, 0, columtWidth, HEAD_HEIGHT);
        painter.drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, heads[column]);

        x = rect.right();
    }

    // ����
    for (int i = 0; i < this->paras.length(); i++)
    {
        float x = (this->width() * 0.02);
        float y = (HEAD_HEIGHT + i * CONTENT_HEIGHT);

        // Name
        font.setBold(false);
        painter.setFont(font);

        painter.setPen(this->foregroundContent);

        QString name = this->paras.at(i);
        float columtWidth = (this->width() * scales[0]);

        QRect rect = QRect(x, y, columtWidth, CONTENT_HEIGHT);
        painter.drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, name);

        // Flag
        x = rect.right();
        columtWidth = (this->width() * scales[1]);

        rect = QRect(x, y, columtWidth, CONTENT_HEIGHT);
        if (!this->paraList.isEmpty())
        {
            Para para = this->paraList.para(name);

            QColor color = UIColor::paraColor(para);
            painter.setPen(color);

            painter.drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, para.flagToString());
        }

        // Result
        font.setBold(true);
        painter.setFont(font);

        x = rect.right();
        columtWidth = (this->width() * scales[2]);

        rect = QRect(x, y, columtWidth, CONTENT_HEIGHT);
        if (!this->paraList.isEmpty())
        {
            Para para = this->paraList.para(name);

            QColor color = UIColor::paraColor(para);
            painter.setPen(color);

            painter.drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, para.valueToString(2));
        }

        // Unit
        font.setBold(false);
        painter.setFont(font);

        painter.setPen(this->foregroundContent);

        x = rect.right();
        columtWidth = (this->width() * scales[3]);

        QString unit = ParaUnit::paraUnit(name);

        rect = QRect(x, y, columtWidth, CONTENT_HEIGHT);
        painter.drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, unit);
    }
}

// ���Ʊ���
void ParaWidget::drawBackground()
{
    QPainter painter(this);

    // ��ͷ
    painter.fillRect(0, 0, this->width(), HEAD_HEIGHT, this->backgroundHead);

    // ����
    int y = HEAD_HEIGHT;
    for (int i = 0; i < this->rows; i++)
    {
        QColor color = (i % 2 ? this->backgroundContent2 : this->backgroundContent1);
        painter.fillRect(0, y + i * CONTENT_HEIGHT, this->width(), CONTENT_HEIGHT, color);
    }
}