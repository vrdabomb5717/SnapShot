#!/usr/bin/perl

use strict;
use warnings;
use CGI qw/:all/;
use IO::Socket::INET;
# $| = 1; # auto flush buffers

my (@pairs, $key, $value, $inputstring);

my $q = CGI->new(); # cgi object
print $q->header();

my $url = $q->param('url'); #url
my $category = $q->param('category'); #category
my $ip = $ENV{'REMOTE_ADDR'};
my $votes = 0;

#($url, $category) = @ARGV; # debugging code. 
# print @ARGV; # debuggin code

my $server_name = "suva.clic.cs.columbia.edu"; # name of server to connect to
my $server_port = 7777; # port number. 
my $input; # msg to send to server
my $server_socket;
my $server_response; #store servers reply

if(!defined($url) || !defined($category) || $url eq '' || $category eq '') # doesn't accept empty submissions
{ 
	# do simple argument validation
	&site_error();
	exit; # Stop running script. 
}

$server_socket = IO::Socket::INET->new( # create new socket and connect to specified address
								PeerAddr => $server_name,
								PeerPort => $server_port,
								Proto => 'tcp'
								);
				
die "Cannot create a connection to the server: Connection Refused ! " unless $server_socket; # debuggin code

# print "url is $url<br>";
# print "category is $category<br>";

# insert into DB here by sending the URL to the image-capturing screenshot on some server somewhere
$server_socket->send("0DF509F6DE");
$server_socket->recv($server_response,256); # wait for server connection accept message. 
$server_socket->send("$category,0,$url"); # send the url to the server. 
$server_socket->recv($server_response,256); # wait for 256 bytes chunk of data and store in $user_input . 
$server_socket->send("quit");
close $server_socket;  # close the connection. 

&success();
exit;

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

sub success
{
	#page displayed if info is sent successfully

		print <<END_OF_PRINTING;
		<html><head>
		<meta http-equiv="refresh" content="3; URL=index.html">
		<title>URL Received!</title></head>
		<body>
		<br>Thanks, your URL has been received!<br>
		<br> Redirecting to the home page in 3 seconds...<br>
		</body
		</html>
	
END_OF_PRINTING
}
