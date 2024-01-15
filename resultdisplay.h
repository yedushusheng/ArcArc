#ifndef RESULTDISPLAY_H
#define RESULTDISPLAY_H

//#include "db_connection.h"
#include "sqliteoperator.h"

#include <QDialog>

namespace Ui {
class ResultDisplay;
}

class ResultDisplay : public QDialog
{
    Q_OBJECT

public:
    explicit ResultDisplay(QWidget *parent = nullptr);
    ~ResultDisplay();

    void SetResult(CHI_Data &data);

private:
    Ui::ResultDisplay *ui;
};

#endif // RESULTDISPLAY_H
