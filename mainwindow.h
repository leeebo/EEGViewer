#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QAction>
#include "showwave.h"
#include <QTcpSocket>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createActions();                 //创造动作函数
    void createMenus();                   //创造菜单栏函数
    void createToolBars();                //创造工具栏函数
    void SendTCPData();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

private slots:
/********************************创建相关窗口的槽函数************************/
    void showWavePlot();                  //显示波形窗口
    void showRecordData();                //显示数据记录波形
    void showAboutWindow();               //显示软件信息窗口
    void ReadTCPData();
    void ReadTCPError(QAbstractSocket::SocketError);
/********************************关闭相关窗口的槽函数************************/
    void closeWavePlot();                 //关闭波形显示窗口
    void closeRecordData();               //关闭EMG数据记录窗口
/********************************波形放大、缩小的槽函数************************/
    void waveZoomIn();                    //波形放大
    void waveZoomOut();                   //波形缩小
/********************************波形放大、缩小的槽函数************************/
    void connectToDevice();               //连接设备

private:
    QMenu *FileMenu;                   //患者信息菜单
    QMenu *toolsMenu;                     //工具菜单
    QMenu *viewMenu;                      //视图菜单
    QMenu *helpMenu;                      //帮助菜单
    QAction *openfile;           //打开文件
    QAction *savefile;           //保存文件
    QAction *systemSetting;               //系统设置动作
    QAction *deviceSetting;               //设备设置动作
    QAction *aboutRecoder;                //about动作
    QAction *openAction;                  //打开动作
    QAction *closeAction;                 //关闭动作
    QAction *startAction;                 //展示波形动作
    QAction *stopAction;                  //停止展示波形动作
    QAction *zoomInAction;                //波形放大
    QAction *zoomOutAction;               //波形缩小
    QAction *startRecord;                 //开始记录动作
    QAction *stopRecord;                  //停止记录动作
    QAction *connectAction;               //连接设备动作
    QToolBar *mainTool;                   //主工具栏
    QTcpSocket *tcpClient;
/********************************创建相关类的对象************************/
    ShowWave *waveWindow;                 //波形类对象

};

#endif // MAINWINDOW_H
