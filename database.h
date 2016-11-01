#ifndef DATABASE_H
#define DATABASE_H

class Database
{
public:
    Database();
    QString _nome;
    QString _cidade;
    QString _usuario;

    bool conectar();
    bool create_tables(QString nome, QString cidade);
    QString resultado(void);
};

#endif // DATABASE_H
