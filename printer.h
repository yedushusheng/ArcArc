#ifndef PRINTER_H
#define PRINTER_H

#include <QPrinter>
#include <QPixmap>
#include <QPainter>
#include <QPrintPreviewDialog>
#include <QPrintDialog>
#include <QPageSetupDialog>

class Printer : public QObject
{
    Q_OBJECT
public:
    Printer();
    ~Printer();

public:
    // 打印窗口
    void startPrinter(QPixmap &pixmap);
    // 页面设置
    void startPrinterPage();
    // 开启打印预览
    void startPrintPreview(QPixmap &pixmap);
    // 设置预览内容
    void setPrintPixmap(QPixmap &pixmap);
    // 获取打印内容
    QPixmap getPrintPixmap();
    // 开启打印预览窗口
    void PrintPreview();

private slots:

    void Slot_Preview(QPrinter* printer);

private:
    QPixmap m_Pixmap;		//界面控件内像素
    QPrinter *m_pPrinter;	//打印机
};

#endif // PRINTER_H






