#!/usr/bin/perl

# Adds to URL info the SQLite DB. 
# By using the C++ addurl program. 
# 
# Written by Jervis Muindi
# 5th April  2011

##### Still to DO : #############



use strict;
use IO::Socket::INET; # import network socket
use Digest::SHA qw(sha1 sha1_hex sha1_base64); # import SHA 1 hash
use Cwd; 

$| = 1; # auto flush buffers

my $SQL_PATH = "sql"; # path to where sql query c++ program are stored. Usually it's under /sql folder

if(int(@ARGV) != 3){ # do simple argument validation
	die "Please enter only 3 arguments in this form: category, vote, url."; 
}


## input is of form : category,vote,URL
my $cat = $ARGV[0];
my $vote = $ARGV[1]; 
my $url = $ARGV[2];  

# calculate path of image caputed
my $dir = getcwd; # get current working directory
my $imgname = sha1_hex(lc($url)) . ".png";
my $imgpath = "$dir/snaps/$imgname"; 


# addurl C++ takes args: url, category, img path, votes

chdir $SQL_PATH; # change into dir with sql utilities. It's necessary for them to work properly (find testdb.txt file). 
my $cmd = "./addurl $url $cat $imgpath $vote"; # command to execute to add URL

## add / update to DB Only if Test for File existence works. 

if ( -e $imgpath){ # check that image file was successfully created. 
	my $rc = system($cmd); # run command. 
} else{
	print "File Does not Exist. Please make sure that image file was successfully created"; 
	exit(-1);
}

exit(0);
