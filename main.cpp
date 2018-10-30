#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::addLibraryPath("./plugins");
    MainWindow w;
    w.setGeometry(100,40,1200,660);
    w.setAttribute(Qt::WA_QuitOnClose);
    w.show();

    return a.exec();
}
