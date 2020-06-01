#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QMainWindow>
#include <QWidget>
#include <QPaintEvent>
#include <QVector>
#include <QVector4D>

class PaintArea : public QWidget
{
    Q_OBJECT
public:
    explicit PaintArea(QWidget *parent = nullptr);

    int parallels = 0;
    int meridians = 0;


    QVector<QVector4D> dots_for_draw;
    void setDots(QVector<QVector4D> pnts);
    void setParams(int n, int m);
    void clear(QPainter &pntr);
    void removePoints();


protected:
    void paintEvent(QPaintEvent *event);

signals:

};

#endif // PAINTAREA_H
