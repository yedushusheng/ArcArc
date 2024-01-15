#include "printer.h"

Printer::Printer() :m_pPrinter(NULL)
{
    if(m_pPrinter == NULL)
        m_pPrinter = new QPrinter;
}

Printer::~Printer()
{
    if (m_pPrinter != nullptr)
        delete m_pPrinter;
    m_pPrinter = NULL;
}

void Printer::startPrinter(QPixmap &pixmap)
{
    QPrinter printer(QPrinter::ScreenResolution);
    QPrintDialog printDialog(&printer);
    if (printDialog.exec() == QDialog::Accepted) {
        QPainter painterPixmap;
        painterPixmap.begin(&printer);
        painterPixmap.drawPixmap(0, 0, pixmap);
        painterPixmap.end();
    }
}

void Printer::startPrinterPage()
{
    QPrinter printer;
    QPageSetupDialog pageSetUpdlg(&printer);
    if (pageSetUpdlg.exec() == QDialog::Accepted)
    {
        //printer.setOrientation(QPrinter::Landscape);
    }
    else
    {
        //printer.setOrientation(QPrinter::Portrait);
    }
}

void Printer::startPrintPreview(QPixmap &pixmap)
{
    if (pixmap.isNull())
        return;
    setPrintPixmap(pixmap);
    PrintPreview();
}

void Printer::setPrintPixmap(QPixmap &pixmap)
{
    m_Pixmap = pixmap;
}

QPixmap Printer::getPrintPixmap()
{
    return m_Pixmap;
}

void Printer::PrintPreview()
{
    QPrinter printer;
    QPrintPreviewDialog previewDialog(&printer);
    connect(&previewDialog, SIGNAL(paintRequested(QPrinter*)), this, SLOT(Slot_Preview(QPrinter*)));
    previewDialog.exec();
}

void Printer::Slot_Preview(QPrinter* printer)
{
    QPainter painterPixmap;
    painterPixmap.begin(printer);
    painterPixmap.drawPixmap(0, 0, getPrintPixmap());
    painterPixmap.end();
}

