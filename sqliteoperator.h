#ifndef SQLITEOPERATOR_H
#define SQLITEOPERATOR_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QVariant>

/*
 * Database(SQLite) Interface
*/

// 尺寸信息
typedef struct {
    long chi_length = 0;
    long chi_width = 0;
    long chi_height = 0;
} SIZE_T;

// 经纬度信息
typedef struct {
    QString  city_name;
    float latitude = 0.0;
    float longitude = 0.0;
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
    QString toString() {
        QString buffer;
        buffer += "id:";
        buffer += QString::number(id);
        buffer + "name:";
        buffer + name;
        buffer + "type:";
        buffer + type;
        buffer + "author:";
        buffer += author;
        buffer + "years:";
        buffer += years;
        buffer + "description:";
        buffer += description;
        buffer + "chi_height:";
        buffer += QString::number(size_info.chi_height);
        buffer + "chi_length:";
        buffer += QString::number(size_info.chi_length);
        buffer + "chi_width:";
        buffer += QString::number(size_info.chi_width);
        buffer + "city_name:";
        buffer += location_info.city_name;
        buffer + "latitude:";
        buffer += QString::number(location_info.latitude);
        buffer + "longitude:";
        buffer += QString::number(location_info.longitude);
        buffer += image;
        return buffer;
    }
};

class SqliteOperator
{
public:
    SqliteOperator();

    // 打开数据库
    bool openDb(void);
    // 创建数据表
    void createTable(void);
    // 判断数据表是否存在
    bool isTableExist(QString& tableName);

    // 查询全部数据
    void queryTable(QVector<CHI_Data> &dataArray);
    // 插入数据
    void singleInsertData(CHI_Data &singleData); // 插入单条数据
    void multiInsertData(QList<CHI_Data> &multiData); // 插入多条数据
    // 修改数据
    void updateData(CHI_Data &data);
    // 删除数据
    void deleteData(int id);
    //删除数据表
    void deleteTable(QString& tableName);

    // 关闭数据库
    void closeDb(void);

private:
    QSqlDatabase database;// 用于建立和数据库的连接
};

#endif //  SQLITEOPERATOR_H
