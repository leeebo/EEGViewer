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
extern DOUBLE dataplot1;
extern DOUBLE dataplot2;
extern DOUBLE dataplot3;
extern DOUBLE dataplot4;
extern DOUBLE dataplot5;
extern DOUBLE recv_double_buff[16][5];
QString sChannellist="IED_AF3,IED_F7,IED_F3,IED_FC5,IED_T7,IED_P7,IED_Pz,IED_O1,IED_O2,IED_P8,IED_T8,IED_FC6,IED_F4,IED_F8,IED_AF4,RESULT";
QStringList channellist=sChannellist.split(',');
QString sWavelist="theta,alpha,low_beta,high_beta,gamma";
QStringList wavelist=sWavelist.split(',');

ShowWave::ShowWave(QWidget *parent) : QWidget(parent)
{
    currentData=0;
    isShowWave=FALSE;
    fromB=0;
    toT=100;
    setWindowTitle(tr("波形显示"));
    resize(800,400);

    for(int i=0;i<2*BUFFERSIZE;i++){
        Buff[i]=0;
    }
    currentData = 0;
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

    customPlot = new QCustomPlot();
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::blue));

    customPlot2 = new QCustomPlot();
    customPlot2->addGraph();
    customPlot2->graph(0)->setPen(QPen(Qt::green));

    customPlot3 = new QCustomPlot();
    customPlot3->addGraph();
    customPlot3->graph(0)->setPen(QPen(Qt::red));

    customPlot4 = new QCustomPlot();
    customPlot4->addGraph();
    customPlot4->graph(0)->setPen(QPen(Qt::black));

    customPlot5 = new QCustomPlot();
    customPlot5->addGraph();
    customPlot5->graph(0)->setPen(QPen(Qt::yellow));



    customPlot->resize(300,300);
    customPlot->xAxis->setRange(0,BUFFERSIZE);
    customPlot->yAxis->setRange(fromB,toT);
    customPlot->xAxis->setLabel(tr("time"));
    customPlot->yAxis->setLabel(tr("data"));

    customPlot2->resize(300,300);
    customPlot2->xAxis->setRange(0,BUFFERSIZE);
    customPlot2->yAxis->setRange(fromB,toT);
    customPlot2->xAxis->setLabel(tr("time"));
    customPlot2->yAxis->setLabel(tr("data"));

    customPlot3->resize(300,300);
    customPlot3->xAxis->setRange(0,BUFFERSIZE);
    customPlot3->yAxis->setRange(fromB,toT);
    customPlot3->xAxis->setLabel(tr("time"));
    customPlot3->yAxis->setLabel(tr("data"));

    customPlot4->resize(300,300);
    customPlot4->xAxis->setRange(0,BUFFERSIZE);
    customPlot4->yAxis->setRange(fromB,toT);
    customPlot4->xAxis->setLabel(tr("time"));
    customPlot4->yAxis->setLabel(tr("data"));

    customPlot5->resize(300,300);
    customPlot5->xAxis->setRange(0,BUFFERSIZE);
    customPlot5->yAxis->setRange(fromB,toT);
    customPlot5->xAxis->setLabel(tr("time"));
    customPlot5->yAxis->setLabel(tr("data"));

    mainLayout->addWidget(label1,4,0,1,1);
    mainLayout->addWidget(customPlot,0,1,8,25);
    mainLayout->addWidget(label2,12,0,1,1);
    mainLayout->addWidget(customPlot2,8,1,8,25);
    mainLayout->addWidget(label3,20,0,1,1);
    mainLayout->addWidget(customPlot3,16,1,8,25);
    mainLayout->addWidget(label4,28,0,1,1);
    mainLayout->addWidget(customPlot4,24,1,8,25);
    mainLayout->addWidget(label5,36,0,1,1);
    mainLayout->addWidget(customPlot5,32,1,8,25);
    mainLayout->addWidget(combox1,40,0,1,1);
    showLable();
    timer->start(100);
}


