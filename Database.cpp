#include "Database.h"
#include "QSqlDatabase"

using namespace std;

Database::Database(){
    //objeto de database sendo criado
}

bool Database::Connect(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("Oficina");
    db.setUserName("root");
    //BEWARE CHANGING THIS CLASS NEEDS THE CLIENT TO FIX THE PASSWORD//
    db.setPassword("n0ts3cr3t");
    if(db.open()){
        return true;
    }else{
        return false;
    }
}
