#include "datainputpanel.h"
#include "ui_datainputpanel.h"

DataInputPanel::DataInputPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataInputPanel)
{
    image = new QImage();
    ui->setupUi(this);
    setWindowTitle(QObject::tr("加载图片"));
}

DataInputPanel::~DataInputPanel()
{
    delete image;
    delete ui;
}

void DataInputPanel::GetImageBasicInfo()
{

}

void DataInputPanel::GetImageSizeInfo()
{

}

void DataInputPanel::GetImageLocationInfo()
{

}

void DataInputPanel::GetImageDescription()
{

}

QImage DataInputPanel::SetAdaptiveDisplay(QImage *image)
{
    // 原始图片大小
    int ori_width = image->size().width();
    int ori_height = image->size().height();

    // 画布大小
    int label_width = ui->graphicsView->size().width();
    int label_height = ui->graphicsView->size().height();
    int pro = -1;		//比例值
    if(ori_width / label_width >= ori_height / label_height )
        pro = ori_width / label_width ;
    else
        pro = ori_height / label_height ;
    // 缩放比例
    int scale_width = ori_width / pro;
    int scale_height = ori_height / pro;
    // 缩放图片
    QImage *scale_image = new QImage();
    *scale_image = image->scaled(scale_width, scale_height, Qt::KeepAspectRatio);

    return *scale_image;
}

void DataInputPanel::SetGraphicsView(QImage *image)
{
    // 自适应显示设置
    QImage adaptive_image = SetAdaptiveDisplay(image);

    // opencv处理图片生成纹理图
    ImageProcessing *image_processing = new ImageProcessing();
    QImage gray_image = image_processing->Gray(adaptive_image);
    //QImage edge_detection_image = image_processing->EdgeDetection(gray_image);
    //QImage mean_filter_image = image_processing->MeanFilter(edge_detection_image);

    // 显示图
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(QPixmap::fromImage(gray_image));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

/* 初始化图片的基本信息
 * 1.ID
 * 2.名称
 * 3.类型
 * 4.作者
 * 5.地区
 * 6.朝代
 * 7.世纪
*/
void DataInputPanel::SetImageBasicInfo(qlonglong id, QString &name, QString &type, QString &author,
                                          QString &region, QString &years, QString &generation)
{
    m_data->id = id;
    m_data->name = name;
    m_data->type = type;
    m_data->author = author;
    m_data->region = region;
    m_data->years = years;
    m_data->generation = generation;
}

/* 初始化图片的尺寸信息:
 * 1.长度
 * 2.宽度
 * 3.高度
*/
void DataInputPanel::SetImageSizeInfo(SIZE_T &size)
{
    m_data->size_info.chi_height = size.chi_height;
    m_data->size_info.chi_length = size.chi_length;
    m_data->size_info.chi_width = size.chi_width;
}

/* 初始化图片的位置信息
 * 1.时区
 * 2.经度
 * 3.维度
*/
void DataInputPanel::SetImageLocationInfo(LOACATION_T &location)
{
    m_data->location_info.city_name = location.city_name;
    m_data->location_info.latitude = location.latitude;
    m_data->location_info.longitude = location.longitude;
}

/* 初始化图片的描述信息
*/
void DataInputPanel::SetImageDescription(QString &description) {
    m_data->description = description;
}


void DataInputPanel::on_ok_pushButton_clicked()
{
    // ID编号
    qlonglong id;
    if(!ui->id_comboBox->currentText().isEmpty())
    {
        id = ui->id_comboBox->currentText().toLongLong();
    }
    // 名称(name)
    QString name;
    if (!ui->name_lineEdit->selectedText().isEmpty())
    {
        name = ui->name_lineEdit->selectedText();
    }
    // 类型(type)
    QString type;
    if (!ui->type_comboBox->currentText().isEmpty())
    {
        type = ui->type_comboBox->currentText();
    }
    // 作者(author)
    QString author;
    if (!ui->author_lineEdit->selectedText().isEmpty())
    {
        author = ui->author_lineEdit->selectedText();
    }
    // 地区(region)
    QString region;
    if (!ui->region_lineEdit->selectedText().isEmpty())
    {
        region = ui->region_lineEdit->selectedText();
    }
    // 朝代(years)
    QString years;
    if (!ui->year_comboBox->currentText().isEmpty())
    {
        years = ui->year_comboBox->currentText();
    }
    // 纪元(generation)
    QString generation;
    if (!ui->generation_comboBox->currentText().isEmpty())
    {
        generation = ui->generation_comboBox->currentText();
    }
    // 尺寸
    qlonglong length;
    qlonglong width;
    qlonglong height;
    if (!ui->size_length_lineEdit->selectedText().isEmpty())
    {
        length = ui->size_length_lineEdit->selectedText().toLongLong();
    }
    if (!ui->size_width_lineEdit->selectedText().isEmpty())
    {
        width = ui->size_width_lineEdit->selectedText().toLongLong();
    }
    if (!ui->size_height_lineEdit->selectedText().isEmpty())
    {
        height = ui->size_height_lineEdit->selectedText().toLongLong();
    }
    // 位置


    // 描述(description)
    QString description;
    if (!ui->description_textEdit->document()->isEmpty())
    {
        description = ui->description_textEdit->document()->toPlainText();
    }

    QMessageBox::information(this, QObject::tr("加载图像信息"), QObject::tr("加载图像信息成功！"), QMessageBox::Ok);
}

void DataInputPanel::on_cancle_pushButton_clicked()
{
    //ui->graphicsView->resizeAnchor();
    ui->id_comboBox->clear();
    ui->name_lineEdit->clear();
    //ui->type_comboBox->clear();
    //ui->author_lineEdit->clear();
    //ui->region_lineEdit->clear();
    ui->year_comboBox->clear();
    ui->generation_comboBox->clear();
    //ui->size_height_lineEdit->clear();
    //ui->size_length_lineEdit->clear();
    //ui->size_width_lineEdit->clear();
    ui->location_comboBox->clear();
    ui->description_textEdit->clear();

}
