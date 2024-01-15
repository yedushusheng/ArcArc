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
    ui->treeWidget->setHeaderLabel("查询结果");
    QTreeWidgetItem *item = ui->treeWidget->topLevelItem(0);       // 获取第一个根节点
    if (item) {
        item->setData(2, Qt::UserRole, "custom data");   // 设置第三列的自定义数据
    }
    // 读取节点数据可以使用item->data(2, Qt::UserRole).toString();
}
