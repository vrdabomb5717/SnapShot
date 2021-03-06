/*
 * SQLiteDB.h
 * A simple C++ class that encapsulates common SQLite functions
 *  Created on: Apr 23, 2011
 *      Author: Jervis Muindi
 */

#ifndef SQLITEDB_H_
#define SQLITEDB_H_


#include <iostream>
#include <sqlite3.h> // SQlite C interface
#include<stdlib.h>
#include<string> // C++ strings

using namespace std;


class SQLiteDB{
public:
	SQLiteDB(string db);
	int insert(string sql);
	int remove(string sql);
	int view(string sql);
	int view_all();
	~SQLiteDB();

private:
	sqlite3 * dbPtr; /* Pointer to the Open DB connection*/


};


#endif /* SQLITEDB_H_ */
