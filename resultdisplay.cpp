#include "resultdisplay.h"
#include "ui_resultdisplay.h"

ResultDisplay::ResultDisplay(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultDisplay)
{
    ui->setupUi(this);
}

ResultDisplay::~ResultDisplay()
{
    delete ui;
}

void ResultDisplay::SetResult(CHI_Data &data)
{
    //ui->graphicsView->setScreen();
    //创建显示容器
    QGraphicsScene *scene = new QGraphicsScene;

    //向容器中添加文件路径为fileName（QString类型）的文件
    if (data.image.size()) {
        QPixmap outImg;
        outImg.loadFromData(data.image);
        scene->addPixmap(outImg);
        //借助graphicsView（QGraphicsView类）控件显示容器的内容
        ui->graphicsView->setScene(scene);
        //开始显示
        ui->graphicsView->show();
    }

    ui->treeWidget->setHeaderLabel("数据查询结果");
    QTreeWidgetItem *item = ui->treeWidget->topLevelItem(0);       // 获取第一个根节点
    if (item) {
        item->setData(2, Qt::UserRole, "custom data");   // 设置第三列的自定义数据
    }
    // 读取节点数据可以使用item->data(2, Qt::UserRole).toString();
}