void ShowWave::showLine(QCustomPlot *customPlot)
{
    static QVector<double> Xvalue(BUFFERSIZE);

    static QVector<double> Yvalue(BUFFERSIZE);
    static int buff_counter1=0;
    static double Buff1[BUFFERSIZE*2];
    //无论如何，折线图一次能展示的区域总是有限的,这里一次最多绘制1800个点

    //如果你想图形更加精细，可以多定义些点

       if(buff_counter1<BUFFERSIZE)
       {  //当图形中不足1800个点时，进入到if句里处理
           Xvalue[buff_counter1]=buff_counter1;
           Yvalue[buff_counter1]=Buff1[buff_counter1]=currentData;//将新数据存入缓冲区
           buff_counter1++;
           customPlot->graph(0)->setData(Xvalue,Yvalue);
           customPlot->graph(0)->setName(tr("OutPut"));

           if(isShowWave){
               customPlot->replot();//重绘图形
           }

        }
       else{

           for(int i=0;i<BUFFERSIZE-1;i++)

           {

              Buff1[i]=Buff1[i+1];
              Yvalue[i] =Buff1[i];
           }
           Yvalue[BUFFERSIZE-1]=Buff1[BUFFERSIZE-1]=currentData;

           //缓冲区整体左移，Buff[0]丢弃，Buff[99]接收新数据

           customPlot->graph(0)->setData(Xvalue,Yvalue);

           //X坐标轴跟着平移

           if(isShowWave){
               customPlot->replot();//重绘图形
           }


       }
      //当实时数据超过1800个时，进行以下处理


}
void ShowWave::showLine2(QCustomPlot *customPlot)
{
    static QVector<double> Xvalue(BUFFERSIZE);

    static QVector<double> Yvalue(BUFFERSIZE);
    static int buff_counter2=0;
    static double Buff2[BUFFERSIZE*2];
    //无论如何，折线图一次能展示的区域总是有限的,这里一次最多绘制1800个点

    //如果你想图形更加精细，可以多定义些点

       if(buff_counter2<BUFFERSIZE)
       {  //当图形中不足1800个点时，进入到if句里处理
           Xvalue[buff_counter2]=buff_counter2;
           Yvalue[buff_counter2]=Buff2[buff_counter2]=currentData;//将新数据存入缓冲区
           buff_counter2++;

           customPlot->graph(0)->setData(Xvalue,Yvalue);
           customPlot->graph(0)->setName(tr("OutPut2"));


           if(isShowWave){
               customPlot->replot();//重绘图形
           }

        }
       else{

           for(int i=0;i<BUFFERSIZE-1;i++)

           {

              Buff2[i]=Buff2[i+1];
              Yvalue[i] =Buff2[i];
           }
           Yvalue[BUFFERSIZE-1]=Buff2[BUFFERSIZE-1]=currentData;

           //缓冲区整体左移，Buff[0]丢弃，Buff[99]接收新数据

           customPlot->graph(0)->setData(Xvalue,Yvalue);

           //X坐标轴跟着平移

           if(isShowWave){
               customPlot->replot();//重绘图形
           }


       }
      //当实时数据超过1800个时，进行以下处理


}
void ShowWave::showLine3(QCustomPlot *customPlot)
{
    static QVector<double> Xvalue(BUFFERSIZE);

    static QVector<double> Yvalue(BUFFERSIZE);
    static int buff_counter3=0;
    static double Buff3[BUFFERSIZE*2];
    //无论如何，折线图一次能展示的区域总是有限的,这里一次最多绘制1800个点

    //如果你想图形更加精细，可以多定义些点

       if(buff_counter3<BUFFERSIZE)
       {  //当图形中不足1800个点时，进入到if句里处理
           Xvalue[buff_counter3]=buff_counter3;
           Yvalue[buff_counter3]=Buff3[buff_counter3]=currentData;//将新数据存入缓冲区
           buff_counter3++;

           customPlot->graph(0)->setData(Xvalue,Yvalue);
           customPlot->graph(0)->setName(tr("OutPut3"));

           if(isShowWave){
               customPlot->replot();//重绘图形
           }

        }
       else{

           for(int i=0;i<BUFFERSIZE-1;i++)

           {

              Buff3[i]=Buff3[i+1];
              Yvalue[i] =Buff3[i];
           }
           Yvalue[BUFFERSIZE-1]=Buff3[BUFFERSIZE-1]=currentData;

           //缓冲区整体左移，Buff[0]丢弃，Buff[99]接收新数据

           customPlot->graph(0)->setData(Xvalue,Yvalue);

           //X坐标轴跟着平移

           if(isShowWave){
               customPlot->replot();//重绘图形
           }


       }
      //当实时数据超过1800个时，进行以下处理


}
void ShowWave::showLine4(QCustomPlot *customPlot)
{
    static QVector<double> Xvalue(BUFFERSIZE);

    static QVector<double> Yvalue(BUFFERSIZE);
    static int buff_counter3=0;
    static double Buff3[BUFFERSIZE*2];
    //无论如何，折线图一次能展示的区域总是有限的,这里一次最多绘制1800个点

    //如果你想图形更加精细，可以多定义些点

       if(buff_counter3<BUFFERSIZE)
       {  //当图形中不足1800个点时，进入到if句里处理
           Xvalue[buff_counter3]=buff_counter3;
           Yvalue[buff_counter3]=Buff3[buff_counter3]=currentData;//将新数据存入缓冲区
           buff_counter3++;

           customPlot->graph(0)->setData(Xvalue,Yvalue);
           customPlot->graph(0)->setName(tr("OutPut3"));

           if(isShowWave){
               customPlot->replot();//重绘图形
           }

        }
       else{

           for(int i=0;i<BUFFERSIZE-1;i++)

           {

              Buff3[i]=Buff3[i+1];
              Yvalue[i] =Buff3[i];
           }
           Yvalue[BUFFERSIZE-1]=Buff3[BUFFERSIZE-1]=currentData;

           //缓冲区整体左移，Buff[0]丢弃，Buff[99]接收新数据

           customPlot->graph(0)->setData(Xvalue,Yvalue);

           //X坐标轴跟着平移

           if(isShowWave){
               customPlot->replot();//重绘图形
           }


       }
      //当实时数据超过1800个时，进行以下处理


}
void ShowWave::showLine5(QCustomPlot *customPlot)
{
    static QVector<double> Xvalue(BUFFERSIZE);

    static QVector<double> Yvalue(BUFFERSIZE);
    static int buff_counter3=0;
    static double Buff3[BUFFERSIZE*2];
    //无论如何，折线图一次能展示的区域总是有限的,这里一次最多绘制1800个点

    //如果你想图形更加精细，可以多定义些点

       if(buff_counter3<BUFFERSIZE)
       {  //当图形中不足1800个点时，进入到if句里处理
           Xvalue[buff_counter3]=buff_counter3;
           Yvalue[buff_counter3]=Buff3[buff_counter3]=currentData;//将新数据存入缓冲区
           buff_counter3++;

           customPlot->graph(0)->setData(Xvalue,Yvalue);
           customPlot->graph(0)->setName(tr("OutPut3"));

           if(isShowWave){
               customPlot->replot();//重绘图形
           }

        }
       else{

           for(int i=0;i<BUFFERSIZE-1;i++)

           {

              Buff3[i]=Buff3[i+1];
              Yvalue[i] =Buff3[i];
           }
           Yvalue[BUFFERSIZE-1]=Buff3[BUFFERSIZE-1]=currentData;

           //缓冲区整体左移，Buff[0]丢弃，Buff[99]接收新数据

           customPlot->graph(0)->setData(Xvalue,Yvalue);

           //X坐标轴跟着平移

           if(isShowWave){
               customPlot->replot();//重绘图形
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
void ShowWave::readyShowLine(double recvMat[16][5])
{
    int currentChannel=combox1->currentIndex();

    currentData=recvMat[currentChannel][0];
    showLine(customPlot);
    currentData=recvMat[currentChannel][1];
    showLine2(customPlot2);
    currentData=recvMat[currentChannel][2];
    showLine3(customPlot3);
    currentData=recvMat[currentChannel][3];
    showLine4(customPlot4);
    currentData=recvMat[currentChannel][4];
    showLine5(customPlot5);

}

void ShowWave::readyShowLine()
{
   readyShowLine(recv_double_buff);
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
    customPlot->yAxis->setRange(fromB,toT);
    customPlot2->yAxis->setRange(fromB,toT);
    customPlot3->yAxis->setRange(fromB,toT);
    customPlot4->yAxis->setRange(fromB,toT);
    customPlot5->yAxis->setRange(fromB,toT);
    customPlot->replot();//重绘图形
    customPlot2->replot();//重绘图形
    customPlot3->replot();//重绘图形
    customPlot4->replot();//重绘图形
    customPlot5->replot();//重绘图形


}
