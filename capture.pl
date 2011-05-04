#!/usr/bin/perl

# Captures the given URL as an Image
# and stores it in the given path. 
# Written by Jervis Muindi
# May  04, 2011


# Arguments are   
# url - url to capture
# imagename - name of image file with extension. 

use Cwd;  # for changing current working directory
use strict; # stop us from doing stupid things 

my $IMAGE_REL_PATH = "../../snaps/";
my $WINE_REL_PATH = "wine/bin/";

# Get Commandline Arguments
my $url = $ARGV[0]; 
my $image_name = $ARGV[1];

chdir $WINE_REL_PATH or die "Cannot Change Directory to $WINE_REL_PATH \n";   # change directory with wine executable

my $img_path = "$IMAGE_REL_PATH" . "$image_name"; 

my $cmd = "./wine phantomjs.exe rasterize.js $url $img_path"; 

my $output = `$cmd`; # Run Capture Command. 

print "Capture Success\n";  # Output OKAY Status. 

exit(0); # Output OKAY Status. 
