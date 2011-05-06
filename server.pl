#!/usr/bin/perl

# Simple Image Server
# Waits for a client connection and forks a new 
# new thread to handle that connection. 
# 
# Written by Jervis Muindi
# 18th April  2011

##### Still to DO : ##############
 # * Process User Input of URLs and take screenshots


use strict;
use IO::Socket::INET; # import network socket
use Digest::SHA qw(sha1 sha1_hex sha1_base64); # import SHA 1 hash


$| = 1; # auto flush buffers

my $port; # user defined port number
if(int(@ARGV) != 1){
	$port = 7777; # default listening port
	print "\nPlease enter only a single argument for the port. Using default port of 7777...\n";
}
else{
	$port = $ARGV[0]; 
}


my $socket;
my $reverse_input; 

#ReusePort => 1, # disabled b'se it causes an error. 
#LocalAddr => Don't use 'localhost' so that we bind to ALL network interfaces. 

$socket = IO::Socket::INET->new(	
						LocalPort => "$port", # port number
						Proto => 'tcp', # use TCP connenction
						Listen => 5 # limit max simultanenous conenctions to 5 a time
			
						);
die "Couldn't open start server" unless $socket; # Exit if error occured opening socket

print "\n TCP Server waiting for client on port $port\n";

$SIG{CHLD} = 'IGNORE'; # kill zoombie process. (Works on UNIX-only)

##### Fork new child processes for each new connection received #######

REQUEST:
while(my $client_socket = $socket->accept()) { # Wait for and accept new incoming connection
	my $kidpid;	
	if($kidpid = fork){
		close $client_socket;
		next REQUEST;
	}

	defined($kidpid) or die "cannot fork: $!" ;
	close $socket; # Child closese unused handle that was copied over when process was forked. 
	select($client_socket); # new default for prints
	$| = 1; # autoflush
	

	#per connection child node des IO with Client socket handle

	##### Process Client Input ####
	my @urls; # keep list of urls. 
	while(1){ # Continous keep on printing user input
	
		my $line; # store read line input from client.
		my $user_input;

		$client_socket->recv($user_input,256); # wait for 256 bytes chunk of data and store in $user_input . 
		print STDOUT "Server-received:$user_input\n";

		if(lc($user_input) eq "quit"){ # quit, if user enters 'quit' 
			print STDOUT "Exiting server\n";
			print STDOUT "We got the following:\n";
			print STDOUT @urls; 
			$client_socket->send("Server has exited"); # send closing msg
		   #close $client_socket;
			last;
		}

	push @urls, $user_input; # add user-input to list. 

	#$reverse_input = reverse($user_input); # reverse input
	$client_socket->send("Input received\n"); # send ACK to client. 
	
	}

	### To do:  Process User Input of URLs
	
	#my $hash; # store url hash which is what will be used to name image file.
	my $cap_cmd; # store command to capture image file
	my $rc; # store return code
	my $img_name; # name of image file. stored as a hash. 
	foreach my $line(@urls){
		
		my @list = split(',', $line);  # Input should be in form: category,vote,URL
		my $cat = $list[0]; #category
		my $vote = $list[1]; #vote count. It's a 0/1
		my $url = $list[2]; # URL path

		print STDOUT "cat: $cat \n";
		print STDOUT "vote : $vote \n"; 
		print STDOUT "url : $url \n"; 
	
		$url = lc($url); # convert to lower case. 

		$img_name = sha1_hex($url) . ".png"; # hash lowercase url to get image name. 
		$cap_cmd = "./capture.pl $url $img_name";
		
		$rc = system($cap_cmd); # run capture command. 	

		# add to the DB
		my $add_cmd = "./addurl.pl $cat $vote $url"; 

		system($add_cmd); # add to the SQLite database

	}

	close $client_socket;
	exit; #don't let the child process back to accept !
}
sub reverse{ # reverses string
	my $string = $_[0];
	$string = scalar reverse $string; #reverse string
	return $string;
}

