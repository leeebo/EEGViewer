#include "handmovement.h"
#include <QGridLayout>
#include <QPixmap>
#include <QVBoxLayout>
#include <QMovie>

HandMovement::HandMovement(QWidget *parent) : QWidget(parent)
{
    setWindowTitle(tr("手部动作展示"));
    label1 = new QLabel(tr("动作一"));
    label1->setScaledContents(true);
    QPixmap *img1 = new QPixmap(":/image/手部动作一.jpg");
    img1->scaled(label1->size(), Qt::KeepAspectRatio);
    label1->setPixmap(*img1);

    label2 = new QLabel(tr("动作二"));
    label2->setScaledContents(true);
    QPixmap *img2 = new QPixmap(":/image/手部动作二.jpg");
    img2->scaled(label2->size(), Qt::KeepAspectRatio);
    label2->setPixmap(*img2);

    label3 = new QLabel(tr("动作三"));
    label4 = new QLabel(tr("动作四"));
    label5 = new QLabel(tr("动作五"));
    label6 = new QLabel(tr("动作六"));
    label7 = new QLabel(tr("动作七"));
    label8 = new QLabel(tr("动作八"));
    label9 = new QLabel(tr("动作九"));

    button1 = new QPushButton(tr("浏览"));
    connect(button1,SIGNAL(clicked()),this,SLOT(button1_clicked()));
    button2 = new QPushButton(tr("浏览"));
    connect(button2,SIGNAL(clicked()),this,SLOT(button2_clicked()));
    button3 = new QPushButton(tr("浏览"));
    button4 = new QPushButton(tr("浏览"));
    button5 = new QPushButton(tr("浏览"));
    button6 = new QPushButton(tr("浏览"));
    button7 = new QPushButton(tr("浏览"));
    button8 = new QPushButton(tr("浏览"));
    button9 = new QPushButton(tr("浏览"));

    QVBoxLayout *layout1 = new QVBoxLayout();
    QVBoxLayout *layout2 = new QVBoxLayout();
    QVBoxLayout *layout3 = new QVBoxLayout();
    QVBoxLayout *layout4 = new QVBoxLayout();
    QVBoxLayout *layout5 = new QVBoxLayout();
    QVBoxLayout *layout6 = new QVBoxLayout();
    QVBoxLayout *layout7 = new QVBoxLayout();
    QVBoxLayout *layout8 = new QVBoxLayout();
    QVBoxLayout *layout9 = new QVBoxLayout();

    layout1->addWidget(label1);
    layout1->addWidget(button1);
    layout2->addWidget(label2);
    layout2->addWidget(button2);
    layout3->addWidget(label3);
    layout3->addWidget(button3);
    layout4->addWidget(label4);
    layout4->addWidget(button4);
    layout5->addWidget(label5);
    layout5->addWidget(button5);
    layout6->addWidget(label6);
    layout6->addWidget(button6);
    layout7->addWidget(label7);
    layout7->addWidget(button7);
    layout8->addWidget(label8);
    layout8->addWidget(button8);
    layout9->addWidget(label9);
    layout9->addWidget(button9);

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addLayout(layout1,0,0,2,2);
    mainLayout->addLayout(layout2,0,2,2,2);
    mainLayout->addLayout(layout3,0,4,2,2);
    mainLayout->addLayout(layout4,2,0,2,2);
    mainLayout->addLayout(layout5,2,2,2,2);
    mainLayout->addLayout(layout6,2,4,2,2);
    mainLayout->addLayout(layout7,4,0,2,2);
    mainLayout->addLayout(layout8,4,2,2,2);
    mainLayout->addLayout(layout9,4,4,2,2);

}

void HandMovement::button1_clicked()
{
    QWidget *w = new QWidget();
    w->setGeometry(300,90,300,300);
    QLabel *label = new QLabel();
    QVBoxLayout *uniqueLayout = new QVBoxLayout(w);
    uniqueLayout->addWidget(label);
    uniqueLayout->setSizeConstraint(QLayout::SetFixedSize);
    QMovie *movie = new QMovie();
    movie->setFileName(":/image/test.gif");
    // 设置缓存模式
    movie->setCacheMode(QMovie::CacheAll);
    // 设置动画大小为标签的大小
    QSize size = label->size();
    movie->setScaledSize(size);
    label->setMovie(movie);
    movie->start();
    w->show();
}

void HandMovement::button2_clicked()
{
    QWidget *w = new QWidget();
    w->setGeometry(300,90,300,300);
    QLabel *label = new QLabel();
    QVBoxLayout *uniqueLayout = new QVBoxLayout(w);
    uniqueLayout->addWidget(label);
    uniqueLayout->setSizeConstraint(QLayout::SetFixedSize);
    QMovie *movie = new QMovie();
    movie->setFileName(":/image/movie.gif");
    // 设置缓存模式
    movie->setCacheMode(QMovie::CacheAll);
    // 设置动画大小为标签的大小
    QSize size = label->size();
    movie->setScaledSize(size);
    label->setMovie(movie);
    movie->start();
    w->show();
}
