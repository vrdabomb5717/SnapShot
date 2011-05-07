/*
 * countSnaps.cpp
 * Returns the number of URL snaps taken.
 *  Created on: May 6, 2011
 *      Author: jervis
 */

#include <iostream>
#include <sqlite3.h>
#include<stdlib.h>
#include <sstream>
#include "SQLiteDB.h"
#include <fstream> // for reading config file


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

	int count = db.countSnaps();
	cout << count << endl;

}
