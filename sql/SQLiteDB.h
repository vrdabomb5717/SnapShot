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
	int getViewCount(int id); // return number of view for given url id
	int increaseViewCount(int id); // increases view count for given url id
	int countSnaps(); // get a count of total snaps taken.

	int incrSnaps(); // increment number of URLs snapshotted
	int countRows(string sql); // counts number of records  in given table as specified in the sql query

	int OLD_countURLviews(); // OLD version - don't use. gets a count of total url views. [can think of as being number of pages viewed / served.]
	int OLD_incrURLviews(); // OLD version - don't use. increments number of URL viewed - OLD version. don't use
	~SQLiteDB();

	/**
	 * TO DO:
	 * - add a get URL id method
	 * - update increment URL final exe program.
	 *
	 *
	 * - TURN OFF PRINT MSGS IN UPDATE & other methods.
	 */



private:
	sqlite3 * dbPtr; /* Pointer to the Open DB connection*/


};


#endif /* SQLITEDB_H_ */
