#include "inputip.h"
#include "ui_inputip.h"
extern QString ip;
extern int port;
inputIP::inputIP(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inputIP)
{
    ui->setupUi(this);
}

inputIP::~inputIP()
{
    delete ui;
}

//int inputIP::getIP(QString &ip1, int &port1)
//{
//    ip1=this->ip;
//    port1=this->port;
//    return 1;

//}

void inputIP::on_pushButton_clicked()
{
   ip=ui->lineEdit_IP->text();
   port=(ui->lineEdit_2_PORT->text().toInt());
   close();
}

void inputIP::on_pushButton_2_clicked()
{
    close();
}
