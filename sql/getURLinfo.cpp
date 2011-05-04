/*
 * getURLinfo.cpp
 * Return detailed information on URL with specified ID
 * Note that comments are not returned.
 *
 *
 *  Created on: May 3, 2011
 *      Author: jervis
 */

#include <iostream>
#include <sqlite3.h>
#include<stdlib.h>
#include <sstream>
#include "SQLiteDB.h"
#include <fstream> // for reading config file

using namespace std;

int main(int argc, char* args[]) {

	if (argc != 2 ){ // Need 1 Arguments  in this form : [string id]
		cout << "-1" <<endl;
		cout << "Insufficient arguments supplied" << endl;
		cout << "Usage is getURLinfo url_id" << endl;
		return (-1);
	}

	string id_string(args[1]); // get the id string.

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

	stringstream s(id_string);
	int url_id; // top Number of URL to be returned
	int retv; // return value
	if( s >> url_id) {

		retv  = db.getURLinfo(url_id);  // print URL info .

	}
	else {
		cout << "Invalid arguments supplied. Please enter a valid integer" << endl;
		return -1; // QUIT
	}

	if (retv == -1) {
		cout << "Some kind of error occured while processing the SQL query" << endl;
		return -1;
	}

	return 0;
}
