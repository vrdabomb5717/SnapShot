/*
 * SQLiteDB.cpp
 *
 *  Created on: Apr 23, 2011
 *  Author: Jervis Muindi
 *  Desc: A simple C++ class that encapsulates common SQLite functions
 *
 */

/** URL SQLite Table Schema
 * index value - column name
 * 0 - id
 * 1 - url
 * 2 - category
 * 3 - imagepath
 * 4 - views
 * 5 - votes
 * 6 - comments
 */


#include <iostream>
#include <sqlite3.h>
#include<stdlib.h>
#include "SQLiteDB.h"
#include <sstream> // for converting ints to strings and vice-versa
#include<time.h> // for getting correct time when adding comments.

#define DELIM "==========" // Delimeter to separate one record from another when outputting data from database table


using namespace std;

const string comment_delimeter("^^^^a94a8fe5ccb19ba61c4c0873d391e987982fbbd3^^^^"); // Comment Delimeter

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
		// check if insertion failed due to IP existing already - This is a special case for maintaining uniquness of ips in visitor table
		string uniq = "column ip is not unique";
		string ret(retmsg); // return string error msg
		if(uniq.compare(ret) == 0){
			cout << "IP address exists. Insert skipped.\n";
			return 0;
		}

		// check if insertion failed due to URL already existing.
		uniq = "column url is not unique" ;
		if(uniq.compare(ret) == 0){
			cout << "URL already exists. Insert skipped.\n";
			return 0;
		}

		cout << "Error Msg: "<<retmsg <<endl;
		return -1;

	} else {
		cout << "Insert Succeeded \n";
		return 0;
	}

}


int SQLiteDB::remove(string sql){

	return 0;
}



int SQLiteDB::countSnaps(){
	string sql = "SELECT * FROM stats WHERE id=1"; // ID is always one, since we have data stored only in 1st row

	const char * select = sql.c_str();
	sqlite3_stmt *stmt; /* A ptr to a statement object*/

	sqlite3_prepare_v2(dbPtr,select,-1,&stmt,0); // prep statement


	int retv; // return value from SQL db

	retv =  sqlite3_step(stmt);

	const char *val = (const char*) sqlite3_column_text(stmt,1); // index of value of 1 gives us 'snapcount'. index value of 1 would give 'urlviews'


	if ( retv == SQLITE_ERROR){
		cout << "Some kind of error has occurred" << endl;
		return -1;
	}

	// Convert string to integer //
	string value(val); // convert to a c++ string
	stringstream s(value); /// make stringstream from using the "value" string
	int i;
	s >> i; // convert to integer

	sqlite3_finalize(stmt); // destroy statement object to prevent memory leaks.

	return i; // return the value
}

int SQLiteDB::addIP(string ip){

	string sql = "INSERT INTO visitors VALUES(NULL, '" + ip + "')";

	cout << "SQL : " << sql <<endl; // debugging only

	int retv =  insert(sql);
	if (retv != 0) {
		return -1; // some error occured.
	} else {
		return 0; // no errors
	}
}

int SQLiteDB::getURLinfo(int id){

	stringstream s;
	s << id;
	string url_id = s.str();

	string sql = "SELECT * FROM url WHERE id=" + url_id ; // should give 1 row of data as URL id is unique.

	const char * select = sql.c_str();
	sqlite3_stmt *stmt; /* A ptr to a statement object*/

	sqlite3_prepare_v2(dbPtr,select,-1,&stmt,0); // prep statement

	int cols = sqlite3_column_count(stmt); // get no. of columns in table
	int retv; // return value from SQL db

	retv =  sqlite3_step(stmt); // get the one row of data ( URL id is unique)

	/**URL Table Schema
	 * index value - column name
	 * 0 - id
	 * 1 - url
	 * 2 - category
	 * 3 - imagepath
	 * 4 - views
	 * 5 - votes
	 * 6 - comments
	 */

	for(int i = 0; i < cols - 1; i++) { // cols - 1 so that we skip and don't output comments.
		const char *val = (const char*) sqlite3_column_text(stmt,i); // value in this column
		const char *colname = sqlite3_column_name(stmt,i); // db col name


		cout << colname << " : " << val << endl;  // print the info
	}
	if ( retv == SQLITE_ERROR){
		cout << "-1" << endl;
		cout << "Some kind of error has occurred" << endl;
		return -1;
	}



	sqlite3_finalize(stmt); // destroy statement object to prevent memory leaks.

	return 0; // return the value

}

