#ifndef DATABASE_H
#define DATABASE_H

class Database
{
public:
    Database();
    bool Connect();
    bool check_if_database_file_exists();
};

#endif // DATABASE_H
