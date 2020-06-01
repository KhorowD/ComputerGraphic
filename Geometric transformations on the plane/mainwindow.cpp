#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(!isEndOFScreen){
        startTimer(50);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{

    QPainter painter(this); //Указываем, что рисуем в текущем окне
    clear(painter);
    initLine(painter); //Отрисовываем линию
    drawFigure(points,painter);//Рисуем фигуру
    points = newPoints(points); //расчитываем новые координаты
//    startTimer(1000);

}

void MainWindow::drawFigure(QVector<Coords> pnts, QPainter &pntr)
{
    QPolygonF polyg;

    if (isFirstIteration){

//        QPolygonF polyg(start_values);

        setupBeginPoints(); //Добавляем начальные точки в массив points

        for (int i = 0; i < points.size(); i++)
        {
            polyg << points[i].point;
        }



        for (int i = 0;i < points.size()-1;i++)
        {

            if((i)%4==left && (i+1)%4 == right)
            {
                pntr.setPen(QPen(Qt::red,3,Qt::SolidLine));
            }
            else
            {
                pntr.setPen(QPen(Qt::black,3,Qt::SolidLine));
            }
            if (i != 3)
            {
                pntr.drawLine(points.at(i).point,points.at(i+1).point);
            }
            else
            {
                pntr.drawLine(points.at(i%4).point,points.at((i+1)%4).point);
            }
        }
//        pntr.setPen(QPen(Qt::red,3,Qt::SolidLine));
//        pntr.drawLine(points.at(3).point,points.at(0).point);

        isFirstIteration = false;
    }
    else
    {
        for (int i = 0; i < pnts.size(); i++)
        {
            polyg << pnts[i].point;
        }
//        for (int i = 0;i < points.size()-1;i++)
//        {
//            pntr.setPen(QPen(Qt::black,3,Qt::SolidLine));
//            pntr.drawLine(points.at(i).point,points.at(i+1).point);
//        }
//        pntr.setPen(QPen(Qt::red,3,Qt::SolidLine));
//        pntr.drawLine(points.at(3).point,points.at(0).point);

        //test
        for (int i = 0;i < points.size();i++)
        {

            if((i)%4==left && (i+1)%4 == right)
            {
                pntr.setPen(QPen(Qt::red,3,Qt::SolidLine));
            }
            else
            {
                pntr.setPen(QPen(Qt::black,3,Qt::SolidLine));
            }
            if (i != 3)
            {
                pntr.drawLine(points.at(i).point,points.at(i+1).point);
            }
            else
            {
                pntr.drawLine(points.at(i%4).point,points.at((i+1)%4).point);
            }
        }
    }

    pntr.setPen(QPen(Qt::black,3,Qt::SolidLine));
//    pntr.drawPolygon(polyg,Qt::OddEvenFill);
}

QVector<MainWindow::Coords> MainWindow::newPoints(QVector<Coords> pnts)
{
    Coords center_point =  {pnts.last().point,1}; //берем точку 100,100 как первую
    int angle = 0; //угол поворота
    int turnNumber = 0; //число поворотов на данный угол, чтобы в сумме было 90 градусов
    if (number_of_itteration % 4 == 0)
    {
        angle = 2;
        turnNumber = 45;
    }
    else
    {
        angle = 5;
        turnNumber = 18;
    }
//    int count = 18;
//    int k = 0;
    if (number_of_rotation < turnNumber){
        for (int i = 0;i<pnts.size()-1;i++)
        {
            Coords tmpPoint = calcPoint(pnts.at(i),center_point,angle);
            pnts[i].point = tmpPoint.point;
        }
        number_of_rotation++;
    }
    else
    {
        number_of_itteration++;
        if(number_of_itteration < 9){
            Coords tmp = pnts.takeAt(3);
            pnts.push_front(tmp);
            number_of_rotation = 0;

            left += 1;
            right += 1;
            left = left % 4;
            right = right % 4;
        }
        else
        {
            isEndOFScreen = true;
        }

    }
    return pnts;

}

void MainWindow::initLine(QPainter &pntr)
{
    pntr.setPen(QPen(Qt::black,Qt::SolidLine)); //выбираем ручку(черная, сплошная линия)
    pntr.drawLine(0,0,width(),height()); //Рисуем  линию, по которой движется наш квадрат

}

MainWindow::Coords MainWindow::calcPoint(MainWindow::Coords pnt, MainWindow::Coords center, float corner)
{

    float x = center.point.x()+(pnt.point.x()-center.point.x())*cos(M_PI*corner/180) - \
            (pnt.point.y()-center.point.y())*sin(M_PI*corner/180);
    float y = center.point.y()+(pnt.point.x()-center.point.x())*sin(M_PI*corner/180) + \
            (pnt.point.y()-center.point.y())*cos(M_PI*corner/180);

    pnt.point.setX(x);
    pnt.point.setY(y);

    return pnt;
}

void MainWindow::setupBeginPoints()
{
    //начальные значения

    points.append({QPointF(50,50),1});
    points.append({QPointF(100,0),1});
    points.append({QPointF(150,50),1});
    points.append({QPointF(100,100),1});




}

void MainWindow::clear(QPainter &pntr)
{
    pntr.eraseRect(0,0,width(),height());

}

void MainWindow::timerEvent(QTimerEvent *)
{
    update();

}

void MainWindow::on_actionrestart_triggered()
{
    points.clear();
    isFirstIteration = true;
    number_of_rotation = 0;
    number_of_itteration = 0;
    isEndOFScreen = false;
    left = 3;
    right = 0;
    update();
}
