#include "Database.h"
#include "QSqlDatabase"
#include "QSqlQuery"
#include "QStandardPaths"
#include "QDebug"
#include "QDir"

using namespace std;

Database::Database(){
    //objeto de database sendo criado
}

bool Database::Connect(){

    QDir().mkpath(QDir::homePath() + "/.Oficina");
    QString db_path = QDir::homePath() + "/.Oficina/Oficina.db";

    if (!QFile::exists(db_path)) {
            QString home_Path = QDir::homePath() + "/.Oficina/Oficina.db";
            QFile::copy("/etc/Oficina/Oficina.db", home_Path);
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    //qDebug() <<db_path;    //current path

    db.setDatabaseName(db_path);
    db.open();

    if(db.isOpen()){
        printf("Database OK\n");
        return true;
    }else {
        printf("Database BAD\n");
        return false;
    }
}
