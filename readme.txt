Readme for SnapShot: 
Advanced Programming Project 2
Jervis Muindi and Varun Ravishankar
8th May 2011

Setup
===========
To setup snapshot, please untar the zipped file. Snapshot has a dependency on Wine to do the screencapture of websites and we have pre-included a portable wine installation
for you already. After unpacking, you need to compile the C++ SQL tools that run in the backend. To do this, change to the sql directory and type 'make all'

Issues
==================
We had great trouble getting a tool that worked each time, every time. Webthumb does not work reliably at all and so we decided not to use and find somethign better.Given the restricted environment of the CLIC lab (we couldn't install any programs), this was a great challenge. There were a few Linux programs that did a similar job to webthumb but they had dependencies on other software that the CLIC environment did not have. In the end, after much alot 
of effort, we got PhantomJS running in the backend in. 

External Tools
==================
We used PhantomJS, HTML5 Boilerplate, Modernizr, jQuery 1.5.2, and Slimbox 2.

Jquery 1.5.2: http://jquery.com/
HTML5 Boilerplate: http://html5boilerplate.com/
Modernizr: http://www.modernizr.com/
Slimbox 2: http://www.digitalia.be/software/slimbox2

Future Dev Plans
================
Future plans for the site is to work on improving the usability and friendliness of the UI. We have a very solid and scalable backend (it's only limited by the resources on which the server is running on)
which gives us a good platform to build on great interface to the site. 


Backend Documentation:
============================
At the location of each of these programs (under the sql folder) should be a "testdb.txt" file. This file should contain a path to the SQLite Database. 
A sample working testdb.txt file has been included. 

All programs have a exit code of 0 on success and not zero if some error occurs. 
Database Structure: 

url Table has the following fields:
    -id
    -url
    -category
    -imagepath
    -views
    -votes
    -comments
Each field is pretty self-explanatory.
    
 visitor table has following fields:
    -id
    -ip
  It's used to keep track of Unique IP Vistors
  
stats table has following fields:
    -id
    -snapcount 
It's used to keep track of total snaps taken.
    
Communicating with Server Daemon
================================
Server program should be ran in full X11 environment. It will not work properly when ran over SSH. 
The tool that the server program uses (PhantomJS) to do the website screen capture has a dependecy on Wine, 
so if you do not use the provided Wine installation, make sure you have a working Wine installation. 

There is a server daemon process running on suva.clics.cs.columbia.edu on Port 7777. 
Once connected, send a secret key first - "0DF509F6DE" without the quotes. Also make sure that you have it all caps as password
is case sensitive. We decided to use a secret key because after running server unattended for a while, I noted unsolicited random connection
attempts from the internet. 

After that, send a list of URLs to be snapped/captured. 
These should be full and VALID urls. 
The format in which the URLs should be sent should be as follows: 
    category, vote, URL
    Note: vote is either 1 or 0. 1 means Vote up this URL by that many points. 
    For example: my-fake-cat,1,http://msn.com
   
Once done, send the word "quit" to start the capture process on the server daemon. 
The server will update the Database accordingly. 
From testing, it takes 5 seconds to capture a given URL. 
The images will be stored in the /snaps folder and the name of the image is the SHA1 hash of the url. 


Return Format of SQL C++ Programs:
===================================
Program that return info on multiple URLs this delimiter "==========" on a new Line. See sample below:
id : 6
url : www.hahahaha.com
category : no-category
imagepath : my-fake-path
views : 0
votes : 1
==========
id : 5
url : www.yahoo.com
category : test0
imagepath : image-test-path0
views : 2
votes : 100
==========


Backend Specification (Jervis):
=============================
In Running the SQL c++ programs, make sure that you run them from the same directory as the programs are located in. 

1) addcomment
This adds a Comment to a specified URL in the SQL database.
Needs 3 arguments: url_id, comment_to_add

2) getURLid
Returns URL id of given url string.
Outputs nothing if url not found. 
Arguments: url_id

3) getURLinfo
Return detailed information on URL with specified ID
Note that comments are not returned. To get comments, use the getComment program. 
Arguments: url_id

4) SQLiteDB.cpp
SQL C++ class that contains the methods implementing functionality needed by the snapshot website

5) getBottomURLByVote
Return detailed info on URLs that are the Bottom X (as sorted by user votes) of the site where X is an integer given by user at runtime.
Note that comments are not returned. To get comments, use the getComment program. 
Arguments: Number of Bottom URLs to return.

6) getBottomURL
Return detailed info on URLs that are the Bottom X (as sorted by No. of views) of the site where X is an integer given by user at runtime.
Note that comments are not returned. To get comments, use the getComment program.
Arguments: Number of Bottom URLs to return. 

