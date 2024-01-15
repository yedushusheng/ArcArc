#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVector>
#include <QMap>

#include <QMainWindow>
#include <QUrl>
#include <QDesktopServices>
#include <QCloseEvent>
#include <QInputDialog>
#include <QWidget>
#include <opencv2/opencv.hpp>
//#include <QtOpenGL/QGLWidget>

#include "about.h"
#include "sqliteoperator.h"
#include "login.h"
#include "password.h"
#include "resultdisplay.h"
#include "datainputpanel.h"
#include "imageprocessing.h"
#include "userguidiance.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *);
    void paintEvent(QPaintEvent *event);

private slots:
    //第1个菜单栏槽函数定义
    void on_action_login_triggered();
    void on_action_password_triggered();

    //第2个菜单栏槽函数定义
    void on_action_L_triggered();
    void on_action_P_triggered();
    void on_action_Q_triggered();

    //第3个菜单栏槽函数定义
    void on_action_zoom_in_triggered();
    void on_action_zoom_out_triggered();
    void on_action_rotate_triggered();
    void on_action_clear_triggered();

    //第4个菜单栏槽函数定义
    void on_local_search_triggered();
    void on_net_search_triggered();

    //第5个菜单栏槽函数定义
    void on_action_about_triggered();
    void on_action_user_triggered();
    void on_action_Qt_triggered();

    //第三方库的相关定义


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
