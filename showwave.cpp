#include "showwave.h"
#include <QTime>
#include <QTimer>
#include <QVector>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPainter>
#include <QFont>
#include <QPixmap>
#include <QPen>
#include"EDFlib-master/edflib.h"


extern DOUBLE recv_double_buff[16][5];
QString sChannellist="IED_AF3,IED_F7,IED_F3,IED_FC5,IED_T7,IED_P7,IED_Pz,IED_O1,IED_O2,IED_P8,IED_T8,IED_FC6,IED_F4,IED_F8,IED_AF4,RESULT";
QStringList channellist=sChannellist.split(',');
QString sWavelist="theta,alpha,low_beta,high_beta,gamma";
QStringList wavelist=sWavelist.split(',');

ShowWave::ShowWave(QWidget *parent) : QWidget(parent)
{
    isShowWave=FALSE;
    fromB=0;
    toT=100;
    setWindowTitle(tr("波形显示"));
    resize(800,400);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(readyShowLine()));

    mainLayout = new QGridLayout(this);
    label1 = new QLabel(tr("theta"));
    label1->setFrameStyle(QFrame::Plain|QFrame::Raised); // 设置框架样式
    label1->setAlignment(Qt::AlignCenter);// 设置对齐方式为居中
    label1->setStyleSheet("color:black;");
    label1->setFont(QFont("Timers",9, QFont::Bold));

    label2 = new QLabel(tr("alpha"));
    label2->setFrameStyle(QFrame::Plain|QFrame::Raised); // 设置框架样式
    label2->setAlignment(Qt::AlignCenter);// 设置对齐方式为居中
    label2->setStyleSheet("color:black;");
    label2->setFont(QFont("Timers",9, QFont::Bold));

    label3 = new QLabel(tr("low_beta"));
    label3->setFrameStyle(QFrame::Plain|QFrame::Raised); // 设置框架样式
    label3->setAlignment(Qt::AlignCenter);// 设置对齐方式为居中
    label3->setStyleSheet("color:black;");
    label3->setFont(QFont("Timers",9, QFont::Bold));

    label4 = new QLabel(tr("high_beta"));
    label4->setFrameStyle(QFrame::Plain|QFrame::Raised); // 设置框架样式
    label4->setAlignment(Qt::AlignCenter);// 设置对齐方式为居中
    label4->setStyleSheet("color:black;");
    label4->setFont(QFont("Timers",9, QFont::Bold));

    label5 = new QLabel(tr("gamma"));
    label5->setFrameStyle(QFrame::Plain|QFrame::Raised); // 设置框架样式
    label5->setAlignment(Qt::AlignCenter);// 设置对齐方式为居中
    label5->setStyleSheet("color:black;");
    label5->setFont(QFont("Timers",9, QFont::Bold));

    label6 = new QLabel(tr("CHOOSE"));
    label6->setFrameStyle(QFrame::Plain|QFrame::Raised); // 设置框架样式
    label6->setAlignment(Qt::AlignRight);// 设置对齐方式为居中
    label6->setStyleSheet("color:red;");
    label6->setFont(QFont("Timers",12, QFont::Bold));

    combox1=new QComboBox(this);
    combox1->addItems(channellist);
    connect(combox1,SIGNAL(currentIndexChanged(int)),this,SLOT(showLable()));

    for(int i=0;i<PLOTSIZE;i++)
    {
        QPen penColor[PLOTSIZE]={QPen(Qt::blue),QPen(Qt::green),QPen(Qt::red),QPen(Qt::black),QPen(Qt::yellow)};
        customPlotARY[i]=new QCustomPlot();
        customPlotARY[i]->addGraph();
        customPlotARY[i]->graph(0)->setPen(penColor[i]);
    }


    for(int i=0;i<PLOTSIZE;i++)
    {
        customPlotARY[i]->resize(300,300);
        customPlotARY[i]->xAxis->setRange(0,BUFFERSIZE);
        customPlotARY[i]->yAxis->setRange(fromB,toT);
        customPlotARY[i]->xAxis->setLabel(tr("time"));
        customPlotARY[i]->yAxis->setLabel(tr("data"));
    }

    mainLayout->addWidget(label1,4,0,1,1);
    mainLayout->addWidget(customPlotARY[0],0,1,8,25);
    mainLayout->addWidget(label2,12,0,1,1);
    mainLayout->addWidget(customPlotARY[1],8,1,8,25);
    mainLayout->addWidget(label3,20,0,1,1);
    mainLayout->addWidget(customPlotARY[2],16,1,8,25);
    mainLayout->addWidget(label4,28,0,1,1);
    mainLayout->addWidget(customPlotARY[3],24,1,8,25);
    mainLayout->addWidget(label5,36,0,1,1);
    mainLayout->addWidget(customPlotARY[4],32,1,8,25);
    mainLayout->addWidget(combox1,40,0,1,1);
    showLable();
    timer->start(100);
}

