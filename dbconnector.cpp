#include "dbconnector.h"

QString DBConnector::getEnv(QString nameOfValue){
    QFile envFile(".env");
    envFile.open(QIODevice::ReadOnly);
    QTextStream stream(&envFile);

    QString envValue;

    while(!stream.atEnd()){
        envValue = stream.readLine();
        if(envValue.contains(nameOfValue)){
            envValue = envValue.mid(envValue.indexOf(' ')+1);
            return envValue;
        }
    }
    envFile.close();
}

DBConnector::DBConnector()
{
    db.setHostName(getEnv("hostName"));
    db.setDatabaseName(getEnv("dbName"));
    db.setUserName(getEnv("userName"));
    db.setPassword(getEnv("password"));
}
