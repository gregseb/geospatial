<?php

/**
 * Could also look at parsing shapefiles manually: http://en.wikipedia.org/wiki/Shapefile#Shapefile_shape_format_.28.shp.29
 * Could also implement Iterator: http://php.net/manual/en/class.iterator.php
 */
function _geospatial_parse_wkt_from_spatial_file($uri) {
  module_load_include('inc', 'geospatial', 'includes/ogr2ogr');
  $wkt_values = array();

  $ogr2ogr = new ogr2ogr($uri);

  // Check the file type, extract any relevant files, and run ogr2ogr.
  $ogr2ogr->prepare();

  // Attempt to open the CSV created by ogr2ogr
  if ($ogr2ogr->open()) {
    $header = $ogr2ogr->fgetcsv();
    $wkt_key = array_search('WKT', $header);

    while ($row = $ogr2ogr->fgetcsv()) {
      array_push($wkt_values, $row[$wkt_key]);
    }
  }

  $ogr2ogr->close();
  return $wkt_values;
}
