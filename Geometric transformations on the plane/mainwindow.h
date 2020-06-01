#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <math.h>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    //создадим структуру в которой хранятся двумерные однородные координаты
    struct Coords{
      QPointF point;
      int scale;
    };
    //создадим таймер для контроля вреемени
    QTimer timer;

    QVector<Coords> points; //массив точек многоугольника
    QVector<QPointF> start_values; //массив начальных значений

    bool isFirstIteration = true;

    int number_of_rotation = 0;
    int number_of_itteration = 0;
    bool isEndOFScreen = false;
    int left = 3;
    int right = 0;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
//protected:
    void paintEvent(QPaintEvent *);
    void drawFigure(QVector<Coords> points, QPainter &pntr); //Рисуем фигуру в текущем положении
    QVector<Coords> newPoints(QVector<Coords> points); //высчитываем новые координаты
    void initLine(QPainter &pntr); //Отрисовка линии, по которой движется фигура
    Coords calcPoint(Coords point, Coords center, float corner); //расчитываем новые координаты для одной точки
    void setupBeginPoints();
    void clear(QPainter &pntr);
    void timerEvent(QTimerEvent *);


private slots:
    void on_actionrestart_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
