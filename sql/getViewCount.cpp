/*
 * getViewCount.cpp
 * Return the number of views count for given URL ID
 * stored in the database file.
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

	if (argc != 2 ){ // Need 1 Arguments  in this form : [string URL_ID]
		cout << "-1" <<endl;
		cout << "Insufficient arguments supplied" << endl;
		cout << "Usage is getViewCount URL_ID" << endl;
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

		int count = db.getViewCount(url_id); // get count. returns -1 if an error occured


		if(count == -1){
			cout << "-1" << endl;
			cout << "Some error has occured in accessing the URL with given ID="+ id << ". Please make sure that this is a valid URL-ID and try again." ;
		} else {
			stringstream s;
			s << count;
			string countS = s.str();
			// cout << "0" << endl; // Just print the count.
			cout << "countS" << endl;
		}

	} else { // Convert url id part of input string to an integer failed, print out error msg
		cout << "-1" <<endl;
		cout << "Invalid url-id argument entered. Please enter a valid integer only" <<endl;
		return (-1);
	}
}
