#!/usr/bin/perl

# A Simple Test Client
# Send text input to a server
# Written by Jervis Muindi
# April  16, 2011

use strict;
use IO::Socket::INET;
$| = 1; # auto flush buffers


my $server_name = $ARGV[0]; # name of server to connect to
my $server_port = $ARGV[1]; # port number. 
my $input; # msg to send to server
my $server_socket;
my $server_response; #store servers reply


#$server_name = 'localhost'; # debuggin'
#$server_port = '7777'; # debuggin' 

if(int(@ARGV) != 2){ # do simple argument validation
	die "Please enter only a  server address and port number to connect to." .
		"For example: client-lab4.pl localhost 7777";
}

print "Server is $server_name and port is $server_port";
$server_socket = IO::Socket::INET->new( # create new socket and connect to specified address
								PeerAddr => $server_name,
								PeerPort => $server_port,
								Proto => 'tcp'
								);
					
die "Cannot create a connection to the server: Connection Refused ! " unless $server_socket; # debuggin code

print "Connected to server $server_name:$server_port. Please enter text to be sent to server\n";
#$server_socket = $socket->connect(); # connect to the server
#$socket->send("HELLO MSG FROM CLIENT");

while($input = <STDIN>){ # get getting user input
	chomp($input); # remove last new line char
	#print "User input is: $input"; # debuggin code
	$server_socket->send($input); # send to server.
	
	$server_socket->recv($server_response,256); # wait for 256 bytes chunk of data and store in $user_input . 
	print "Server:$server_response";
	
	if($server_response eq 'Server has exited'){
		exit; # close client program
	}
}


