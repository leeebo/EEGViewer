#ifndef SHOWWAVE_H
#define SHOWWAVE_H

#include <QWidget>
#include "qcustomplot.h"
#define BUFFERSIZE 100
#define PLOTSIZE 5
class ShowWave : public QWidget
{
    Q_OBJECT
public:
    explicit ShowWave(QWidget *parent = 0);
    void showLine(QCustomPlot *customPlot[PLOTSIZE], double recvMat[16][5]);
    bool isShowWave;
    int fromB;
    int toT;

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

signals:

public slots:

private slots:
    void readyShowLine();
    void showLable();

private:

    QCustomPlot *customPlotARY[PLOTSIZE];
    QGridLayout *mainLayout;
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QLabel *label4;
    QLabel *label5;
    QLabel *label6;
    QTimer *timer;
    QComboBox *combox1;
    QPoint offset;

};

#endif // SHOWWAVE_H
