#ifndef SUBJECTMANAGEMENT_H
#define SUBJECTMANAGEMENT_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QRadioButton>
#include <QPushButton>
#include <QTextEdit>

class SubjectManagement : public QWidget
{
    Q_OBJECT
public:
    explicit SubjectManagement(QWidget *parent = 0);

private:
    QLabel *subjectLabel;
    QLineEdit *subjectLineEdit;

    QLabel *nameLabel;
    QLineEdit *nameLineEdit;

    QLabel *genderLabel;
    QComboBox *genderCombox;

    QTextEdit *condition;
    QTextEdit *text1;
    QTextEdit *text2;

    QPushButton *OkButton;
    QPushButton *CancelButton;

};

#endif // SUBJECTMANAGEMENT_H
