#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "formulas.cpp"
#include "paintarea.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    wgt = new PaintArea(this);

    ui->verticalLayout_2->addWidget(wgt);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type())
    {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::makeStartPonints()
{
    if (points.length() != 0)
    {
        points.clear();
    }
    double xy_corner = 180/(float) m;

    float z_level =(float) (2*r)/ (float)(n+1) ;

    float current_level = -r + z_level;

    double alpha = 0;

    alpha = qDegreesToRadians(alpha);

    points.append(QVector4D(0,0,-r,1));

    qDebug() << points.last();

    for (int i = 0; i <n; i++)
    {
        for (int j = 0; j < 2*m; j++)
        {
            double teta_cor = acosf(current_level/r);
            points.append(polarToDecard(r,alpha,teta_cor));
            qDebug() << points.last();
            alpha += qDegreesToRadians(xy_corner);

        }
        current_level += z_level;
        alpha = 0;
    }

    points.append(QVector4D(0,0,r,1));

    qDebug() << points.last();

}



QVector4D MainWindow::polarToDecard(int radius, double alpha, double teta)
{
    float x_coord = radius*sinf(teta)*cosf(alpha);
    float y_coord = radius*sinf(teta)*sinf(alpha);
    float z_coord = radius*cosf(teta);

    return QVector4D(x_coord,y_coord,z_coord,1);
}

void MainWindow::on_pushButton_clicked()
{
    r = ui->r_spinBox->value();
    n = ui->n_spinBox->value();
    m = ui->m_spinBox->value();
    d = ui->d_value->value();

    phi = ui->phi_spinBox->value();
    teta = ui->teta_spinBox->value();

    makeStartPonints();

    QMatrix4x4 viewMatrix = MatrixViewPoints(teta,phi);

    if(ui->radioButton->isChecked())
    {
        qDebug() << wgt->width();
        qDebug() << wgt->height();
        for (int i = 0; i < points.size();i++)
        {
            points.replace(i, points.at(i) * viewMatrix);


            points[i].setZ(points[i].z()+d);
            points[i].setX(points[i].x()*d/points[i].z());
            points[i].setY(points[i].y()*d/points[i].z());

            qDebug() << points.at(i);
        }
    }
    else
    {
        for (int i = 0; i < points.size();i++)
        {
            points.replace(i, points.at(i) * viewMatrix);

        }
    }
    qDebug() << points.length();
    wgt->removePoints();
    wgt->setDots(points);
    wgt->setParams(n,m);
    wgt->show();
    wgt->repaint();
}

void MainWindow::clear(QPainter &pntr)
{
    pntr.eraseRect(0,0,width(),height());
}
