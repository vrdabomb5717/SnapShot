//============================================================================
// Name        : testsql.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <sqlite3.h>
#include<stdlib.h>
#include "SQLiteDB.h"

using namespace std;

int main(int argc, char** args) {

	string dbfile("/mnt/hgfs/EclipseC_workspace/snapshot/test.db");
	cout<< "Opening DB File ... \n";
	SQLiteDB db(dbfile);

	cout<< "Printing out ALL DB Records \n";
	string qry("SELECT * from url");
	db.view(qry);

}

void testsql(){

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
		cout <<"Trying to open databse \n";

		if(0){
			cout <<"C++ treats !0 as being true\n";
		}
		if(NULL){
			cout << "C++ treats !NULL as being true\n";
		}

		sqlite3 * hndPtr;
		sqlite3_stmt *stmt;

		sqlite3_open("/mnt/hgfs/EclipseC_workspace/snapshot/test.db", &hndPtr);

		char insert[256]  = "INSERT INTO url VALUES(NULL, 'www.aol.com', 'test', 'image-test-path', '222', '111')"; // Add the NULL so that the URL ID is auto-chosen for us.
		char select[256] = "SELECT * from url";


		char * error = (char*) malloc (sizeof(char) * 1024);

		cout << "Inserting data into SQL Database \n";
		sqlite3_exec(hndPtr, insert, 0,0,&error); // insert into sql table
		sqlite3_prepare_v2(hndPtr,select,-1,&stmt,0 );

		if(error != SQLITE_OK){
			cout << "Error Msg: "<<error <<endl;
		}


		int cols = sqlite3_column_count(stmt); // get no. of columns in table
		int retv; // return value from SQL db

		while ( SQLITE_ROW == (retv =  sqlite3_step(stmt))){ // while they are rows in stmt still
			// Print out the row of data.
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



		//sqlite3_stmt = sqlite3_prepare_v2(&db, insert, 255) ;


}
