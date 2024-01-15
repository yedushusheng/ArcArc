#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore>
#include <QFileDialog>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QStringList>
#include <QMessageBox>
//#include <QtCore5Compat/QTextCodec>
#include <QPainter>
#include <QPaintDevice>
#include <QMouseEvent>
#include <QProcess>
#include <QProgressDialog>
#include <QMap>
#include <QTextStream>
#include <QDataStream>
#include <qmath.h>

//数据库相关
#include <QSqlDatabase>
#include <QDebug>
#include <QStringList>
#include <QVariant>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlDriver>
#include <QSqlError>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    //srand(QDateTime::currentDateTime().toTime_t());
    ui->setupUi(this);
    setWindowTitle(QObject::tr("海派建筑图像文化遗产数据库"));

    //QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    resize(1000,500);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::paintEvent(QPaintEvent *event)
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //    QMessageBox msgBox;
    //    msgBox.question(this,QObject::tr("提示"),QObject::tr("确定退出程序吗?"),QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
    //    //添加判断处理程序
}

/*
 * 第一个菜单栏槽函数：登陆(L)
*/
// 登陆(L) -> 用户登陆
void MainWindow::on_action_login_triggered()
{
    login *customer = new login;
    customer->show();
}

// 登陆(L) -> 修改密码
void MainWindow::on_action_password_triggered()
{
    password *changepass = new password;
    changepass->show();
}

/*
 * 第二个菜单栏槽函数：文件(F)
*/
// 文件(F) -> 加载(L)
void MainWindow::on_action_L_triggered()
{
    //文件选择对话框
    QString fileName = QFileDialog::getOpenFileName(this,QObject::tr("文件选择对话框"),
                                                          "F:",QObject::tr("图像文件(*.*)"));
    //判断文件是否选择，并给出提示信息对话框
    if(fileName.length()==0)//or fileName.isEmpty()
    {
        QMessageBox::information(NULL,QObject::tr("文件选择"),
                                 QObject::tr("请选择图像文件！"));
    }
    else
    {
        QMessageBox::information(NULL,QObject::tr("文件选择"),
                                 QObject::tr("你已选择图像文件：")+fileName);

        /* 解析文件的基本信息并持久化
         * 1.图像的拍摄时间
         * 2.图像格式
         * 3.图像的经纬度信息
        */
        DataInputPanel *data_input_palel_dialog = new DataInputPanel;
        // 将图像输出到用户面板上
        data_input_palel_dialog->show();
        if(data_input_palel_dialog->image->load(fileName))
        {
            data_input_palel_dialog->SetGraphicsView(data_input_palel_dialog->image);
        }
    }
    /*
    // 数据持久化到SQLite
    if (createConnection()) return;
    CHI_Data data;

    data.id = 1;
    data.name = "鸱吻";
    data.author = "未知";
    data.description = "明代宫廷建筑饰品";
    data.size_info.chi_height = 1;
    data.size_info.chi_length = 2;
    data.size_info.chi_width = 3;
    qDebug() << "insert chi_struct data begin";
    insertCHIStruct(data);
    qDebug() << "insert chi_struct data finish";
    */

    // for debug
    /*
    QVector<CHI_Data> data_array;
    qDebug() << "select chi_struct data begin";
    queryCHIStruct(data_array);
    qDebug() << "select chi_struct data finish";
    for (size_t i = 0; i < data_array.size(); i++) {
        CHI_Data tmp_data = data_array[i];
        qDebug() << "select chi_struct data: " << tmp_data.author << tmp_data.description;
        qDebug() << "select chi_struct data have result";
    }
    */
}

// 文件(F) -> 打印(P)
void MainWindow::on_action_P_triggered()
{

}

// 文件(F) -> 退出(Q)
void MainWindow::on_action_Q_triggered()
{
//    qDebug()<<"quit";
}


/*
 * 第三个菜单栏槽函数：编辑(E)
*/
// 编辑(E) -> 放大
void MainWindow::on_action_zoom_in_triggered()
{

}

// 编辑(E) -> 缩小
void MainWindow::on_action_zoom_out_triggered()
{

}

// 编辑(E) -> 旋转
void MainWindow::on_action_rotate_triggered()
{

}

// 编辑(E) -> 清除
void MainWindow::on_action_clear_triggered()
{

}

/*
 * 第四个菜单栏槽函数：检索(S)
*/
// 检索(S) -> 本地检索
void MainWindow::on_local_search_triggered()
{
    /* 数据库检索相关记录并展示
     * 如果是多条记录则按照网页的方式展示
    */
    QVector<CHI_Data> results;
    // TODO:add new database intrerface (SELECT)
    SqliteOperator sql_operator;
    sql_operator.openDb();
    sql_operator.queryTable(results);

    ResultDisplay *result_display = new ResultDisplay;
    CHI_Data data;
    for (size_t i = 0; i < results.size(); i++)
    {

        data.id = results[i].id;
        data.name = results[i].name;
        data.type = results[i].type;
        data.author = results[i].author;
        data.years =  results[i].years;
        data.description = results[i].description;
        data.size_info.chi_height = results[i].size_info.chi_height;
        data.size_info.chi_length = results[i].size_info.chi_length;
        data.size_info.chi_width = results[i].size_info.chi_width;
        data.location_info.city_name = "上海";
        data.location_info.latitude = 12;
        data.location_info.longitude = 23;
        data.image = results[i].image;
    }
    result_display->SetResult(data);
    result_display->show();
}

// 检索(S) -> 网络检索
void MainWindow::on_net_search_triggered()
{
    // 链接ChatGPT或者google
    QDesktopServices::openUrl(QUrl("https://www.google.com.hk/"));
}

/*
 * 第五个菜单栏槽函数：帮助(H)
*/
// 帮助(H) -> 关于软件
void MainWindow::on_action_about_triggered()
{
    about *about_dialog = new about;
    about_dialog->show();//unmodal dialog,即非模态对话框
    //dialog->exec();//modal dialog,模态对话框
}

// 帮助(H) -> 用户手册
void MainWindow::on_action_user_triggered()
{
    UserGuidiance *user_guidiance_dialog = new UserGuidiance;
    user_guidiance_dialog->show();//unmodal dialog,即非模态对话框
    //dialog->exec();//modal dialog,模态对话框
}

// 帮助(H) -> 关于网站
void MainWindow::on_action_Qt_triggered()
{
    //QDesktopServices::openUrl(QUrl("http://www.qt.io/"));
}
