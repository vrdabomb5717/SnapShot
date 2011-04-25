#!/usr/bin/perl

# Perl DB Test scipt
# Contains methods to handle & manipulate SQL DB
# Written by Jervis Muindi
# April  19, 2011

use strict;
use DBI;


print "inserting into db ...\n";
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


	
sub createdb{
	`sqlite3 test2.db "CREATE TABLE url ( id INTEGER PRIMARY KEY,
                        url TEXT NOT NULL COLLATE NOCASE,
                        category TEXT NOT NULL,
                        imagepath TEXT NOT NULL COLLATE NOCASE,
                        views INTEGER NOT NULL,
                        votes INTEGER NOT NULL,
                        comments TEXT NOT NULL COLLATE NOCASE,
                        UNIQUE (url) );"`;
exit;     
}	
             