/*
 * addIP.cpp
 * Adds given IP to visitors table in database
 * Note: Only if an IP doesn't not exist, is it actually
 * added to the database.
 *
 *  Created on: May 1, 2011
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

	if (argc != 2 ){ // Need 1 Arguments  in this form : [string ip]
		cout << "-1" <<endl;
		cout << "Insufficient arguments supplied" << endl;
		cout << "Usage is addIP IP_Address " << endl;
		return (-1);

	}

	string ip(args[1]); // get the ip address entered.

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

	int retv = db.addIP(ip);

	if(retv != 0){
		cout << "-1" << endl;
		cout << "Some error has occured";
	} else {
		cout << "0";
	}
}
