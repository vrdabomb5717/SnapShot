/*
 * increaseViewCount.cpp
 * Increments the view count for the URL with specified URL-ID
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

	if (argc != 2 ){ // Need 1 Arguments  in this form : [string URL_ID]
		cout << "-1" <<endl;
		cout << "Insufficient arguments supplied" << endl;
		cout << "Usage is increaseViewCount URL_ID" << endl;
		return (-1);
	}

	string id(args[1]); // get the URL ID given
	stringstream inputStream(id);
	int url_id; // store url id.

	if(inputStream >> url_id){ // if we can convert the url id to an integer and store in url_id

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

		int retv = db.increaseViewCount(url_id);

		if(retv != 0){
			cout << "-1" << endl;
			cout << "Some error has occured - the incement operation did not successfully complete";
		} else {
			cout << "0" << endl;
		}

	} else { // Convert url id part of input string to an integer failed, print out error msg
		cout << "-1" <<endl;
		cout << "Invalid url-id argument entered. Please enter a valid integer only" <<endl;
		return (-1);
	}
}
