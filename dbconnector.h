#ifndef DBCONNECTOR_H
#define DBCONNECTOR_H

#include <QSqlDatabase>
#include <QtSql>

#include <QFile>
#include <QTextStream>

class DBConnector
{
public:
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    DBConnector();
    QString getEnv(QString nameOfValue);
};

#endif // DBCONNECTOR_H
