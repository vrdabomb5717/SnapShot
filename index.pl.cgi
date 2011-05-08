#!/usr/bin/perl --
# A Home Page for the SnapShot Website 
# Written by Varun Ravishankar and Jervis Muindi
# May 6th , 2011

use strict;
use warnings;
use CGI qw/:all/;


my $ip = $ENV{'REMOTE_ADDR'}; # get IP

chdir "sql";  # change to SQL

`./addIP $ip`; # add IP to DB




sub printhtml{
	
	print <<EOF
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
					<li><a href="index.html">Home</a></li>
					<li><a href="submit.html">Submit Website</a></li>
					<li><a href="popular.pl.cgi">Most Popular</a></li>
					<li><a href="recent.pl.cgi">Most Recent</a></li>
					<li><a href="stats.pl.cgi">Statistics</a></li>
					<li><a href="about.html">About</a></li>
				</ul>
			</nav>
		</header>
		
		<hgroup id="title">
			<h1>SnapShot!</h1>
			<h2>Like Digg, only not dead.</h2>
		</hgroup>

		<div id="main" role="main">
		
		<p>The main text goes here.</p>

		</div>

		<footer>
			<nav id="navlinks">
				<h1>Navigation</h1>
				<ul>
					<li><a href="index.html">Home</a></li>
					<li><a href="stats.pl.cgi">Statistics</a></li>
					<li><a href="about.html">About</a></li>
				</ul>
			</nav>
			<nav id="links">
				<h1>Browse Websites</h1>
				<ul>
					<li><a href="submit.html">Submit Website</a></li>
					<li><a href="popular.pl.cgi">Most Popular</a></li>
					<li><a href="recent.pl.cgi">Most Recent</a></li>
				</ul>
			</nav>
			<p class="copyright">Copyright � 2011 Varun Ravishankar and Jervis Muindi</p>
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



EOF
	
}