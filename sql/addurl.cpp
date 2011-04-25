/*
 * Add URL
 * This adds a URL to the SQL database.
 *
 *  Created on: Apr 25, 2011
 *      Author: Jervis
 */


#include <iostream>
#include <sqlite3.h>
#include<stdlib.h>
#include <sstream>
#include "SQLiteDB.h"

using namespace std;

int main(int argc, char* args[]) {

	if (argc != 5 ){ // Need 4 Arguments  in this form : [string url, string category, string imagepath, int votes];
		cout << "-1" <<endl;
		cout << "Insufficient arguments supplied" << endl;
		cout << "Usage is addurl url, category, imagepath, votecount" << endl;
		return (-1);
	}

	int votes;
	string input(args[4]); // get the vote value
	stringstream inputStream(input);

	string url(args[1]);
	string category(args[2]);
	string imgpath(args[3]);


	if(input << votes){ // if we can convert the vote to an integer

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

		int retv = db.addurl(url,category,imgpath,votes); // arguments are of form : [string url, string category, string imagepath, int votes];

		if(retv != 0){
			cout << "-1" << endl;
			cout << "Some error has occured";
		} else {
			cout << "0";
		}

	} else { // Convert vote part of input string to an integer failed, print out error msg
		cout << "-1" <<endl;
		cout << "Invalid vote argument entered. Please enter a valid integer only" <<endl;
		return (-1);
	}
}
