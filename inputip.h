#ifndef INPUTIP_H
#define INPUTIP_H

#include <QDialog>

namespace Ui {
class inputIP;
}

class inputIP : public QDialog
{
    Q_OBJECT

public:
    explicit inputIP(QWidget *parent = 0);
    ~inputIP();
    //int getIP(QString &ip1,int &port1);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
//    QString ip;
//    int port;
    Ui::inputIP *ui;
};

#endif // INPUTIP_H
