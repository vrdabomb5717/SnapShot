/*
 * SQLiteDB.cpp
 *
 *  Created on: Apr 23, 2011
 *  Author: Jervis Muindi
 *  Desc: A simple C++ class that encapsulates common SQLite functions
 *
 */


#include <iostream>
#include <sqlite3.h>
#include<stdlib.h>
#include "SQLiteDB.h"

using namespace std;

SQLiteDB::SQLiteDB(string db){
	const char * dbfile = db.c_str();
	sqlite3_open(dbfile, &dbPtr); // Open the database connection to file.
}

SQLiteDB::~SQLiteDB(){ // Destructor

	sqlite3_close(dbPtr); // close database connection
}
int SQLiteDB::insert(string sql){
	cout << "Trying to insert data into SQL Database \n"; // debugging


	const char * insert = sql.c_str();
	char * retmsg = (char*) malloc (sizeof(char) * 1024); // return msg if there is an error

/* Parameters for sqlite3_exec
 * -----------------------------
 *	  sqlite3*,                                   An open database
 *	  const char *sql,                            SQL to be evaluated
 *	  int (*callback)(void*,int,char**,char**),   Callback function
 *	  void *,                                     1st argument to callback
 *	  char **errmsg                               Error msg written here
 */
	sqlite3_exec(dbPtr, insert, 0,0,&retmsg); // insert into sql table


	if(retmsg != SQLITE_OK){
		cout << "Error Msg: "<<retmsg <<endl;
	} else {
		cout << "Insert Succeeded \n";
	}

}

int SQLiteDB::remove(string sql){
	const char * select = sql.c_str();

}

int SQLiteDB::view(string sql){
	const char * select = sql.c_str();
	sqlite3_stmt *stmt; /* A ptr to a statement object*/

	sqlite3_prepare_v2(dbPtr,select,-1,&stmt,0); // prep statement

	int cols = sqlite3_column_count(stmt); // get no. of columns in table
	int retv; // return value from SQL db

	while ( SQLITE_ROW == (retv =  sqlite3_step(stmt))){ // get return values from DB, and compare to SQLITE_ROW - the two will match while they are still rows to be retrieved
		// Print out the rows of data.
		for(int i =0; i < cols; i++){
			const char *val = (const char*) sqlite3_column_text(stmt,i);
			const char *colname = sqlite3_column_name(stmt,i);

			cout << colname << " : " << val << endl;
		}

		cout << "=================================" << endl;

	}

	if ( retv == SQLITE_ERROR){
		cout << "Some kind of error has occurred" << endl;

	}


	sqlite3_finalize(stmt); // destory statement object to prevent memory leaks.

}

int SQLiteDB::view_all(){ /* Prints all records in DB */

	char select[32] = "SELECT * from url"; // Select ALL SQL Query
	sqlite3_stmt *stmt; /* A ptr to a statement object*/

	sqlite3_prepare_v2(dbPtr,select,-1,&stmt,0); // prep statement

	int cols = sqlite3_column_count(stmt); // get no. of columns in table
	int retv; // return value from SQL db

	while ( SQLITE_ROW == (retv =  sqlite3_step(stmt))){ // get return values from DB, and compare to SQLITE_ROW - the two will match while they are still rows to be retrieved
		// Print out the rows of data.
		for(int i =0; i < cols; i++){
			const char *val = (const char*) sqlite3_column_text(stmt,i);
			const char *colname = sqlite3_column_name(stmt,i);

			cout << colname << " : " << val << endl;
		}

		cout << "=================================" << endl;

	}

	if ( retv == SQLITE_ERROR){
		cout << "Some kind of error has occurred" << endl;

	}

	sqlite3_finalize(stmt); // destory statement object to prevent memory leaks.
}