int SQLiteDB::getURLid(string url) {

	string sql = "SELECT * FROM url WHERE url='" + url + "' LIMIT 1"; // limit by 1 - they should only be one result since URL are unique.

	const char * select = sql.c_str();
	sqlite3_stmt *stmt; /* A ptr to a statement object*/

	sqlite3_prepare_v2(dbPtr,select,-1,&stmt,0); // prep statement

	int retv; // return value from SQL db

	retv =  sqlite3_step(stmt); // get one row of data

	/**URL Table Schema
	 * index value - column name
	 * 0 - id
	 * 1 - url
	 * 2 - category
	 * 3 - imagepath
	 * 4 - views
	 * 5 - votes
	 * 6 - comments
	 */
	const char *val = (const char*) sqlite3_column_text(stmt,0); // 0 -id. see schema above for index value.

	if ( retv == SQLITE_ERROR){
		cout << "-1" << endl;
		cout << "Some kind of error has occurred" << endl;
		return -1;
	}

	cout << val; // print the id

	sqlite3_finalize(stmt); // destroy statement object to prevent memory leaks.

	return 0; // return the value

}


int SQLiteDB::getBottomURLByVote(int n ){ // Get Bottom X URls as determined by number of votes.

	stringstream s;
	s << n;
	string rank = s.str();

	string sql = "SELECT * from url ORDER BY votes ASC LIMIT " + rank; // Order by  votes

	const char * select = sql.c_str();

	sqlite3_stmt *stmt; /* A ptr to a statement object*/

	sqlite3_prepare_v2(dbPtr,select,-1,&stmt,0); // prep statement

	int cols = sqlite3_column_count(stmt); // get no. of columns in table
	int retv; // return value from SQL db

	while ( SQLITE_ROW == (retv =  sqlite3_step(stmt))){ // get return values from DB, and compare to SQLITE_ROW - the two will match while they are still rows to be retrieved
		// Print out the rows of data.
		for(int i =0; i < cols-1; i++){ // cols -1 to skip the comments column
			const char *val = (const char*) sqlite3_column_text(stmt,i);
			const char *colname = sqlite3_column_name(stmt,i);

			cout << colname << " : " << val << endl;
		}

		cout << DELIM << endl; // delimeter has 10 equal signs

	}

	if ( retv == SQLITE_ERROR){
		cout << "Some kind of error has occurred" << endl;
		return -1;

	}

	sqlite3_finalize(stmt); // destory statement object to prevent memory leaks.
	return 0;

}



int SQLiteDB::getBottomURL(int n ){ // Get Bottom X URls as determined by number of views.

	stringstream s;
	s << n;
	string rank = s.str();


	string sql = "SELECT * from url ORDER BY views ASC, votes ASC LIMIT " + rank; // Order by  views and THEN votes. The ASC is needed twice.

	const char * select = sql.c_str();

	sqlite3_stmt *stmt; /* A ptr to a statement object*/

	sqlite3_prepare_v2(dbPtr,select,-1,&stmt,0); // prep statement

	int cols = sqlite3_column_count(stmt); // get no. of columns in table
	int retv; // return value from SQL db

	while ( SQLITE_ROW == (retv =  sqlite3_step(stmt))){ // get return values from DB, and compare to SQLITE_ROW - the two will match while they are still rows to be retrieved
		// Print out the rows of data.
		for(int i =0; i < cols-1; i++){ // cols -1 to skip the comments column
			const char *val = (const char*) sqlite3_column_text(stmt,i);
			const char *colname = sqlite3_column_name(stmt,i);

			cout << colname << " : " << val << endl;
		}

		cout << DELIM << endl; // delimeter has 10 equal signs

	}

	if ( retv == SQLITE_ERROR){
		cout << "Some kind of error has occurred" << endl;
		return -1;

	}

	sqlite3_finalize(stmt); // destory statement object to prevent memory leaks.
	return 0;

}


/**
 * Return the Top X of URLs in the DB.
 * Popularity / Topness of a URL is decided by the number of
 * votes that it has received.
 */

