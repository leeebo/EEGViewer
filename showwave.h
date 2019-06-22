#ifndef SHOWWAVE_H
#define SHOWWAVE_H
#include <QWidget>
#include <QVector>
#include "qcustomplot.h"
#define PLOTBUFSIZE 5000
#define CPLOTSIZE 2

class ShowWave : public QWidget
{
    Q_OBJECT
public:
    explicit ShowWave(QWidget *parent = nullptr);
    void showLine(QCustomPlot *customPlot[CPLOTSIZE], double recvMat[16][5]);
    void showLine(QCustomPlot *customPlot[CPLOTSIZE], uint32_t recvMat[]);
    bool isShowWave;
    int fromB;
    int toT;
    QTimer *timer;
    void setRange();
protected:
    void wheelEvent(QWheelEvent *event);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:

public slots:

private slots:
    void readyShowLine();
    void showLable();

private:
    QCustomPlot *customPlotARY[CPLOTSIZE];
    QGridLayout *mainLayout;
    QComboBox *combox1;
};

#endif // SHOWWAVE_H
