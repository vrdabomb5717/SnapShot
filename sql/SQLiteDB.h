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
	int update(string sql);
	int voteup(int id);
	int votedown(int id);
	int addurl(string url, string category, string imagepath, int votes);
	int addcomment(int id, string comment);
	int addIP(string ip); // updates statistics table.
	int countIP(); // gets a counts of unique IPs.
	int countURLviews(); // gets a count of total url views. [can think of as being number of pages viewed / served.]
	int countSnaps(); // get a count of total snaps taken.
	int incrURLviews(); // increments number of URL viewed
	int incrSnaps(); // increment number of URLs snapshotted
	int countRows(string sql); // counts number of records  in given table as specified in the sql query
	~SQLiteDB();

private:
	sqlite3 * dbPtr; /* Pointer to the Open DB connection*/


};


#endif /* SQLITEDB_H_ */
