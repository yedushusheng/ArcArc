#ifndef DB_CONNECTION_H
#define DB_CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include <QtXml/QDomDocument>

using namespace std;
/*
 * Database(SQLite) Interface
*/

// 尺寸信息
typedef struct {
    long chi_length;
    long chi_width;
    long chi_height;
} SIZE_T;

// 经纬度信息
typedef struct {
    QString  city_name;
    float latitude;
    float longitude;
} LOACATION_T;

struct CHI_Data {
    long id;  // timestamp
    QString name;
    QString type; //具体的类别
    QString author; //作者
    QString years; //年代
    QString description;
    SIZE_T size_info;
    LOACATION_T location_info;
    QByteArray image;

    // TODO:add print func for debug
};

static bool createConnection()
{
    //SqlDatabase为实现数据库连接的类
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","connection_create");//创建一个数据库，添加数据库驱动
    db.setDatabaseName("chi_haipai.db");//设置数据库的名字
    if(! db.open())
    {
        QMessageBox::critical(0,QObject::tr("无法加载数据库"),
             QObject::tr("无法建立有效的数据库连接"),QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query(db);//新建一个查询库
    bool ret = query.exec("create table if not exists chi_haipai_struct (id longlong primary key,name varchar(100),type varchar(100),"
                          "author varchar(100), years varchar(100),"
                          "description text, chi_length longlong, chi_width longlong, chi_height longlong, city_name varchar(100),"
                          "latitude float, longitude float, image BLOB)");
    if (!ret) {
        qDebug() << "Failed to create table: " << query.lastError().text();
        QMessageBox::critical(0,QObject::tr("无法创建数据库"),
             QObject::tr("无法创建数据库"),QMessageBox::Cancel);
        return false;
    }
    return true;
}

// 插入数据
static bool insertCHIStruct(CHI_Data &data)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","connection_insert");//创建一个数据库，添加数据库驱动
    db.setDatabaseName("chi_haipai.db");//设置数据库的名字
    if(! db.open())
    {
        QMessageBox::critical(0,QObject::tr("无法加载数据库"),
             QObject::tr("无法建立有效的数据库连接"),QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query;
    // 根据具体的类别插入到不同的库（海派建筑库）
    QString sql = QString("INSERT INTO chi_struct (id, name, type, author, years, description,"
                          "chi_length, chi_width, chi_height, city_name, latitude, longitude, image) "
                          "VALUES (%1, %2, %3, %4, %5, %6, %7, %8, %9, %10, %11, %12, %13)").arg(data.id).
                          arg(data.name).arg(data.type).arg(data.author).arg(data.years).
                          arg(data.description).arg(data.size_info.chi_length).arg(data.size_info.chi_width).arg(data.size_info.chi_height).
                  arg(data.location_info.city_name).arg(data.location_info.latitude).arg(data.location_info.longitude).arg(data.image);
    bool ret = query.exec(sql);
    if (!ret) {
        qDebug() << "Failed to insert data: " << query.lastError().text();
    }
    return ret;
}

// 更新数据(TODO:重载，方便更新不同属性值)
static bool updateCHIStruct(CHI_Data &data)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","connection_update");//创建一个数据库，添加数据库驱动
    db.setDatabaseName("chi_haipai.db");//设置数据库的名字
    if(! db.open())
    {
        QMessageBox::critical(0,QObject::tr("无法加载数据库"),
             QObject::tr("无法建立有效的数据库连接"),QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query;
    QString sql = QString("UPDATE chi_haipai_struct SET description=%1"
                          "WHERE id=%2").arg(data.description).arg(data.id);
    bool ret = query.exec(sql);
    if (!ret) {
        qDebug() << "Failed to update data: " << query.lastError().text();
    }
    return ret;
}

// 删除数据
static bool deleteCHIStruct(int id)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","connection_delete");//创建一个数据库，添加数据库驱动
    db.setDatabaseName("chi_haipai.db");//设置数据库的名字
    if(! db.open())
    {
        QMessageBox::critical(0,QObject::tr("无法加载数据库"),
             QObject::tr("无法建立有效的数据库连接"),QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query;
    QString sql = QString("DELETE FROM chi_struct WHERE id=%1").arg(id);
    bool ret = query.exec(sql);
    if (!ret) {
        qDebug() << "Failed to delete data: " << query.lastError().text();
    }
}

// 查询数据(TODO:需要支持LIKE模糊查询)
static bool queryCHIStruct(QVector<CHI_Data> &data_array)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","connection_select");//创建一个数据库，添加数据库驱动
    db.setDatabaseName("chi_haipai.db");//设置数据库的名字
    if(! db.open())
    {
        QMessageBox::critical(0,QObject::tr("无法加载数据库"),
             QObject::tr("无法建立有效的数据库连接"),QMessageBox::Cancel);
        return false;
    }
    bool ret = true;
    QSqlQuery query("SELECT * FROM chi_haipai_struct");
    data_array.clear();
    while (query.next()) {
        //id, name, type, author, years, description
        //chi_length, chi_width, chi_height, city_name, latitude, longitude, image
        CHI_Data data;
        data.id = query.value(0).toInt();
        data.name = query.value(1).toString();
        data.type = query.value(2).toString();
        data.author = query.value(3).toString();
        data.years = query.value(4).toString();
        data.description = query.value(5).toString();
        data.size_info.chi_height = query.value(6).toInt();
        data.size_info.chi_length = query.value(7).toInt();
        data.size_info.chi_width = query.value(8).toInt();
        data.location_info.city_name = query.value(9).toString();
        data.location_info.latitude = query.value(10).toInt();
        data.location_info.longitude = query.value(11).toInt();
        data.image = query.value(12).toByteArray();
        data_array.push_back(data);
    }
    return ret;
}

bool static createXml()
{
    QFile file("chi_haipai_struct_analyze.xml");//创建一个xml文件
    if(file.exists())
        return true;
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))//以只写方式打开，且清零以前的信息
        return false;
    QDomDocument doc;//新建一个QDomDocument类对象，它代表一个xml文件
    QDomProcessingInstruction instruction;//添加处理指令
    instruction = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);//xml文件版本等信息
    QDomElement root = doc.createElement(QString("分析结果："));
    doc.appendChild(root);//增加根目录
    QTextStream out(&file);//指定文本流
    doc.save(out, 4);//将xml文档保存到文件data.xml文件中，4表示子元素缩进字符数
    file.close();

    return true;
}

#endif // DB_CONNECTION_H
