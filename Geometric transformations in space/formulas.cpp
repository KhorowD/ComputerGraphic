//Формулы необходимые для рассчета

#include <QMatrix4x4>
#include <qmath.h>

QMatrix4x4 rotate_Oz(double phi)
{
    float m_11 = cosf(phi);
    float m_12 = sinf(phi);
    float m_21 = -sinf(phi);
    float m_22 = cosf(phi);
    QMatrix4x4 mtx = QMatrix4x4(m_11,m_12,0,0,\
                                m_21,m_22,0,0,\
                                0, 0, 1, 0,\
                                0, 0, 0, 1);




    return mtx;
}

QMatrix4x4 rotate_Ox(double phi)
{
    float m_22 = cosf(phi);
    float m_23 = sinf(phi);
    float m_32 = -sinf(phi);
    float m_33 = cosf(phi);
    QMatrix4x4 mtx = QMatrix4x4(1, 0, 0, 0,\
                                0,m_22,m_23,0,\
                                0, m_32, m_33, 0,\
                                0, 0, 0, 1);


    return mtx;
}

QMatrix4x4 rotate_Oy(double phi)
{
    float m_11 = cosf(phi);
    float m_13 = -sinf(phi);
    float m_31 = sinf(phi);
    float m_33 = cosf(phi);
    QMatrix4x4 mtx = QMatrix4x4(m_11, 0, m_13, 0,\
                                0, 1, 0, 0,\
                                m_31, 0, m_33, 0,\
                                0, 0, 0, 1);


    return mtx;
}

QMatrix4x4 transfer(float a, float b, float c)
{
    QMatrix4x4 mtx = QMatrix4x4(1, 0, 0, 0,\
                                0, 1, 0, 0,\
                                0, 0, 1, 0,\
                                a, b, c, 1);



    return mtx;
}

QMatrix4x4 scaling(float Sx, float Sy, float Sz)
{
    QMatrix4x4 mtx = QMatrix4x4(Sx, 0, 0, 0,\
                                0, Sy, 0, 0,\
                                0, 0, Sz, 0,\
                                0, 0, 0, 1);



    return mtx;
}

QMatrix4x4 MatrixViewPoints(double phi, double teta)
{

    float m_11 = sinf(teta)*cosf(phi);
    float m_12 = -sinf(phi);
    float m_13 = -sinf(phi);

    float m_21 = cosf(teta);
    float m_22 = 0;
    float m_23 = sinf(teta);

    float m_31 = sinf(phi);
    float m_32 = cosf(phi);
    float m_33 = cosf(phi);

    QMatrix4x4 mtx = QMatrix4x4(m_11, m_12, m_13, 0,\
                                m_21, m_22, m_23, 0,\
                                m_31, m_32, m_33, 0,\
                                0, 0, 0, 1);





    return mtx;

}
