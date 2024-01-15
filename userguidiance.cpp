#include "userguidiance.h"
#include "ui_userguidiance.h"

UserGuidiance::UserGuidiance(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserGuidiance)
{
    ui->setupUi(this);
}

UserGuidiance::~UserGuidiance()
{
    delete ui;
}
