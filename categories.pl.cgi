#!/usr/bin/perl --
# A Basic Sample Statistics Page for SnapShot
# Written by Jervis Muindi and Varun Ravishankar
# May 6th , 2011

use strict;
use warnings;
use CGI qw/:all/;


my $SQL_PATH = "sql"; 

chdir $SQL_PATH;  # change to directory with SQL 

my $ip = $ENV{'REMOTE_ADDR'};
`./addIP $ip`;


my $category = $q->url_param('category'); #id 

if($category eq "" or !defined($category))
{
	&html_page;
	exit;
}






sub html_page
{
	## Print the HTML 
	print "Content-type: text/html\n\n"; # declaration for cgi script
	print <<END_OF_HTML;
		
			<!DOCTYPE html>
		<!--[if lt IE 7 ]> <html lang="en" class="no-js ie6"> <![endif]-->
		<!--[if IE 7 ]>    <html lang="en" class="no-js ie7"> <![endif]-->
		<!--[if IE 8 ]>    <html lang="en" class="no-js ie8"> <![endif]-->
		<!--[if IE 9 ]>    <html lang="en" class="no-js ie9"> <![endif]-->
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
			<link rel="stylesheet" href="css/style.css?v=2">
			
		<!--
			<link rel="apple-touch-icon" href="/apple-touch-icon.png">
			<link rel="stylesheet" media="handheld" href="css/handheld.css?v=2">
		-->
			
			<script src="js/libs/modernizr-1.7.min.js"></script>
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
					<title> View Categories </title>
				</header>
		
				<div id="main" role="main">
				<br><br>
				<h1> Categories </h1>
				<br><br>
				<ul id="navigation">
							<li><a href="categories.pl.cgi?category=\"News\">News</a></li>
							<li><a href="categories.pl.cgi?category=\"Business\">Business</a></li>
							<li><a href="categories.pl.cgi?category=\"Politics\">Politics</a></li>
							<li><a href="categories.pl.cgi?category=\"Technology\">Technology</a></li>
							<li><a href="categories.pl.cgi?category=\"Gaming\">Gaming</a></li>
							<li><a href="categories.pl.cgi?category=\"Science\">Science</a></li>
							<li><a href="categories.pl.cgi?category=\"Entertainment\">Entertainment</a></li>
							<li><a href="categories.pl.cgi?category=\"Sports\">Sports</a></li>
							<li><a href="categories.pl.cgi?category=\"Other\">Other</a></li>
						</ul>
		
				</div>
		
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