#ifndef HANDMOVEMENT_H
#define HANDMOVEMENT_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class HandMovement : public QWidget
{
    Q_OBJECT
public:
    explicit HandMovement(QWidget *parent = 0);

signals:

public slots:

private slots:
    void button1_clicked();
    void button2_clicked();

private:
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QLabel *label4;
    QLabel *label5;
    QLabel *label6;
    QLabel *label7;
    QLabel *label8;
    QLabel *label9;

    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
    QPushButton *button4;
    QPushButton *button5;
    QPushButton *button6;
    QPushButton *button7;
    QPushButton *button8;
    QPushButton *button9;

};

#endif // HANDMOVEMENT_H
