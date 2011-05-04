/*
 * getURLid.cpp
 * Returns URL id of given url string.
 *
 * Note that the first line is not an error code specifier (i.e. 1 or 0).
 * I just return the data from the DB. However, if an error occurs in processing
 * request, I warn you at that time (in the end).

 *  Created on: May 3, 2011
 *      Author: Jervis Muindi
 */


#include <iostream>
#include <sqlite3.h>
#include<stdlib.h>
#include <sstream>
#include "SQLiteDB.h"
#include <fstream> // for reading config file

using namespace std;

int main(int argc, char* args[]) {

	if (argc != 2 ){ // Need 1 Arguments  in this form : [string url]
		cout << "-1" <<endl;
		cout << "Insufficient arguments supplied" << endl;
		cout << "Usage is getURLid A_URL" << endl;
		return (-1);
	}

	string url(args[1]); // get the given category

	string cf("testdb.txt"); // string with location of db configuration file
	ifstream file(cf.c_str(), ifstream::in); // open file for reading only


	if (!file.is_open()) {
		cout << "-1" << endl;
		cout << "Error - Could not open database configuration file " << cf << ". Please make sure that this file is in the same directory as the program" << endl;
		return -1; // QUIT
	}


	string dbfile = "";

	getline(file, dbfile); // read database file location from file and store in variable "dbfile"
	file.close();  // close file stream
	SQLiteDB db(dbfile); /// open sql database

	int retv = db.getURLid(url);  // print url string.

	if (retv == -1) {
		cout << "Some kind of error occured while processing the SQL query" << endl;
		return -1;
	}

	return 0;
}
