#include "DatabaseManager.h"
#include "sqlite3.h"
#include <iostream>

const char* databaseName = "database.db";
DatabaseManager* DatabaseManager::instance = 0;

DatabaseManager::DatabaseManager()
{
    db = NULL;
}

DatabaseManager::DatabaseManager(sqlite3* _database)
{
    db = _database;
}

DatabaseManager::~DatabaseManager()
{
    if(instance !=0)
    {
        sqlite3_close(db);
        db = NULL;
        delete instance;
        instance = NULL;
    }
}

sqlite3* DatabaseManager::getDb()
{
    return db;
}


DatabaseManager* DatabaseManager::getInstance()
{
    if(instance == 0)
    {
        sqlite3 *_db;
        char *zErrMsg = 0;
        int rc;
        
        rc = sqlite3_open(databaseName, &_db);
        
        if( rc )
        {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(_db));
        }
        else
        {
            instance = new DatabaseManager(_db);
        }
        
    }
    return instance;
}
