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
    db.setPassword("root");
    if(db.open()){
        return true;
    }
    return false;
}
