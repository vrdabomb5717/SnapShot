#!/usr/bin/perl --
# Top 10 Most Votes
# Written by Varun Ravishankar and Jervis Muindi
# May 6th , 2011

use strict;
use warnings;
use CGI qw/:all/;

my $SQL_PATH = "sql"; 

chdir $SQL_PATH;  # change to directory with SQL 

my $urls = `./getTopURLByVote 10`;

my @list = split("==========", $urls);

my $ip = $ENV{'REMOTE_ADDR'};
`./addIP $ip`;

&htmlprint(@list);


sub htmlprint
{
	my @list = @_;

	## Print the HTML 
	print "Content-type: text/html\n\n"; # declaration for cgi script
	print <<END_OF_HTML;
		
		<!DOCTYPE html>
		<!--[if lt IE 7 ]> <html lang="en" class="no-js ie6"> <![endif]-->
		<!--[if IE 7 ]> <html lang="en" class="no-js ie7"> <![endif]-->
		<!--[if IE 8 ]> <html lang="en" class="no-js ie8"> <![endif]-->
		<!--[if IE 9 ]> <html lang="en" class="no-js ie9"> <![endif]-->
		<!--[if (gt IE 9)|!(IE)]><!--> 
		<html lang="en" class="no-js"> <!--<![endif]-->
		<head>
		<style type="text/css">
		
		</style>
			<meta charset="UTF-8">
			<meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1">
			
			<title>SnapShot!</title>
			<meta name="description" content="A website that takes screenshots of any URL you submit.">
			<meta name="author" content="Varun Ravishankar">
			
			<meta name="viewport" content="width=device-width, initial-scale=1.0">
			
			<link rel="shortcut icon" href="/favicon.ico">
			<link rel="stylesheet" href="css/slimbox2.css" type="text/css" media="screen" />
		 	<link rel="stylesheet" href="css/style.css?v=2">
			
		<!--
			<link rel="apple-touch-icon" href="/apple-touch-icon.png">
			<link rel="stylesheet" media="handheld" href="css/handheld.css?v=2">
		-->
			
			<script src="js/libs/modernizr-1.7.min.js"></script>
			<script type="text/javascript" src="js/libs/jquery-1.5.2.min.js"></script>
			<script type="text/javascript" src="js/slimbox2.js"></script>
		</head>
		<body>
			<div id="container">
				<header>
					<nav id="header">
						<ul id="navigation">
							<li><a href="index.pl.cgi">Home</a></li>
							<li><a href="submit.html">Submit Website</a></li>
							<li><a href="popular.pl.cgi">Most Popular</a></li>
							<li><a href="recent.pl.cgi">Most Recent</a></li>
							<li><a href="mostviews.pl.cgi">Most Viewed</a></li>
							<li><a href="random.pl.cgi">Random</a></li>
							<li><a href="stats.pl.cgi">Statistics</a></li>
							<li><a href="about.html">About</a></li>
						</ul>
					</nav>
					<title> Most Votes </title>
				</header>
END_OF_HTML

	my $bool = 0;
	print "<br>";
	
	# iterate through URLs and split info
	foreach my $line(@list)
	{
		print "<br><br>";
		chomp;
		$line =~ s/://g;
		next if ($line eq "");
		my @strings = split(/\s+/, $line);
		
		
		my($id, $url, $category, $imagepath, $views, $votes);
		
		if($bool eq 0)
		{
			$id = $strings[1];
			$url = $strings[3];
			next if ($url eq "");
			$category = $strings[5];
			$imagepath = $strings[7];
			$views = $strings[9];
			$votes = $strings[11];
			$bool = 1;
		}
		else
		{
			$id = $strings[2];
			$url = $strings[4];
			next if ($url eq "");
			$category = $strings[6];
			$imagepath = $strings[8];
			$views = $strings[10];
			$votes = $strings[12];
		}

		$url =~ s/http\/\//http:\/\//g;
		my $domain = $url;
		
		if($domain =~ /([^:]*:\/\/)?([^\/]*\.)*([^\/\.]+)\.[^\/]+/g)
		{
			$domain = $3;
		}
		print "<div id=\"main\" role=\"main\">";
		print "<a href=$url>$url</a> (<a href=categories.pl.cgi?category=$category>$category</a>)<br><br>";
		print "<a href=$imagepath rel=\"lightbox\" title=\"$domain\">
				<img src=\"$imagepath\" alt=\"$domain\" title=\"$domain.\" width=\"200\" height=\"200\"/>
				<br/></a>";
		
		print "Views: $views<br>";
		print "Votes: $votes <a href=\"voteup.pl.cgi?id=$id\"><img src=\"images/up.png\" alt=\"Vote up.\"></a>&nbsp<a href=\"votedown.pl.cgi?id=$id\"><img src=\"images/down.png\" alt=\"Vote down.\"></a><br>";
		print "<br>";
		print "<a href=url.pl.cgi?id=$id>More Info here</a> <br>";
		
		print "</div>";
	}

	print <<END_OF_HTML;
				<footer>
					<nav id="navlinks">
						<h1>Navigation</h1>
						<ul>
							<li><a href="index.pl.cgi">Home</a></li>
							<li><a href="submit.html">Submit Site</a></li>
							<li><a href="about.html">About</a></li>
						</ul>
					</nav>
					<nav id="links">
					<h1>Other Links</h1>
					<ul>
						<li><a href="categories.pl.cgi">Categories</a></li>
						<li><a href="leastpopular.pl.cgi">Least Votes</a></li>
						<li><a href="leastviews.pl.cgi">Least Views</a></li>
					</ul>
					</nav>
					<p class="copyright">Copyright &copy 2011 Varun Ravishankar and Jervis Muindi</p>
				</footer>
			</div>
			<script src="//ajax.googleapis.com/ajax/libs/jquery/1.5.2/jquery.min.js"></script>
			<script>!window.jQuery && document.write(unescape('%3Cscript src="js/libs/jquery-1.5.2.min.js"%3E%3C/script%3E'))</script>
			<script src="js/plugins.js"></script>
			<script src="js/script.js"></script>
			<!--[if lt IE 7 ]>
			<script src="js/libs/dd_belatedpng.js"></script>
			<script> DD_belatedPNG.fix('img, .png_bg');</script>
			<![endif]-->
		</body>
		</html>
END_OF_HTML
}