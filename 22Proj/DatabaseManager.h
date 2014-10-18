
#include "sqlite3.h"
#ifndef __DATABASE_MANAGER__
#define __DATABASE_MANAGER__
/*
 The Database filename is set in DatabaseManager.cpp
 To use the database manager:
	DatabaseManager* databaseManager = DatabaseManager::getInstance();
	sqlite3 *db = databaseManager->getDb();
	
 */
class DatabaseManager
{
protected:
    DatabaseManager();
    DatabaseManager(sqlite3* );
    ~DatabaseManager();
public:
    static DatabaseManager* getInstance();
    sqlite3* getDb();
    
private:
    sqlite3 *db;
    static DatabaseManager* instance;
};
#endif