void ShowWave::showLine(QCustomPlot *customPlot[PLOTSIZE],double recvMat[16][5])
{
    int currentChannel=combox1->currentIndex();
    static QVector<QVector<double>> Xvalue(PLOTSIZE);
    static QVector<QVector<double>> Yvalue(PLOTSIZE);
    static uint initFlag=0;
 //   static double Buff1[PLOTSIZE][BUFFERSIZE*2];
    //无论如何，折线图一次能展示的区域总是有限的,这里一次最多绘制1800个点

    //如果你想图形更加精细，可以多定义些点
    if(initFlag==0)
    {
        for(int i=0;i<PLOTSIZE;i++)
        {
            Xvalue[i].resize(BUFFERSIZE);
            Yvalue[i].resize(BUFFERSIZE);
            for(int x=0;x<BUFFERSIZE;x++)
            {
            Xvalue[i][x]=x;
            Yvalue[i][x]=0;
            }
        }
        initFlag=1;

    }

    for(int i=0;i<PLOTSIZE;i++)
    {
        if(Yvalue[i].size()==BUFFERSIZE)
        {
            Yvalue[i].removeFirst();
        }
        Yvalue[i].append(recvMat[currentChannel][i]);//将新数据存入缓冲区

            if(isShowWave)
            {
                customPlot[i]->graph(0)->setData(Xvalue[i],Yvalue[i]);
                //customPlot[i]->graph(0)->setName(tr("OutPut"));
                customPlot[i]->replot();//重绘图形
            }


    }
       //当实时数据超过1800个时，进行以下处理


}

void ShowWave::showLable()
{
    int currentChannel=combox1->currentIndex();
    if(currentChannel<15){
        label1->setText(channellist[currentChannel]+QString("-")+wavelist[0]);
        label2->setText(channellist[currentChannel]+QString("-")+wavelist[1]);
        label3->setText(channellist[currentChannel]+QString("-")+wavelist[2]);
        label4->setText(channellist[currentChannel]+QString("-")+wavelist[3]);
        label5->setText(channellist[currentChannel]+QString("-")+wavelist[4]);


    }
    else if(currentChannel>=15){
        label1->setText(channellist[currentChannel]+QString("-")+QString("result1"));
        label2->setText(channellist[currentChannel]+QString("-")+QString("result2"));
        label3->setText(channellist[currentChannel]+QString("-")+QString("result3"));
        label4->setText("NULL");
        label5->setText("NULL");

    }

}


void ShowWave::readyShowLine()
{

  showLine(customPlotARY,recv_double_buff);
//    槽函数
}

void ShowWave::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/image/background.jpg"));
}

void ShowWave::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        QCursor cursor;
        cursor.setShape(Qt::ClosedHandCursor);
        QApplication::setOverrideCursor(cursor);
    }
}

void ShowWave::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    QApplication::restoreOverrideCursor();
}

void ShowWave::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0)
    {
        toT-=10;
        if(toT>10)
        {
           toT=10;
        }

    }else{
       // fromB--;
        toT+=10;
        if(toT>500){
            toT=500;
        }
    }
    for(int i=0;i<PLOTSIZE;i++)
    {
        customPlotARY[i]->yAxis->setRange(fromB,toT);
        customPlotARY[i]->replot();

    }

}
