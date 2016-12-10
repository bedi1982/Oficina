#include "Database.h"
#include "QtSql"
#include "QMessageBox"

using namespace std;

Database::Database(){
    //objeto de database sendo criado
}

bool Database::conectar(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("Oficina");
    db.setUserName("root");
    //BEWARE CHANGING THIS CLASS NEEDS THE CLIENT TO FIX THE PASSWORD//
    //db.setPassword("xxxxxxx");
    if(db.open()){
        return true;
    }else{
        QMessageBox::critical(0,"O banco de dados não está ativo!(classe: database.cpp)", db.lastError().text());
        return false;
    }
}
