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

#define DELIM "=========="

using namespace std;

/*Function declaration*/
void OLD_incrementURL();
void OLD_countURLviews();

int voteup();
void testsql();
void addurl();
void viewall();
void addcomment();
void addIP();
void countIP();
void incrementSnap();
void countSnaps();
void getViewCount();
void increaseViewCount();
void getURLByCat();
void getTopURL();
void getTopURLByVote();
void getBottomURL();
void getBottomURLByVote();
void getcomment();
void getRandURL();
void getURLinfo(int n);
void getURLid(string s);



int main(int argc, char** args) {


	//getURLinfo(2);
	getURLid("www.google.com");
	//getTopURLByVote();
	//getBottomURLByVote();


	//getRandURL();

	//getcomment();

	//getBottomURL();
	//getTopURL();

	//getURLByCat();

	//increaseViewCount();
	//getViewCount();

	//countSnaps();
	//countURLviews();

	//incrementSnap();
	//incrementURL();

	//countIP();
	//addIP();
	//addcomment();
	//viewall();


}

void getURLinfo(int n) {


	string dbfile("/mnt/hgfs/EclipseC_workspace/snapshot/test2.db");
	cout<< "Opening DB File ... \n";
	SQLiteDB db(dbfile);
	cout<< "Getting URL info for Specified URL \n";


	db.getURLinfo(n);
}

void getURLid(string url ) {


	string dbfile("/mnt/hgfs/EclipseC_workspace/snapshot/test2.db");
	cout<< "Opening DB File ... \n";
	SQLiteDB db(dbfile);
	cout<< "Getting URL id  for Specified URL \n";

	db.getURLid(url);
}

void getTopURLByVote(){

	string dbfile("/mnt/hgfs/EclipseC_workspace/snapshot/test2.db");
	cout<< "Opening DB File ... \n";
	SQLiteDB db(dbfile);

	cout<< "Getting URLs info on TOP X URls that are in DB orderd BY VOTES\n";
	int top = 4;
	db.getTopURLByVote(4);
}


void getBottomURLByVote(){

	string dbfile("/mnt/hgfs/EclipseC_workspace/snapshot/test2.db");
	cout<< "Opening DB File ... \n";
	SQLiteDB db(dbfile);
	cout<< "Getting URLs info on Bottom  X URls that are in DB orded by VOTES\n";
	int top = 4;
	db.getBottomURLByVote(4);

}




void getcomment(){


	string dbfile("/mnt/hgfs/EclipseC_workspace/snapshot/test2.db");
	cout<< "Opening DB File ... \n";
	SQLiteDB db(dbfile);
	cout<< "Getting Comment for Specified URL \n";
	int n = 1;
	db.getcomment(n);


}

void getRandURL(){
	string dbfile("/mnt/hgfs/EclipseC_workspace/snapshot/test2.db");
	cout<< "Opening DB File ... \n";
	SQLiteDB db(dbfile);
	cout<< "Getting Specified Number of Random URLs info \n";
	int n = 2;
	db.getRandURL (n);
	}

void getBottomURL(){

	string dbfile("/mnt/hgfs/EclipseC_workspace/snapshot/test2.db");
	cout<< "Opening DB File ... \n";
	SQLiteDB db(dbfile);
	cout<< "Getting URLs info on Bottom  X URls that are in DB\n";
	int top = 4;
	db.getBottomURL(4);

}


void getTopURL(){

	string dbfile("/mnt/hgfs/EclipseC_workspace/snapshot/test2.db");
	cout<< "Opening DB File ... \n";
	SQLiteDB db(dbfile);

	cout<< "Getting URLs info on TOP X URls that are in DB\n";
	int top = 4;
	db.getTopURL(4);
}

void getURLByCat(){

	string dbfile("/mnt/hgfs/EclipseC_workspace/snapshot/test2.db");
	cout<< "Opening DB File ... \n";
	SQLiteDB db(dbfile);

	cout<< "Getting URLs info with given categor that are in DB\n";
	string cat("test");
	db.getURLByCat(cat);

}

void increaseViewCount(){

	string dbfile("/mnt/hgfs/EclipseC_workspace/snapshot/test2.db");
	cout<< "Opening DB File ... \n";
	SQLiteDB db(dbfile);

	cout<< "Incrementing URL View count for URL ID Specified in DB\n";
	int id = 4;
	db.increaseViewCount(4);

}

void incrementSnap(){ // increment snap count

	string dbfile("/mnt/hgfs/EclipseC_workspace/snapshot/test2.db");
	cout<< "Opening DB File ... \n";
	SQLiteDB db(dbfile);

	cout<< "Incrementing URL Snap count in DB\n";

	db.incrSnaps();

}

void getViewCount(){ // test for OLD method - don't use


	int id = 4;
	string dbfile("/mnt/hgfs/EclipseC_workspace/snapshot/test2.db");
	cout<< "Opening DB File ... \n";
	SQLiteDB db(dbfile);

	cout<< "Getting View Count for URL ID in DB\n";

	int count = db.getViewCount(id);
	cout << "View count is " << count << endl;

}

void OLD_incrementURL(){ // test for OLD method ... increment url views

	string dbfile("/mnt/hgfs/EclipseC_workspace/snapshot/test2.db");
	cout<< "Opening DB File ... \n";
	SQLiteDB db(dbfile);

	cout<< "Incrementing URL view count in DB\n";

	db.OLD_incrURLviews();

}

void countSnaps(){

	string dbfile("/mnt/hgfs/EclipseC_workspace/snapshot/test2.db");
	cout<< "Opening DB File ... \n";
	SQLiteDB db(dbfile);

	cout<< "Geting Count of URL Snaps taken from DB\n";

	int count = db.countSnaps();
	cout << "Total URL Snaps  = " << count <<endl;
}

void OLD_countURLviews(){ // test for OLD Method - count total number of url viewed - can think of as being number of pages viewed / served.

	string dbfile("/mnt/hgfs/EclipseC_workspace/snapshot/test2.db");
	cout<< "Opening DB File ... \n";
	SQLiteDB db(dbfile);

	cout<< "Geting Count of URL views from DB\n";

	int count = db.OLD_countURLviews();
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
