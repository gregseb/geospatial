;TODO; A better writer than myself reword this readme.

CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Installation
 * Instructions 
 
INTRODUCTION
------------

This is an adaption of the spatial 7 module written by Affinity Bridge.  The
code for parsing shapefiles has been thus far taken straight from spatial
(https://github.com/affinitybridge/spatial).  This repository is a space to store this
adaption until it's fate is decided.

INSTALLATION
------------

Depends on the geofield, geophp, geocoder, ctools, ogr2ogr, and file modules.
Basic drupal contributed module installation.
See http://drupal.org/documentation/install/modules-themes/modules-7
for more info.


INSTRUCTIONS
------------

1. Enable geospatial module and dependancies
2. Create a content type
3. Add a file field
4. Add a geofield and select the geocoder from other field widget.
5. choose the file field made in step 3 and select the shapefile geocoder plugin.