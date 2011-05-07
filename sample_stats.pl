#!/usr/bin/perl

# A Basic Sample Statistics Page for SnapShot
# Written by Jervis Muindi
# May 6th , 2011

use strict;
use Digest::MD5 qw(md5 md5_hex md5_base64);



## Get Statistics info :

my $SQL_PATH = "sql"; 

chdir $SQL_PATH ;  # change to directory with SQL 

my $ips = `./countIP` ;  # run get Uniq IP SQL Query
my $url_count = `./countSnaps`; # get URL total snaps count

## Print the HTML 
print "Content-type: text/html\n\n"; # declaration for cgi script
	print <<EOF;
	<html>
	<head>
	<title> Statistics Page </title>
	</head>
	<body > 
    <h1> Statistics Page </h1>
    <h2> Site Statistics </h2>
    <h3> Number of Unique Visitors : $ips </h3>
    <h3> Number of URLs Snapped    : $url_count </h3> 
    </body
    </html> 
EOF