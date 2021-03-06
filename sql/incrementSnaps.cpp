/*
 * incrementSnaps.cpp
 * Increment Number of URL Snapshots taken
 * that is stored in the SQLite database
 *  Created on: May 2, 2011
 *      Author: jervis
 */


#include <iostream>
#include <sqlite3.h>
#include <stdlib.h>
#include <sstream>
#include <fstream> // for reading config file>
#include "SQLiteDB.h"

using namespace std;

int main(int argc, char* args[]) { // We don't take any commandline arguments

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

	int retv = db.incrSnaps();

	if(retv != 0){
		cout << "-1" << endl;
		cout << "Some error has occured";
	} else {
		cout << "0";
	}
}
