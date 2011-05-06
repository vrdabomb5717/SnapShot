# Makefile for Snapshot
# Written by Jervis Muindi
# May 3rd, 2011
# Note: $@ is the name of the make target

# Make All
# Just compiles all the steps.
all:
	make addcomment
	make addIP
	make addurl
	make countIP
	make getBottomURL
	make getBottomURLByVote
	make getRandURL
	make getTopURL
	make getTopURLByVote
	make getURLByCat
	make getURLid
	make getURLinfo
	make getViewCount
	make increaseViewCount
	make incrementSnaps
	make votedown
	make voteup
	make getcomment
	make getURLrecent
	rm -rf *.dSYM


addcomment : addcomment.cpp SQLiteDB.cpp
	g++ $@.cpp SQLiteDB.cpp -g -o $@ -lsqlite3	

addIP : addIP.cpp SQLiteDB.cpp
	g++ $@.cpp SQLiteDB.cpp -g -o $@ -lsqlite3	
	
addurl : addurl.cpp SQLiteDB.cpp
	g++ $@.cpp SQLiteDB.cpp -g -o $@ -lsqlite3	

countIP : countIP.cpp SQLiteDB.cpp
	g++ $@.cpp SQLiteDB.cpp -g -o $@ -lsqlite3	

getBottomURL : getBottomURL.cpp SQLiteDB.cpp
	g++ $@.cpp SQLiteDB.cpp -g -o $@ -lsqlite3	


getBottomURLByVote : getBottomURLByVote.cpp SQLiteDB.cpp
	g++ $@.cpp SQLiteDB.cpp -g -o $@ -lsqlite3	


getRandURL : getRandURL.cpp SQLiteDB.cpp
	g++ $@.cpp SQLiteDB.cpp -g -o $@ -lsqlite3	


getTopURL : getTopURL.cpp SQLiteDB.cpp
	g++ $@.cpp SQLiteDB.cpp -g -o $@ -lsqlite3	


getTopURLByVote : getTopURLByVote.cpp SQLiteDB.cpp
	g++ $@.cpp SQLiteDB.cpp -g -o $@ -lsqlite3	


getURLByCat : getURLByCat.cpp SQLiteDB.cpp
	g++ $@.cpp SQLiteDB.cpp -g -o $@ -lsqlite3	


getURLid : getURLid.cpp SQLiteDB.cpp
	g++ $@.cpp SQLiteDB.cpp -g -o $@ -lsqlite3	


getURLinfo : getURLinfo.cpp SQLiteDB.cpp
	g++ $@.cpp SQLiteDB.cpp -g -o $@ -lsqlite3	


getViewCount : getViewCount.cpp SQLiteDB.cpp
	g++ $@.cpp SQLiteDB.cpp -g -o $@ -lsqlite3	


increaseViewCount : increaseViewCount.cpp SQLiteDB.cpp
	g++ $@.cpp SQLiteDB.cpp -g -o $@ -lsqlite3	


incrementSnaps : incrementSnaps.cpp SQLiteDB.cpp
	g++ $@.cpp SQLiteDB.cpp -g -o $@ -lsqlite3	


testsql : testsql.cpp SQLiteDB.cpp
	g++ $@.cpp SQLiteDB.cpp -g -o $@ -lsqlite3	


votedown : votedown.cpp SQLiteDB.cpp
	g++ $@.cpp SQLiteDB.cpp -g -o $@ -lsqlite3	


voteup : voteup.cpp SQLiteDB.cpp
	g++ $@.cpp SQLiteDB.cpp -g -o $@ -lsqlite3	

getcomment : getcomment.cpp SQLiteDB.cpp
	g++ $@.cpp SQLiteDB.cpp -g -o $@ -lsqlite3

getURLrecent : getURLrecent.cpp SQLiteDB.cpp
	g++ $@.cpp SQLiteDB.cpp -g -o $@ -lsqlite3

# Delete all object files
clean :
	rm -rf *.o *.dSYM addcomment addIP addurl countIP getBottomURL getBottomURLByVote getRandURL getTopURL getTopURLByVote getURLByCat getURLid getURLinfo getViewCount increaseViewCount incrementSnaps getcomment votedown voteup getURLrecent