/*
 * Vote Down
 * This votes Down the given URL-id
 *
 *  Created on: Apr 25, 2011
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

	if (argc != 2 ){ // Need one Argument
		cout << "-1" <<endl;
		cout << "Insufficient arguments supplied" << endl;
		cout << "Usage is votedown [url-id]" << endl;
		return (-1);
	}

	int url_id;
	string input(args[1]); // get the url id number
	stringstream inputStream(input);

	if(inputStream >> url_id){ // if we can convert input to a url id (integer)

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

		int retv = db.votedown(url_id);

		if(retv != 0){
			cout << "-1" << endl;
			cout << "Some error has occured";
		} else {
			cout << "0";
		}

	} else { // Convert input string to a integer failed, print out error msg
		cout << "-1" <<endl;
		cout << "Invalid argument entered. Please enter a valid integer only" <<endl;
		return (-1);
	}
}
