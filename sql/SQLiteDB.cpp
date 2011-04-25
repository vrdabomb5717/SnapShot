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
#include <sstream> // for converting ints to strings and vice-versa
#include<time.h> // for getting correct time when adding comments.


using namespace std;

const string comment_delimeter("^^^a94a8fe5ccb19ba61c4c0873d391e987982fbbd3^^^"); // Comment Delimeter

SQLiteDB::SQLiteDB(string db){
	const char * dbfile = db.c_str();
	sqlite3_open(dbfile, &dbPtr); // Open the database connection to file.
}

SQLiteDB::~SQLiteDB(){ // Destructor

	sqlite3_close(dbPtr); // close database connection
}

int SQLiteDB::update(string sql){
	cout << "Trying to update data in SQL Database \n"; // debugging


	const char * update = sql.c_str();
	char * retmsg = (char*) malloc (sizeof(char) * 1024); // return msg if there is an error

/* Parameters for sqlite3_exec
 * -----------------------------
 *	  sqlite3*,                                   An open database
 *	  const char *sql,                            SQL to be evaluated
 *	  int (*callback)(void*,int,char**,char**),   Callback function
 *	  void *,                                     1st argument to callback
 *	  char **errmsg                               Error msg written here
 */
	sqlite3_exec(dbPtr, update, 0,0,&retmsg); // insert into sql table


	if(retmsg != SQLITE_OK){
		cout << "Error Msg: "<<retmsg <<endl;
		return -1;
	} else {
		cout << "Update Succeeded \n\n";
		free(retmsg);
		return 0;
	}

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
		return -1;
	} else {
		cout << "Insert Succeeded \n";
		return 0;
	}

}


int SQLiteDB::remove(string sql){
	const char * select = sql.c_str();
	return 0;
}


int SQLiteDB::addcomment(int id, string comment){

	/// Convert id to a string
	stringstream s;
	s << id;
	string url_id = s.str();

	time_t raw;
	struct tm * timestruct; // a tm object that holds time details
	time ( &raw); // fill in time_t "time" object with current time info
	timestruct = localtime(&raw);  // fill time struct with current time.
	char * ctime = asctime(timestruct); // convert tm struct to a C string with time info in human readable form

	string comment_text;
	comment_text =  "Date: ";
	comment_text += ctime + '\n';
	comment_text += "Comment: " + comment + "\n";
	comment_text += "\n" + comment_delimeter + "\n \n";


	string sql = "UPDATE url SET comments = (comments || '\n" + comment_text + "' ) "  + "WHERE id=" + url_id ;

	cout << "SQL : " << sql <<endl; // debugging only

	int retv =  update(sql);
	if (retv != 0) {
		return -1; // some error occured.
	} else {
		return 0; // no errors
	}

}

int SQLiteDB::addurl(string url, string category, string imagepath, int votes_no){ // Adds Url to DB. Parameters are [string url, string category, string imagepath, int votes];
	// Convert votes to a string
	stringstream s;
	s << votes_no;
	string votes = s.str();
	string views("0");

	string sql = "INSERT INTO url VALUES(NULL, '" + url + "', " + "'" + category + "', " + "'" + imagepath + "', " + "'" + views + "', " + "'" + votes + "', '' ) ";
	cout << "SQL : " << sql << endl; // debugging only.

	int retv = insert(sql);

	if(retv != 0){
		cout << "Some error has occured" << endl;
		return -1;
	} else {
		cout << "Url added " << endl;
		return 0;
	}
}

int SQLiteDB::voteup(int id){

	// Convert id to a string
	stringstream s;
	s << id;
	string url_id = s.str();

	string sql = "UPDATE url SET votes=votes+1 WHERE id=" + url_id ;

	int retv =  update(sql);
	if (retv != 0) {
		return -1; // some error occured.
	} else {
		return 0; // no errors
	}
}

int SQLiteDB::votedown(int id){

	// Convert id to a string
	stringstream s;
	s << id;
	string url_id = s.str();

	string sql = "UPDATE url SET votes=votes-1 WHERE id=" + url_id ;

	int retv =  update(sql);
	if (retv != 0) {
		return -1; // some error occured.
	} else {
		return 0; // no errors
	}
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
		return -1;

	}


	sqlite3_finalize(stmt); // destory statement object to prevent memory leaks.
	return 0;
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
		return -1;

	}

	sqlite3_finalize(stmt); // destory statement object to prevent memory leaks.
	return 0;
}



