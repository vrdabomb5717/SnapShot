#!/usr/bin/perl

use strict;
use warnings;
use CGI qw/:all/;

my $q = CGI->new(); # cgi object
print $q->header();

my $comment = $q->param('comment'); #comment 
my $id = $q->url_param('id'); #id 

my $SQL_PATH = "sql"; 
chdir $SQL_PATH;  # change to directory with SQL

my $ip = $ENV{'REMOTE_ADDR'};
`./addIP $ip`;


my $urlinfo = `./getURLinfo $id`;
my @list = split("==========", $urlinfo);
my $line = $list[1];
$line =~ s/://g;
&site_error($comment, $id) if $line eq "id  ";

# print "$comment";
# escape out newlines and special characters like # %  & _ \ |:;"' , ./
$comment =~ s/\n/\\\n/g;
$comment =~ s/\r/\\\n/g;
$comment =~ s/([\\\/\^\.\$\*\+\?\@\{\}\[\]\(\)\<\>])/\\$&/g;
$comment =~ s/([#&%_=:;"|,~`])/\\$&/g;
$comment =~ s/\'/\\\n/g;

`./addcomment $id $comment`;

&success($comment, $id);


sub site_error
{
	my ($comment, $id) = @_;
	
	#page displayed if website is malformed

		print <<END_OF_PRINTING;
		<html><head>
		<meta http-equiv="refresh" content="3; URL=submit.html">
		<title>URL Malformed!</title></head>
		<body>
		<br>Sorry, the URL you tried commenting on doesn't exist. Try submitting it!<br>
		<br> Redirecting in 3 seconds...<br>
		</body
		</html>
	
END_OF_PRINTING
}

sub success
{
	my ($comment, $id) = @_;
# 	print "id is $id";

	#page displayed if info is sent successfully

		print <<END_OF_PRINTING;
		<html><head>
		<meta http-equiv="refresh" content="3; URL=url.pl.cgi?id=$id">
		<title>URL Received!</title></head>
		<body>
		<br>Thanks, your comment has been received!<br>
		<br> Redirecting to the URL's page in 3 seconds...<br>
		</body
		</html>
	
END_OF_PRINTING

	exit;
}
