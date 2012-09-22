<?php
// $Id$

/**
 * @file
 * Plugin to provide a kml geocoder.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t("Shapefile"),
  'description' => t('Get the geometry out of a zipped up archive of shapefile data.'),
  'callback' => 'geospatial_shapefile',
  'field_types' => array('file'),
  'field_callback' => 'geospatial_shapefile_field',
);

/**
 * Process Markup
 */
function geospatial_shapefile($features, $options = array()) {
  geophp_load();
  return geoPHP::load($features[0]['wkt'], 'wkt');
}

function geospatial_shapefile_field($field, $field_item) {
  if ($field['type'] == 'file') {
    if ($field_item['fid']) {
      $file = file_load($field_item['fid']);
      //$data = file_get_contents($file->uri);
      $features = geospatial_shapefile_get_wkt($file->uri);
      $features = geospatial_file_parse_wkt_features($features);
      
      return geospatial_shapefile($features);
    }
  } else {
    // Something has gone wrong...
  }
}

/**
 * extract geodata from shapefile.
 */
function geospatial_shapefile_get_wkt($shapefile_uri) {
  if ($shapefile = geospatial_shapefile_open($shapefile_uri)) {
    if ($spatial_features = $shapefile->process()) {
      return $spatial_features;
    }
  }

  return NULL;
}

/**
 * Open a stream to a Shapefile
 */
function geospatial_shapefile_open($uri) {
  module_load_include('inc', 'geospatial', 'geospatial_shapefile.class');
  if ($shapefile = new SpatialShapefile($uri)) {
    return $shapefile;
  }
}