int SQLiteDB::getTopURLByVote(int n){

	stringstream s;
	s << n;
	string rank = s.str();

	// SELECT * from url ORDER BY views DESC LIMIT N
	string sql = "SELECT * from url ORDER BY votes DESC LIMIT " + rank; // Order by  views and THEN votes. The DESC is needed twice.

	const char * select = sql.c_str();

	sqlite3_stmt *stmt; /* A ptr to a statement object*/

	sqlite3_prepare_v2(dbPtr,select,-1,&stmt,0); // prep statement

	int cols = sqlite3_column_count(stmt); // get no. of columns in table
	int retv; // return value from SQL db

	while ( SQLITE_ROW == (retv =  sqlite3_step(stmt))){ // get return values from DB, and compare to SQLITE_ROW - the two will match while they are still rows to be retrieved
		// Print out the rows of data.
		for(int i =0; i < cols-1; i++){ // cols -1 to skip the comments column
			const char *val = (const char*) sqlite3_column_text(stmt,i);
			const char *colname = sqlite3_column_name(stmt,i);

			cout << colname << " : " << val << endl;
		}

		cout << DELIM << endl; // delimeter has 10 equal signs

	}

	if ( retv == SQLITE_ERROR){
		cout << "Some kind of error has occurred" << endl;
		return -1;

	}

	sqlite3_finalize(stmt); // destory statement object to prevent memory leaks.
	return 0;

}





/**
 * Return the Top X of URLs in the DB.
 * Popularity / Topness of a URL is decided by the number of
 * views that it has received. (votes also play a minor part)
 */

int SQLiteDB::getTopURL(int n){

	stringstream s;
	s << n;
	string rank = s.str();

	// SELECT * from url ORDER BY views DESC LIMIT N
	string sql = "SELECT * from url ORDER BY views DESC, votes DESC LIMIT " + rank; // Order by  views and THEN votes. The DESC is needed twice.

	const char * select = sql.c_str();

	sqlite3_stmt *stmt; /* A ptr to a statement object*/

	sqlite3_prepare_v2(dbPtr,select,-1,&stmt,0); // prep statement

	int cols = sqlite3_column_count(stmt); // get no. of columns in table
	int retv; // return value from SQL db

	while ( SQLITE_ROW == (retv =  sqlite3_step(stmt))){ // get return values from DB, and compare to SQLITE_ROW - the two will match while they are still rows to be retrieved
		// Print out the rows of data.
		for(int i =0; i < cols-1; i++){ // cols -1 to skip the comments column
			const char *val = (const char*) sqlite3_column_text(stmt,i);
			const char *colname = sqlite3_column_name(stmt,i);

			cout << colname << " : " << val << endl;
		}

		cout << DELIM << endl; // delimeter has 10 equal signs

	}

	if ( retv == SQLITE_ERROR){
		cout << "Some kind of error has occurred" << endl;
		return -1;

	}

	sqlite3_finalize(stmt); // destory statement object to prevent memory leaks.
	return 0;

}

int SQLiteDB::getURLByCat(string category){

	string sql = "SELECT * from url WHERE category='" + category + "'"; // Select ALL SQL Query

	const char * select = sql.c_str();

	sqlite3_stmt *stmt; /* A ptr to a statement object*/

	sqlite3_prepare_v2(dbPtr,select,-1,&stmt,0); // prep statement

	int cols = sqlite3_column_count(stmt); // get no. of columns in table
	int retv; // return value from SQL db

	while ( SQLITE_ROW == (retv =  sqlite3_step(stmt))){ // get return values from DB, and compare to SQLITE_ROW - the two will match while they are still rows to be retrieved
		// Print out the rows of data.
		for(int i =0; i < cols-1; i++){ // cols -1 to skip the comments column
			const char *val = (const char*) sqlite3_column_text(stmt,i);
			const char *colname = sqlite3_column_name(stmt,i);

			cout << colname << " : " << val << endl;
		}

		cout << DELIM << endl; // delimeter has 10 equal signs

	}

	if ( retv == SQLITE_ERROR){
		cout << "Some kind of error has occurred" << endl;
		return -1;

	}

	sqlite3_finalize(stmt); // destory statement object to prevent memory leaks.
	return 0;


}

int SQLiteDB::getRandURL(int n){

	stringstream s;
	s << n;
	string rank = s.str();

	// SELECT * from url ORDER BY views DESC LIMIT N
	string sql = "SELECT * from url ORDER BY RANDOM() LIMIT " + rank; // Order by  views and THEN votes. The DESC is needed twice.

	const char * select = sql.c_str();

	sqlite3_stmt *stmt; /* A ptr to a statement object*/

	sqlite3_prepare_v2(dbPtr,select,-1,&stmt,0); // prep statement

	int cols = sqlite3_column_count(stmt); // get no. of columns in table
	int retv; // return value from SQL db

	while ( SQLITE_ROW == (retv =  sqlite3_step(stmt))){ // get return values from DB, and compare to SQLITE_ROW - the two will match while they are still rows to be retrieved
		// Print out the rows of data.
		for(int i =0; i < cols-1; i++){ // cols -1 to skip the comments column
			const char *val = (const char*) sqlite3_column_text(stmt,i);
			const char *colname = sqlite3_column_name(stmt,i);

			cout << colname << " : " << val << endl;
		}

		cout << DELIM << endl; // delimeter has 10 equal signs

	}

	if ( retv == SQLITE_ERROR){
		cout << "Some kind of error has occurred" << endl;
		return -1;

	}

	sqlite3_finalize(stmt); // destory statement object to prevent memory leaks.
	return 0;

}


