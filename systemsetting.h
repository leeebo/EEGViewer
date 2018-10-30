#ifndef SYSTEMSETTING_H
#define SYSTEMSETTING_H

#include <QDialog>

namespace Ui {
class systemsetting;
}

class systemsetting : public QDialog
{
    Q_OBJECT

public:
    explicit systemsetting(QWidget *parent = 0);
    ~systemsetting();

private:
    Ui::systemsetting *ui;
};

#endif // SYSTEMSETTING_H
