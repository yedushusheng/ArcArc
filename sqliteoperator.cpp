#include "sqliteoperator.h"

// 构造函数中初始化数据库对象，并建立数据库
SqliteOperator::SqliteOperator()
{
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        // 建立和SQlite数据库的连接
        database = QSqlDatabase::addDatabase("QSQLITE");
    }
    // 设置数据库文件的名字
    database.setDatabaseName("chi_decoration.db");
}

// 打开数据库
bool SqliteOperator::openDb()
{
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        // do something
    }

    return true;
}

// 创建数据表
void SqliteOperator::createTable()
{
    // 用于执行sql语句的对象
    QSqlQuery sqlQuery("chi_decoration.db");
    // 构建创建数据库的sql语句字符串
    QString createSql = QString("CREATE TABLE if not exists chi_decoration_info (\
                                id INT PRIMARY KEY,\
                                name varchar(100) NOT NULL,\
                                type varchar(100),\
                                author varchar(100),\
                                years varchar(100),\
                                description text,\
                                chi_length longlong,\
                                chi_width longlong,\
                                chi_height longlong,\
                                city_name varchar(100),\
                                latitude float,\
                                longitude float,\
                                image BLOB)");
    sqlQuery.prepare(createSql);
    // 执行sql语句
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to create table. " << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "Table created!";
    }
}

// 判断数据库中某个数据表是否存在
bool SqliteOperator::isTableExist(QString& tableName)
{
    QSqlDatabase database = QSqlDatabase::database();
    if(database.tables().contains(tableName))
    {
        return true;
    }

    return false;
}

// 查询全部数据
void SqliteOperator::queryTable(QVector<CHI_Data> &dataArray)
{
    QSqlQuery sqlQuery("chi_decoration.db");
    sqlQuery.exec("SELECT * FROM chi_decoration_info");
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
    }
    else
    {
        CHI_Data data;
        while(sqlQuery.next())
        {
            data.id = sqlQuery.value(0).toInt();
            data.name = sqlQuery.value(1).toString();
            data.type = sqlQuery.value(2).toString();
            data.author= sqlQuery.value(3).toString();
            data.years = sqlQuery.value(4).toString();
            data.description = sqlQuery.value(5).toString();
            data.size_info.chi_length = sqlQuery.value(6).toInt();
            data.size_info.chi_width = sqlQuery.value(7).toInt();
            data.size_info.chi_height = sqlQuery.value(8).toInt();
            data.location_info.city_name = sqlQuery.value(9).toString();
            data.location_info.latitude = sqlQuery.value(10).toFloat();
            data.location_info.longitude = sqlQuery.value(11).toFloat();
            data.image = sqlQuery.value(12).toByteArray();
            dataArray.push_back(data);
        }
    }
}

// 插入单条数据
void SqliteOperator::singleInsertData(CHI_Data &singleData)
{
    QSqlQuery sqlQuery("chi_decoration.db");
    sqlQuery.prepare("INSERT INTO chi_decoration_info(id,name,type,author,years,description,chi_height,chi_width,chi_height,city_name,latitude,longitude,image) VALUES(:id,:name,:type,:author,:years,:description,:chi_length,:chi_width,:chi_height,:city_name,:latitude,:longitude,:image)");
    sqlQuery.bindValue(":id", QString::number(singleData.id));
    sqlQuery.bindValue(":name", singleData.name);
    sqlQuery.bindValue(":type", singleData.type);
    sqlQuery.bindValue(":author", singleData.author);
    sqlQuery.bindValue(":years", singleData.years);
    sqlQuery.bindValue(":description", singleData.description);
    sqlQuery.bindValue(":chi_length", QString::number(singleData.size_info.chi_length));
    sqlQuery.bindValue(":chi_width", QString::number(singleData.size_info.chi_width));
    sqlQuery.bindValue(":chi_height", QString::number(singleData.size_info.chi_height));
    sqlQuery.bindValue(":city_name", singleData.location_info.city_name);
    sqlQuery.bindValue(":latitude", singleData.location_info.latitude);
    sqlQuery.bindValue(":longitude", singleData.location_info.longitude);
    sqlQuery.bindValue(":image", singleData.image);

    qDebug() << "Info: Insert into data sql: " << singleData.toString();
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to insert data. " << sqlQuery.lastError();
    }
    else
    {
        // do something
    }
}

// 插入多条数据
void SqliteOperator::multiInsertData(QList<CHI_Data>& multiData)
{
    // 进行多个数据的插入时，可以利用绑定进行批处理
    QSqlQuery sqlQuery("chi_decoration.db");
    sqlQuery.prepare("INSERT INTO chi_decoration_info VALUES(?,?,?)");
    QVariantList idList,nameList;
    for(int i=0; i< multiData.size(); i++)
    {
        //idList <<  QString(multiData.at(i).id);
        nameList << multiData.at(i).name;
    }
    sqlQuery.addBindValue(idList);
    sqlQuery.addBindValue(nameList);

    if (!sqlQuery.execBatch()) // 进行批处理，如果出错就输出错误
    {
        qDebug() << sqlQuery.lastError();
    }
}

// 修改数据
void SqliteOperator::updateData(CHI_Data &data)
{
    QSqlQuery sqlQuery("chi_decoration.db");
    //sqlQuery.prepare("UPDATE chi_decoration_info SET id=?,age=? WHERE id=?");
    //sqlQuery.addBindValue(data.id);
    sqlQuery.addBindValue(data.name);
    sqlQuery.addBindValue(data.type);

    if(!sqlQuery.exec())
    {
        qDebug() << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "updated data success!";
    }
}

// 删除数据
void SqliteOperator::deleteData(int id)
{
    QSqlQuery sqlQuery("chi_decoration.db");

    sqlQuery.exec(QString("DELETE FROM chi_decoration_info WHERE id = %1").arg(id));
    if(!sqlQuery.exec())
    {
        qDebug()<<sqlQuery.lastError();
    }
    else
    {
        qDebug()<<"deleted data success!";
    }
}

//删除数据表
void SqliteOperator::deleteTable(QString& tableName)
{
    QSqlQuery sqlQuery("chi_decoration.db");

    sqlQuery.exec(QString("DROP TABLE %1").arg(tableName));
    if(sqlQuery.exec())
    {
        qDebug() << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "deleted table success";
    }
}

void SqliteOperator::closeDb(void)
{
    database.close();
}
