#include "mainwindow.h"
#include <QIcon>
#include <QHBoxLayout>
#include <QDialog>


DOUBLE recv_double_buff[16][5]={0};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
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
    connect(tcpClient, SIGNAL(readyRead()), this, SLOT(ReadTCPData()));
    connect(tcpClient, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(ReadTCPError(QAbstractSocket::SocketError)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::ReadTCPData()
{
    QByteArray buffer = tcpClient->readAll();

//    char *sbuffer;
//    char data1[5]="0000";
//    char data2[5]="0000";
//    char data3[5]="0000";
    if(!buffer.isEmpty())
    {
        memcpy(recv_double_buff,buffer,buffer.size());
//        dataplot1=recv_double_buff[15][0];
//        dataplot2=recv_double_buff[15][1];
//        dataplot3=recv_double_buff[15][2];
//        dataplot4=recv_double_buff[15][3];
//        dataplot5=recv_double_buff[15][4];
//        sbuffer=buffer.data();
//        if(sbuffer[0]=='5'&&sbuffer[1]=='A')
//        {

//            data1[0]=sbuffer[4];
//            data1[1]=sbuffer[5];
//            data1[2]=sbuffer[6];
//            data1[3]=sbuffer[7];

//            data2[0]=sbuffer[10];
//            data2[1]=sbuffer[11];
//            data2[2]=sbuffer[12];
//            data2[3]=sbuffer[13];

//            data3[0]=sbuffer[16];
//            data3[1]=sbuffer[17];
//            data3[2]=sbuffer[18];
//            data3[3]=sbuffer[19];

//            dataplot1=atoi(data1);
//            dataplot2=atoi(data2);
//            dataplot3=atoi(data3);


//        }

//       //sbuffer=buffer.toStdString();
    }
}
void MainWindow::ReadTCPError(QAbstractSocket::SocketError)
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

    //    showHandAction = new QAction(QIcon(":/image/handsAction.png"),tr("手部动作展示"),this);
    //    connect(showHandAction,SIGNAL(triggered()),this,SLOT(showHandMovement()));
    //    showHandAction->setStatusTip(tr("展示预识别动作"));

    //    showMuscle = new QAction(QIcon(":/image/Muscle.jpg"),tr("可选择肌肉"),this);
    //    connect(showMuscle,SIGNAL(triggered()),this,SLOT(showMuscleSelect()));
    //    showMuscle->setStatusTip(tr("展示可选择肌肉"));

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
    connect(startRecord,SIGNAL(triggered()),this,SLOT(showRecordData()));
    startRecord->setStatusTip(tr("开始记录"));

    stopRecord = new QAction(QIcon(":/image/Stop.jpg"),tr("StopRecord"),this);
    connect(stopRecord,SIGNAL(triggered()),this,SLOT(closeRecordData()));
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

/********************************创建相关窗口的槽函数************************/

void MainWindow::showSubjectManagement()
{
    subjectWindow = new SubjectManagement();
    subjectWindow->setAttribute(Qt::WA_QuitOnClose,false);
    subjectWindow->show();
}

void MainWindow::showHandMovement()
{
    handWindow = new HandMovement();
    handWindow->setAttribute(Qt::WA_QuitOnClose,false);
    handWindow->setGeometry(200,70,900,600);
    handWindow->setFixedSize(900,600);
    handWindow->show();
}

void MainWindow::showMuscleSelect()
{
    muscleWindow = new MuscleSelect();
    muscleWindow->setAttribute(Qt::WA_QuitOnClose,false);
    muscleWindow->show();
}

void MainWindow::showWavePlot()
{
    waveWindow->isShowWave=true;
}

void MainWindow::showRecordData()
{
    recordWindow = new RecordData();
    recordWindow->setAttribute(Qt::WA_QuitOnClose,false);
    recordWindow->show();
    isOpenRecordWindow=true;
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

void MainWindow::closeRecordData()
{
    if(isOpenRecordWindow){
        recordWindow->close();
        isOpenRecordWindow=false;
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
        offset = event->globalPos() - pos();
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
