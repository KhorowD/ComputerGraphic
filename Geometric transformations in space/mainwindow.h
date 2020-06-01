#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QVector>
#include <QVector4D>
#include "paintarea.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    QVector<QVector4D> points;
    double phi; //угол между осями х и у
    double teta; //угол между осями z и у
    int r; // радиус
    int n; // число паралелей
    int m; // число меридианов
    int d; //расстояние до экрана






    void makeStartPonints(); //функция которая создает точки сферы по заданным параметрам

    QVector4D polarToDecard(int radius, double alpha, double teta);


    void clear(QPainter &pntr);

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    PaintArea *wgt;
};
#endif // MAINWINDOW_H
