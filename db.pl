#!/usr/bin/perl

# Perl DB Test scipt
# Contains methods to handle & manipulate SQL DB
# Written by Jervis Muindi
# April  19, 2011

use strict;
use DBI;


print "inserting into db ...\n";
#createdb2();
#initdb();
#mkdir "./files/$u";
	
	
	my $dbfile = "test.db"; 

	my $dbh = DBI->connect( "dbi:SQLite:$dbfile", "", "",
	{RaiseError => 1, AutoCommit => 1}) || die "connect to DB", "$dbfile - $DBI::errstr";
	
	
	my ($url, $category, $imagepath, $views, $votes);
	
	$url = "http://www.msn.com";
	$category = "Search_Engine";
	$imagepath = "/home/jjm2190/project2/msn.png";
	$views = "300";
	$votes = "10";
	 
# INSERT INTO userpass (filepath, filename, public, permissions, timemodified, timeadded, size, kind, comments, tags) VALUES (:1, :2, :3, :4, :5, :6, :7, :8, :9, :10)
	my $insert = "INSERT OR REPLACE INTO url (url, category, imagepath, views, votes) VALUES (:1, :2, :3, :4, :5)";
	my $sth = $dbh->prepare("$insert");
	$sth->execute($url, $category, $imagepath, $views, $votes);

sub createdb2{ # make a stat db, and create the 0th id. 
	`sqlite3 test2.db "CREATE TABLE visitors ( id INTEGER PRIMARY KEY,
                        ip TEXT NOT NULL COLLATE NOCASE,
                        UNIQUE (ip) );"`;

`sqlite3 test2.db "CREATE TABLE stats ( id INTEGER PRIMARY KEY,
                        snapcount INTEGER NOT NULL COLLATE NOCASE,
                        urlviews INTEGER NOT NULL COLLATE NOCASE);"`;
	
exit;  
}


sub initdb{ # initialize the stats db. 
	
# insert the 0th id. 
my $dbfile = "test2.db"; 
my $dbh = DBI->connect( "dbi:SQLite:$dbfile", "", "",
	{RaiseError => 1, AutoCommit => 1}) || die "connect to DB", "$dbfile - $DBI::errstr";

my $insert = "INSERT OR REPLACE INTO stats (snapcount, urlviews) VALUES (:1, :2)";
	my $sth = $dbh->prepare("$insert");
	$sth->execute(0,0);
	exit; 	
}

	
sub createdb{
	my $dbname = "test2.db";
	`sqlite3 $dbname "CREATE TABLE url ( id INTEGER PRIMARY KEY,
                        url TEXT NOT NULL COLLATE NOCASE,
                        category TEXT NOT NULL COLLATE NOCASE,
                        imagepath TEXT NOT NULL COLLATE NOCASE,
                        views INTEGER NOT NULL,
                        votes INTEGER NOT NULL,
                        comments TEXT NOT NULL COLLATE NOCASE,
                        UNIQUE (url) );"`;
                        
     `sqlite3 $dbname "CREATE TABLE visitors ( id INTEGER PRIMARY KEY,
                        ip TEXT NOT NULL COLLATE NOCASE,
                        UNIQUE (ip) );"`;

`sqlite3 $dbname "CREATE TABLE stats ( id INTEGER PRIMARY KEY,
                        snapcount INTEGER NOT NULL COLLATE NOCASE,
                        urlviews INTEGER NOT NULL COLLATE NOCASE);"`;
exit;     
}	
             