7) getTopURLByVote
Return detailed info on URLs that are the TOP X (as sorted by user votes) of the site where X is an integer given by user at runtime.
Note that comments are not returned. To get comments, use the getComment program.
Arguments: Number of Top URLs to return.

8) getTopURL
Return detailed info on URLs that are the Top X (as sorted by No. of views) of the site where X is an integer given by user at runtime.
Note that comments are not returned. To get comments, use the getComment program.
Arguments: Number of Top URLs to return. 

9) getRandURL
Return detailed info on Randomly selected URLs.
Note that comments are not returned. To get comments, use the getComment program. 
Arguments: Number of Random URLs to return. 

10) addIP
Adds given IP to visitors table in database
Note that only if an IP does not already exist is it then
added to the database. Adding an already existing IP has no effect. 
Outputs "0" on success and "-1" if operation fails. 
Arguments: IP Address to Add. 


11) getViewCount
Return the number of views count for given URL ID stored in the database file.
If an error occurs, view count returned is "-1" 
Arguments: url_id

12) getURLByCat
Return detailed info on URLs in the specified category.
Note that comments are excluded from the data returned.
Arguments: A Category

13) increaseViewCount
Increments the view count for the specified URL-id 
Outputs 0 on success and -1 on error. 
Arguments: url_id

14) voteup
Votes up the given URL ID
Outputs 0 on success and -1 on error
Arguments: url_id

15) votedown
Votes down the given URL ID
Outputs 0 on success and -1 on error
Arguments: url_id

16) addurl
This adds a URL to the SQL database.
Needs 4 Arguments: url, category, imagepath, votes 
where: 
    URL - the full URL of the webpage/site
    category - category of the URL, if any. This should be ONE WORD w/o spaces.
    imagepath - full image path to image of webpage
    votes - 1 or 0. Indicates if user chose to Vote UP URL when adding it. 
Outputs 0 on success and -1 on error. 

17) incrementSnaps
Increment Number of URL Snapshots taken that is stored in the SQLite database
Outputs 0 on success and -1 on error. 

18) countIP
Returns the Number of Unique IP Visitors Stored in visitors table
Outputs -1 if an error occurs. 

19) getcomment
Returns the comment(s) for the given  URL id
Comments are separated from each other by this
delimeter on a new line "^^^^a94a8fe5ccb19ba61c4c0873d391e987982fbbd3^^^^"  without the quotes
Arguments: url_id

20) getURLrecent
Returns the most recent X URLs uploaded to the site. X is an integer specified by the user.
Arguments: Number of recent URLs to return. 

21) countSnaps
Returns the number of URL snaps takens. 
Outputs -1 if an error occurs. 
Takes no arguments.


Frontend Specification (Varun):
=============================
Each of the CGI pages should be run from the web. Data is sent via GET and POST for the CGI files.

1) about.html
A basic about page describing the goal of the project and the tools used to create it.

2) comments.pl.cgi
A Perl CGI file that submits comments to the database given a URL id.

3) css/style.css
The main stylesheet for the site. Themes the fonts, header, and footer.

4) favicon.ico
A silly little favicon for the website.

5) humans.txt
Text file that contains credits for tools used and team member info.

6) index.pl.cgi
The main page, that displays 5 random URLs for people to view and vote on.

7) js
Contains the Jquery file, Slimbox 2 files, and some basic functions for loading pictures.
 
8) leastpopular.pl.cgi
Displays 10 least popular URLs by votes.

9) leastviews.pl.cgi
Displays 10 least popular URLs by views.

10) mostviews.pl.cgi
Displays 10 most popular URLs by views.

11) popular.pl.cgi
Displays 10 most popular URLs by votes.

12) random.pl.cgi
Displays 10 random URLs for people to view and vote on.

13) recent.pl.cgi
Displays 10 recent URLs for people to view.

14) robots.txt
Lists pages to index on the site.

15) stats.pl.cgi
Displays stats about the site, like URLs on the site, total views, and total unique visitors.

16) submit.html
Page displayed when user attempts to add a new URL to the site.

17) submit.pl.cgi
CGI file that sends to server and asks it to generate a new image file.

18) url.pl.cgi
More info page displayed that displays info about URL and allows you to view comments.

19) votedown.pl.cgi
Votes a URL down in the database. Negative votes are allowed.

20) voteup.pl.cgi
Votes a URL up in the database.

21) categories.pl.cgi
Displayed when a user attempts to view a category. When no info is passed over GET, the category selection is displayed. Otherwise, all URLs in a category are displayed.