#include "subjectmanagement.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

SubjectManagement::SubjectManagement(QWidget *parent) : QWidget(parent)
{
    setWindowTitle(tr("Subject Management"));
    setGeometry(200,100,800,600);
    subjectLabel = new QLabel(tr("SubjectID:"));
    subjectLineEdit = new QLineEdit();
    nameLabel = new QLabel(tr("Name:"));
    nameLineEdit = new QLineEdit();
    genderLabel = new QLabel(tr("Gender:"));
    genderCombox = new QComboBox();
    genderCombox->addItem(tr("Male"));
    genderCombox->addItem(tr("Female"));
    genderCombox->addItem(tr("Both"));
    condition = new QTextEdit();

    QGridLayout *leftTopLayout = new QGridLayout();
    leftTopLayout->addWidget(subjectLabel,0,0);
    leftTopLayout->addWidget(subjectLineEdit,0,1);
    leftTopLayout->addWidget(nameLabel,1,0);
    leftTopLayout->addWidget(nameLineEdit,1,1);
    leftTopLayout->addWidget(genderLabel,2,0);
    leftTopLayout->addWidget(genderCombox,2,1);
    leftTopLayout->addWidget(condition,3,0,2,2);

    text1 = new QTextEdit();
    text2 = new QTextEdit();
    QVBoxLayout *rightTopLayout = new QVBoxLayout();
    rightTopLayout->addWidget(text1);
    rightTopLayout->addWidget(text2);

    OkButton = new QPushButton(tr("OK"));
    CancelButton = new QPushButton(tr("Cancel"));
    QHBoxLayout *buttomLayout = new QHBoxLayout();
    buttomLayout->addStretch(1);
    buttomLayout->addWidget(OkButton);
    buttomLayout->addWidget(CancelButton);
    buttomLayout->addStretch(1);

    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addLayout(leftTopLayout);
    topLayout->addLayout(rightTopLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(buttomLayout);

}
