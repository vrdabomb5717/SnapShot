/*
 * Add Comment
 * This adds a Comment to a specified URL in the SQL database.
 *
 *  Created on: Apr 25, 2011
 *      Author: Jervis
 */


#include <iostream>
#include <sqlite3.h>
#include<stdlib.h>
#include <sstream>
#include "SQLiteDB.h"
#include <fstream> // for reading config file

#define comment_delimeter ""

using namespace std;

int main(int argc, char* args[]) {

	if (argc != 4 ){ // Need 3 Arguments  in this form : [url id, string comment, string commenter]
		cout << "-1" <<endl;
		cout << "Insufficient arguments supplied" << endl;
		cout << "Usage is addcomment url_id, comment_to_add, commenter_user_name " << endl;
		return (-1);
	}

	int url_id; // url id to add comment to.
	string id_string(args[1]); // get the url-id and store in id_string
	stringstream inputStream(id_string);

	string comment(args[2]);
	string commenter(args[3]); // screename of the commenter.

	if(inputStream >> url_id){ // if we can convert the input string of url-id to an integer

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

		int retv = db.addcomment(url_id,comment);  // add the comment

		if (retv != 0) {
			cout << "-1" << endl;
			cout << "Some error occured while trying to add the comment" << endl;
			return -1; // some error occured.
		} else {
			return 0; // no errors
		}


	} else { // Convert url-idto an integer failed, print out error msg
		cout << "-1" <<endl;
		cout << "Invalid url id. Please enter a valid integer only" <<endl;
		return (-1);
	}
}
