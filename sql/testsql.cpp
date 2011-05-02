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

#include <fstream> // for reading files

using namespace std;

/*Function declaration*/
int voteup();
void testsql();
void addurl();
void viewall();
void addcomment();
void addIP();
void countIP();
void incrementSnap();
void incrementURL();
void countURLviews();
void countSnaps();

int main(int argc, char** args) {

	//countSnaps();
	//countURLviews();

	//incrementSnap();
	//incrementURL();

	//countIP();
	//addIP();
	//addcomment();
	//viewall();


}


void incrementSnap(){ // increment snap count

	string dbfile("/mnt/hgfs/EclipseC_workspace/snapshot/test2.db");
	cout<< "Opening DB File ... \n";
	SQLiteDB db(dbfile);

	cout<< "Incrementing URL Snap count in DB\n";

	db.incrSnaps();

}


void incrementURL(){ // increment url views

	string dbfile("/mnt/hgfs/EclipseC_workspace/snapshot/test2.db");
	cout<< "Opening DB File ... \n";
	SQLiteDB db(dbfile);

	cout<< "Incrementing URL view count in DB\n";

	db.incrURLviews();

}

void countSnaps(){

	string dbfile("/mnt/hgfs/EclipseC_workspace/snapshot/test2.db");
	cout<< "Opening DB File ... \n";
	SQLiteDB db(dbfile);

	cout<< "Geting Count of URL Snaps taken from DB\n";

	int count = db.countSnaps();
	cout << "Total URL Snaps  = " << count <<endl;
}

void countURLviews(){ // count total number of url viewed - can think of as being number of pages viewed / served.

	string dbfile("/mnt/hgfs/EclipseC_workspace/snapshot/test2.db");
	cout<< "Opening DB File ... \n";
	SQLiteDB db(dbfile);

	cout<< "Geting Count of URL views from DB\n";

	int count = db.countURLviews();
	cout << "Total URL views  = " << count <<endl;



}

void countIP(){
	string dbfile("/mnt/hgfs/EclipseC_workspace/snapshot/test2.db");
	cout<< "Opening DB File ... \n";
	SQLiteDB db(dbfile);

	cout<< "Geting IP Count from DB\n";

	int count = db.countIP();

	cout << "The count is " << count << endl;


}


void addIP(){

	string dbfile("/mnt/hgfs/EclipseC_workspace/snapshot/test2.db");
	cout<< "Opening DB File ... \n";
	SQLiteDB db(dbfile);

	cout<< "Adding IP to statistic tablein DB \n";

	string ip = "12.12.12.12";
	db.addIP(ip);

}
void addcomment(){

	string dbfile("/mnt/hgfs/EclipseC_workspace/snapshot/test2.db");
	cout<< "Opening DB File ... \n";
	SQLiteDB db(dbfile);

	cout<< "Adding Comment to URL in DB \n";

	string com = " This is just a test comment \n";
	com+= "This a 2nd line of a comment \n";
	com+="3rd line of comment";


	db.addcomment(1,com);
}

void addurl() {

	string dbfile("/mnt/hgfs/EclipseC_workspace/snapshot/test2.db");
	cout<< "Opening DB File ... \n";
	SQLiteDB db(dbfile);

	cout<< "Adding URL to DB \n";

	string url = "www.hahahaha.com";
	string cat = "no-category";
	string imgpath = "my-fake-path";
	int vote = 1;

	db.addurl(url,cat,imgpath,vote);


}

void viewall(){

	string dbfile("/mnt/hgfs/EclipseC_workspace/snapshot/test2.db");
	cout<< "Opening DB File ... \n";
	SQLiteDB db(dbfile);

	cout<< "Printing out ALL DB Records \n";
	string qry("SELECT * from url");
	//db.insert("INSERT INTO url VALUES(NULL, 'www.grc.com', 'test', 'image-test-path', '222', '111')");
	//db.update("UPDATE url SET url='www.fake3url.com' WHERE id='7'");
	//db.votedown(2);
	db.view(qry);
}


int voteup(){
	return 0;
}

void readfile() {

	// Open file for reading only.
	string f("/mnt/hgfs/EclipseC_workspace/ubuntu-testsql/src/testdb.txt");
	const char * fs = f.c_str();

	ifstream file(fs, ifstream::in);
	ifstream file2(fs,  ifstream::in);
	ifstream file3(fs, ifstream::in);

	string url = "";
	string url2 = "";
	string url3 = "";

	cout << "URL 1 before reading is " << url << endl;
	getline(file, url);
	cout << "URL 1 after reading is " << url << endl;

	cout << "URL 2 before reading is " << url2 << endl;
	getline(file2, url2);
	cout << "URL 2 after reading is " << url2 << endl;

	cout << "URL 3 before reading is " << url3 << endl;
	getline(file3, url3);
	cout << "URL 3 after reading is " << url3 << endl;

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

		sqlite3_open("/mnt/hgfs/EclipseC_workspace/snapshot/test2.db", &hndPtr);

		char insert[256]  = "INSERT INTO url VALUES(NULL, 'www.yahoo.com', 'test0', 'image-test-path0', '2', '1', '')"; // Add the NULL so that the URL ID is auto-chosen for us.
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
