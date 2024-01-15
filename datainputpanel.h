#ifndef DATAINPUTPANEL_H
#define DATAINPUTPANEL_H

//#include "db_connection.h"
#include "sqliteoperator.h"
#include "imageprocessing.h"

#include <QDialog>
#include <QGraphicsScene>
#include <QImage>
#include <QGraphicsView>
#include <QSize>

namespace Ui {
class DataInputPanel;
}

class DataInputPanel : public QDialog
{
    Q_OBJECT

public:
    explicit DataInputPanel(QWidget *parent = nullptr);
    ~DataInputPanel();

    // decode imge metadata info
    void GetImageBasicInfo();
    void GetImageSizeInfo();
    void GetImageLocationInfo();
    void GetImageDescription();

    // set Graphics View info
    QImage SetAdaptiveDisplay(QImage *image);
    void SetGraphicsView(QImage *image);
    // load image data info
    void SetImageBasicInfo(qlonglong id, QString &name, QString &type, QString &author,
                            QString &years);
    void SetImageSizeInfo(SIZE_T &size);
    void SetImageLocationInfo(LOACATION_T &location);
    void SetImageDescription(QString &description);

public:
    QImage *image;
private:
    Ui::DataInputPanel *ui;
    CHI_Data *m_data;

private slots:
    void on_ok_pushButton_clicked();
    void on_cancle_pushButton_clicked();
};

#endif // DATAINPUTPANEL_H
