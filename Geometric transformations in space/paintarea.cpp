#include "paintarea.h"
#include <QPainter>
#include <QVector4D>

PaintArea::PaintArea(QWidget *parent) : QWidget(parent)
{

}

void PaintArea::setDots(QVector<QVector4D> pnts)
{
    dots_for_draw = pnts;

}

void PaintArea::setParams(int n, int m)
{
    parallels = n;
    meridians = m;
}

void PaintArea::clear(QPainter &pntr)
{
    pntr.eraseRect(0,0,width(),height());
}

void PaintArea::removePoints()
{
    dots_for_draw.clear();
}

void PaintArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    painter.setPen(QPen(Qt::red,1,Qt::SolidLine));       //Настройки рисования
    painter.setRenderHint(QPainter::Antialiasing, true);  //Разрешаем рендэр
    painter.setWindow(-1000,-1000,2000,2000);           // устанавливаем систему координат
    painter.drawRect(-1000,-1000,2000,2000);            // Рисуем прямоугольник
//    painter.setPen(QPen(Qt::black,1,Qt::SolidLine));
//    painter.drawLine(0,-50,0,60);                     //Координаты
//    painter.drawLine(-100,0,50,0);
    painter.setPen(QPen(Qt::blue, 3, Qt::SolidLine));


    for (int i = 0; i < dots_for_draw.size(); i++)
    {

        painter.drawPoint(dots_for_draw.at(i).toPointF());
    }

    for (int i = 1; i < parallels*meridians*2; i+=meridians*2)
    {
        for (int j = 0; j < 2*meridians; j++)
        {
            if(j < 2*meridians-1)
            {
                painter.drawLine(dots_for_draw.at(i+j).toPointF(),dots_for_draw.at(i+1+j).toPointF());
            }
            else
            {
                painter.drawLine(dots_for_draw.at(i+j).toPointF(),dots_for_draw.at(i).toPointF());
            }
        }
    }

    for (int i = 1; i < 2*meridians*(parallels-1)+1; i+=meridians*2)
    {
        for (int j = 0; j < 2*meridians; j++)
        {

            painter.drawLine(dots_for_draw.at(i+j).toPointF(),dots_for_draw.at(i+j+2*meridians).toPointF());

        }
    }

    for (int i = 0; i < meridians*2; i++)
    {
        painter.drawLine(dots_for_draw.at(0).toPointF(),dots_for_draw.at(i+1).toPointF());
        painter.drawLine(dots_for_draw.at(meridians*parallels*2+1).toPointF(),dots_for_draw.at((meridians*parallels*2)-i).toPointF());
    }

}
