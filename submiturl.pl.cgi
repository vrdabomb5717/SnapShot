#!/usr/bin/perl

use strict;
use warnings;
use CGI qw/:all/;


my (@pairs, $key, $value, $inputstring);

my $q = CGI->new(); # cgi object
print $q->header();

my $url = $q->param('url'); #url
my $category = $q->param('category'); #category
my $comments = $q->param('comments'); #comments
my $ip = $ENV{'REMOTE_ADDR'};

# insert into DB here

sub site_error
{
	#page displayed if website is malformed

		print <<END_OF_PRINTING;
		<html><head>
		<meta http-equiv="refresh" content="3; URL=submit.html">
		<title>URL Malformed!</title></head>
		<body>
		<br>Sorry, the website address you provided was malformed. Go back and try again!<br>
		<br> Redirecting in 3 seconds...<br>
		</body
		</html>
	
END_OF_PRINTING
}