int SQLiteDB::getURLrecent(int n){

	stringstream s;
	s << n;
	string rank = s.str();

	// SELECT * from url ORDER BY views DESC LIMIT N
	string sql = "SELECT * from url ORDER BY id DESC LIMIT " + rank; // Order by  id  descending.

	const char * select = sql.c_str();

	sqlite3_stmt *stmt; /* A ptr to a statement object*/

	sqlite3_prepare_v2(dbPtr,select,-1,&stmt,0); // prep statement

	int cols = sqlite3_column_count(stmt); // get no. of columns in table
	int retv; // return value from SQL db

	while ( SQLITE_ROW == (retv =  sqlite3_step(stmt))){ // get return values from DB, and compare to SQLITE_ROW - the two will match while they are still rows to be retrieved
		// Print out the rows of data.
		for(int i =0; i < cols-1; i++){ // cols -1 to skip the comments column
			const char *val = (const char*) sqlite3_column_text(stmt,i);
			const char *colname = sqlite3_column_name(stmt,i);

			cout << colname << " : " << val << endl;
		}

		cout << DELIM << endl; // delimeter has 10 equal signs

	}

	if ( retv == SQLITE_ERROR){
		cout << "Some kind of error has occurred" << endl;
		return -1;

	}

	sqlite3_finalize(stmt); // destory statement object to prevent memory leaks.
	return 0;

}

int SQLiteDB::getcomment(int id ){

	/// Convert id to a string
	stringstream sstream;
	sstream << id;
	string url_id = sstream.str();

	string sql = "SELECT * FROM url WHERE id=" + url_id; // ID will give us one row of data since it's unique.

	const char * select = sql.c_str();
	sqlite3_stmt *stmt; /* A ptr to a statement object*/

	sqlite3_prepare_v2(dbPtr,select,-1,&stmt,0); // prep statement

	int retv; // return value from SQL db

	retv =  sqlite3_step(stmt); // get one row of data

	/**URL Table Schema
	 * index value - column name
	 * 0 - id
	 * 1 - url
	 * 2 - category
	 * 3 - imagepath
	 * 4 - views
	 * 5 - votes
	 * 6 - comments
	 */
	const char *val = (const char*) sqlite3_column_text(stmt,6); // index of value of 2 gives us 'urlviews'. index value of 1 would give 'snapcount'

	if ( retv == SQLITE_ERROR){
		cout << "-1" << endl;
		cout << "Some kind of error has occurred" << endl;
		return -1;
	}

	cout << val; // print the comment

	sqlite3_finalize(stmt); // destroy statement object to prevent memory leaks.

	return 0; // return the value
}



int SQLiteDB::getViewCount(int id ){

	/// Convert id to a string
	stringstream sstream;
	sstream << id;
	string url_id = sstream.str();

	string sql = "SELECT * FROM url WHERE id=" + url_id; // ID will give us one row of data since it's unique.

	const char * select = sql.c_str();
	sqlite3_stmt *stmt; /* A ptr to a statement object*/

	sqlite3_prepare_v2(dbPtr,select,-1,&stmt,0); // prep statement

	int retv; // return value from SQL db

	retv =  sqlite3_step(stmt);


	/**URL Table Schema
	 * index value - column name
	 * 0 - id
	 * 1 - url
	 * 2 - category
	 * 3 - imagepath
	 * 4 - views
	 * 5 - votes
	 * 6 - comments
	 */
	const char *val = (const char*) sqlite3_column_text(stmt,4); // index of value of 2 gives us 'urlviews'. index value of 1 would give 'snapcount'

	if ( retv == SQLITE_ERROR){
		cout << "-1" << endl;
		cout << "Some kind of error has occurred" << endl;
		return -1;
	}

	// Convert string to integer //
	string value(val); // convert to a c++ string
	stringstream s(value); /// make stringstream from using the "value" string
	int i;
	s >> i; // convert to integer

	sqlite3_finalize(stmt); // destroy statement object to prevent memory leaks.

	return i; // return the value

}

