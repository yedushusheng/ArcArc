#ifndef USERGUIDIANCE_H
#define USERGUIDIANCE_H

#include <QDialog>

namespace Ui {
class UserGuidiance;
}

class UserGuidiance : public QDialog
{
    Q_OBJECT

public:
    explicit UserGuidiance(QWidget *parent = nullptr);
    ~UserGuidiance();

private:
    Ui::UserGuidiance *ui;
};

#endif // USERGUIDIANCE_H
