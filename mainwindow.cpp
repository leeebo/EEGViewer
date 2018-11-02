#include "mainwindow.h"
#include <QIcon>
#include <QHBoxLayout>
#include <QDialog>
#include"EDFlib-master/edflib.h"
#include<QDebug>

#define edf_chns 80
#define SMP_FREQ 2
#define PERI_TINMER_MS 1000/SMP_FREQ

int hdl;
int edf_buf[edf_chns][SMP_FREQ]={0};
DOUBLE recv_double_buff[16][5]={0};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    recordingData=false;
    setWindowTitle(tr("EEGViewer1.0"));
    statusBar();
    createActions();
    createMenus();
    createToolBars();
    waveWindow = new ShowWave(this);
    setCentralWidget(waveWindow);
    //初始化TCP客户端
    tcpClient = new QTcpSocket(this);   //实例化tcpClient
    tcpClient->abort();                 //取消原有连接
    connect(tcpClient, SIGNAL(readyRead()), this, SLOT(readTCPData()));
    connect(tcpClient, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(readTCPError(QAbstractSocket::SocketError)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::readTCPData()
{
    QByteArray buffer = tcpClient->readAll();
    static int edfcounter=0;
    if(!buffer.isEmpty())
    {
        memcpy(recv_double_buff,buffer,buffer.size());
        if(recordingData)
        {
            if (edfcounter<SMP_FREQ+1)
            {
                if (edfcounter==SMP_FREQ)
                {
                    for(int i=0; i<edf_chns; i++)
                    {
                    edfwrite_digital_samples(hdl, edf_buf[i]); //保存1s一次
                    }
                    edfcounter=0;
                }
                for(int i=0;i<16;i++) //赋值
                {
                    for(int j=0;j<5;j++)
                    {
                      edf_buf[(i*5+j)][edfcounter]=(int)recv_double_buff[i][j];
                    }
                }
                edfcounter++;
            }
            else edfcounter=0;
        }else edfcounter=0;
    }
}
void MainWindow::readTCPError(QAbstractSocket::SocketError)
{
    tcpClient->disconnectFromHost();
    connectAction->setIconText(tr("Connect"));
    startAction->setEnabled(FALSE);
    stopAction->setEnabled(FALSE);
    zoomInAction->setEnabled(FALSE);
    zoomOutAction->setEnabled(FALSE);
    QMessageBox msgBox;
    msgBox.setText(tr("failed to connect server because %1").arg(tcpClient->errorString()));
    //xec();
}
void MainWindow::createActions()
{
    openfile = new QAction(tr("Open"));
    openfile->setShortcut(tr("Ctrl+O"));
   // connect(openfile,SIGNAL(triggered()),this,SLOT(showSubjectManagement()));
    openfile->setStatusTip(tr("打开"));

    savefile = new QAction(tr("Save"));
    savefile->setShortcut(tr("Ctrl+S"));
   // connect(openfile,SIGNAL(triggered()),this,SLOT(showSubjectManagement()));
    savefile->setStatusTip(tr("保存"));

    systemSetting = new QAction(QIcon(":/image/SystemSetting.jpg"),tr("SystemSetting"),this);
    systemSetting->setStatusTip(tr("打开系统设置"));

    deviceSetting = new QAction(QIcon(":/image/DeviceSetting.jpg"),tr("DeviceSetting"),this);
    deviceSetting->setStatusTip(tr("打开设备设置"));

    aboutRecoder = new QAction(QIcon(":/image/aboutRecorder.png"),tr("AboutRecorder"),this);
    connect(aboutRecoder,SIGNAL(triggered()),this,SLOT(showAboutWindow()));
    aboutRecoder->setStatusTip(tr("打开帮助"));

    openAction = new QAction(QIcon(":/image/Open.jpg"),tr("Open"),this);
    openAction->setStatusTip(tr(" 打开"));

    closeAction = new QAction(QIcon(":/image/Close.jpg"),tr("Close"),this);
    connect(closeAction,SIGNAL(triggered()),this,SLOT(close()));
    closeAction->setStatusTip(tr("关闭"));

    startAction = new QAction(QIcon(":/image/Start.jpg"),tr("Start"),this);
    connect(startAction,SIGNAL(triggered()),this,SLOT(showWavePlot()));
    startAction->setEnabled(false);
    startAction->setStatusTip(tr("显示波形"));

    stopAction = new QAction(QIcon(":/image/Stop.jpg"),tr("Stop"),this);
    connect(stopAction,SIGNAL(triggered()),this,SLOT(closeWavePlot()));
    stopAction->setEnabled(false);
    stopAction->setStatusTip(tr("停止波形显示"));

    zoomInAction = new QAction(QIcon(":/image/zoomIn.jpg"),tr("zoomIn"),this);
    connect(zoomInAction,SIGNAL(triggered()),this,SLOT(waveZoomIn()));
    zoomInAction->setEnabled(false);
    zoomInAction->setStatusTip(tr("波形放大"));

    zoomOutAction = new QAction(QIcon(":/image/zoomOut.jpg"),tr("zoomOut"),this);
    connect(zoomOutAction,SIGNAL(triggered()),this,SLOT(waveZoomOut()));
    zoomOutAction->setEnabled(false);
    zoomOutAction->setStatusTip(tr("波形缩小"));

    startRecord = new QAction(QIcon(":/image/StartRecord.jpg"),tr("StartRecord"),this);
    connect(startRecord,SIGNAL(triggered()),this,SLOT(recordData()));
    startRecord->setStatusTip(tr("开始记录"));

    stopRecord = new QAction(QIcon(":/image/Stop.jpg"),tr("StopRecord"),this);
    connect(stopRecord,SIGNAL(triggered()),this,SLOT(stopRecordData()));
    stopRecord->setStatusTip(tr("停止记录"));

    connectAction = new QAction(QIcon(":/image/connect.jpg"),tr("Connect"),this);
    connect(connectAction,SIGNAL(triggered()),this,SLOT(connectToDevice()));
    connectAction->setStatusTip(tr("连接设备"));
}



void MainWindow::createMenus()
{
    FileMenu = menuBar()->addMenu(tr("Files"));
    FileMenu->addAction(openfile);
    FileMenu->addAction(savefile);

    toolsMenu = menuBar()->addMenu(tr("Tools"));
    toolsMenu->addAction(systemSetting);
    toolsMenu->addAction(deviceSetting);

    viewMenu = menuBar()->addMenu(tr("View"));
    viewMenu->addAction(zoomInAction);
    viewMenu->addAction(zoomOutAction);

    helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(aboutRecoder);
}

void MainWindow::createToolBars()
{
    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    mainTool = addToolBar(tr("MainTool"));
    mainTool->addAction(openAction);
    mainTool->addAction(closeAction);
    mainTool->addSeparator();
    mainTool->addAction(startAction);
    mainTool->addAction(stopAction);
    mainTool->addAction(zoomInAction);
    mainTool->addAction(zoomOutAction);
    mainTool->addSeparator();
    mainTool->addAction(startRecord);
    mainTool->addAction(stopRecord);
    mainTool->addSeparator();
    mainTool->addAction(connectAction);
}

void MainWindow::initEdfwrite()
{
    int i;
    QString filename;
    char*  chfilename;
    QString sChannellist="IED_AF3,IED_F7,IED_F3,IED_FC5,IED_T7,IED_P7,IED_Pz,IED_O1,IED_O2,IED_P8,IED_T8,IED_FC6,IED_F4,IED_F8,IED_AF4,RESULT";
    QStringList channellist=sChannellist.split(',');
    QString sWavelist="theta,alpha,low_beta,high_beta,gamma";
    QStringList wavelist=sWavelist.split(',');
    QString sWavelist2="power,smooth,activity,trigger,NULL";
    QStringList wavelist2=sWavelist2.split(',');
    QString channelLable;
    char*  chchannelLable;
    QDateTime wait_t = QDateTime::currentDateTime();

    filename="C:/haitian/recordFES-"+wait_t.toString("yyMMdd-HHmmss")+".edf";
    QByteArray ba = filename.toLatin1(); // must
    chfilename=ba.data();
    hdl = edfopen_file_writeonly(chfilename, EDFLIB_FILETYPE_EDFPLUS, edf_chns);

    if(hdl<0)
    {
        qDebug()<< "error: edfopen_file_writeonly()\n";
        return;
    }

    for(i=0; i<edf_chns; i++)
    {
        if(edf_set_samplefrequency(hdl, i, SMP_FREQ))
        {
            qDebug()<< "error: edf_set_samplefrequency()\n";
            return;
        }
    }

    for(i=0; i<edf_chns; i++)
    {
        if(edf_set_physical_maximum(hdl, i, 10000))  //10000可以 50000不行100000不行
        {
            qDebug()<< "error: edf_set_physical_maximum()\n";
            return;
        }
    }

    for(i=0; i<edf_chns; i++)
    {
        if(edf_set_digital_maximum(hdl, i, 10000))
        {
            qDebug()<< "error: edf_set_digital_maximum()\n";
            return;
        }
    }

    for(i=0; i<edf_chns; i++)
    {
        if(edf_set_digital_minimum(hdl, i, -10000))
        {
            qDebug()<< "error: edf_set_digital_minimum()\n";
            return;
        }
    }

    for(i=0; i<edf_chns; i++)
    {
        if(edf_set_physical_minimum(hdl, i, -10000))
        {
            qDebug()<< "error: edf_set_physical_minimum()\n";
            return;
        }
    }


    for(i=0; i<edf_chns; i++)
    {
        if(i<75)
        {
          channelLable=channellist[(i/5)]+wavelist[(i%5)];
        }
        else channelLable=channellist[(i/5)]+wavelist2[(i%5)];
        ba = channelLable.toLatin1(); // must
        chchannelLable=ba.data();
        edf_set_label(hdl, i, chchannelLable);
    }

//    for(i=0; i<edf_chns; i++)
//    {
//        if(edf_set_physical_dimension(hdl, i, ""))//mV
//        {
//            QDebug("error: edf_set_physical_dimension()\n");

//            return(1);
//        }
//    }

    return ;

}

/********************************创建相关窗口的槽函数************************/


void MainWindow::showWavePlot()
{
    waveWindow->isShowWave=true;
}

void MainWindow::recordData()
{
    if(recordingData!=true){

      initEdfwrite();
      recordingData=true;
    }
    else{


    }

}

void MainWindow::showAboutWindow()
{
    QDialog *aboutWindow = new QDialog();
    aboutWindow->setGeometry(300,300,300,100);
    aboutWindow->show();
}

/********************************关闭相关窗口的槽函数************************/

void MainWindow::closeWavePlot()
{
    waveWindow->isShowWave=false;
}

void MainWindow::stopRecordData()
{
    if(recordingData)
    {

        recordingData=false;
        edfclose_file(hdl);
    }


}

/********************************波形放大缩小的槽函数************************/
void MainWindow::waveZoomIn()
{
//    //waveWindow->fromB++;
//    waveWindow->toT-=10;
//    if(waveWindow->toT<0){
//        waveWindow->toT=0;
//    }
}

void MainWindow::waveZoomOut()
{
//    //waveWindow->fromB--;
//    waveWindow->toT+=10;
//    if(waveWindow->toT>500){
//        waveWindow->toT=500;
//    }
}

/********************************连接设备的槽函数************************/
void MainWindow::connectToDevice()
{
    if(startAction->isEnabled()==FALSE)
    {
        tcpClient->connectToHost("127.0.0.1", 4235);
        if (tcpClient->waitForConnected(2000))  // 连接成功则进入if{}
        {
          connectAction->setIconText(tr("Disconnect"));
          startAction->setEnabled(true);
          stopAction->setEnabled(true);
          zoomInAction->setEnabled(true);
          zoomOutAction->setEnabled(true);
        }



    }
    else
    {
        tcpClient->disconnectFromHost();
                if (tcpClient->state() == QAbstractSocket::UnconnectedState||tcpClient->waitForDisconnected(3000))  //已断开连接则进入if{}
                {
                    connectAction->setIconText(tr("Connect"));
                    startAction->setEnabled(FALSE);
                    stopAction->setEnabled(FALSE);
                    zoomInAction->setEnabled(FALSE);
                    zoomOutAction->setEnabled(FALSE);
                }

    }

}

/********************************相关鼠标事件*******************************/

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        QCursor cursor;
        cursor.setShape(Qt::ClosedHandCursor);
        QApplication::setOverrideCursor(cursor);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    QApplication::restoreOverrideCursor();
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        if(windowState() != Qt::WindowFullScreen)
            setWindowState(Qt::WindowFullScreen);
        else setWindowState(Qt::WindowNoState);
    }
}