int SQLiteDB::OLD_countURLviews(){  // Old Version - Don't Use.

	string sql = "SELECT * FROM stats WHERE id=1"; // ID is always one since we have data stored in only 1st row

	const char * select = sql.c_str();
	sqlite3_stmt *stmt; /* A ptr to a statement object*/

	sqlite3_prepare_v2(dbPtr,select,-1,&stmt,0); // prep statement

	int retv; // return value from SQL db

	retv =  sqlite3_step(stmt);

	const char *val = (const char*) sqlite3_column_text(stmt,2); // index of value of 2 gives us 'urlviews'. index value of 1 would give 'snapcount'

	if ( retv == SQLITE_ERROR){
		cout << "Some kind of error has occurred" << endl;
		return -1;
	}

	// Convert string to integer //
	string value(val); // convert to a c++ string
	stringstream s(value); /// make stringstream from using the "value" string
	int i;
	s >> i; // convert to integer

	sqlite3_finalize(stmt); // destroy statement object to prevent memory leaks.

	return i; // return the value

}

int SQLiteDB::countRows(string sql){ // counts number of records  in given table as specified in the sql query

	const char * select = sql.c_str();
	sqlite3_stmt *stmt; /* A ptr to a statement object*/

	sqlite3_prepare_v2(dbPtr,select,-1,&stmt,0); // prep statement

	int retv; // return value from SQL db

	/**
	 * We are doing a basic count of the rows in visitors table
	 * SQL returns this as the first row of the first column in a 1x1 table, so use index value of 0
	 */
	retv =  sqlite3_step(stmt);
	const char *val = (const char*) sqlite3_column_text(stmt,0);  // the count value


	if ( retv == SQLITE_ERROR){
		cout << "Some kind of error has occurred" << endl;
		return -1;
	}

	// Convert string to integer //
	string value(val); // convert to a c++ string
	stringstream s(value); /// make stringstream from using the "value" string
	int i;
	s >> i; // convert to integer

	sqlite3_finalize(stmt); // destroy statement object to prevent memory leaks.

	return i; // return the value
}

int SQLiteDB::countIP(){ // returns number of unique IP visitors

	string sql = "SELECT COUNT(*) FROM visitors";
	const char * select = sql.c_str();
	sqlite3_stmt *stmt; /* A ptr to a statement object*/

	sqlite3_prepare_v2(dbPtr,select,-1,&stmt,0); // prep statement

	int retv; // return value from SQL db


	/**
	 * We are doing a basic count of the rows in visitors table
	 * SQL returns this as the first row of the first column in a 1x1 table, so use index value of 0
	 */
	retv =  sqlite3_step(stmt);
	const char *val = (const char*) sqlite3_column_text(stmt,0);  // the count value

	if ( retv == SQLITE_ERROR){
		cout << "Some kind of error has occurred" << endl;
		return -1;
	}

	// Convert string to integer //
	string value(val); // convert to a c++ string
	stringstream s(value); /// make stringstream from using the "value" string
	int i;
	s >> i; // convert to integer

	sqlite3_finalize(stmt); // destroy statement object to prevent memory leaks.

	return i; // return the value

}

int SQLiteDB::incrSnaps(){

	string url_id = "1"; // ID is always constant at 1 because, we only have 1 row in stats table.

	string sql = "UPDATE stats SET snapcount = snapcount+1 WHERE id=" + url_id ;

	int retv =  update(sql);
	if (retv != 0) {
		return -1; // some error occured.
	} else {
		return 0; // no errors
	}

}

int SQLiteDB::increaseViewCount(int id){

	/// Convert id to a string
	stringstream sstream;
	sstream << id;
	string url_id = sstream.str();


	string sql = "UPDATE url SET views = views+1 WHERE id=" + url_id ;

	int retv =  update(sql);
	if (retv != 0) {
		return -1; // some error occured.
	} else {
		return 0; // no errors
	}


}

int SQLiteDB::OLD_incrURLviews(){

	string url_id = "1"; // ID is always constant at 1 because, we only have 1 row in stats table.

	string sql = "UPDATE stats SET urlviews = urlviews+1 WHERE id=" + url_id ;

	int retv =  update(sql);
	if (retv != 0) {
		return -1; // some error occured.
	} else {
		return 0; // no errors
	}
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

		cout <<  DELIM << endl; // record delimeter

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

		cout <<  DELIM << endl; // record delimeter

	}

	if ( retv == SQLITE_ERROR){
		cout << "Some kind of error has occurred" << endl;
		return -1;

	}

	sqlite3_finalize(stmt); // destory statement object to prevent memory leaks.
	return 0;
}



