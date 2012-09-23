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
function geospatial_shapefile($wkt_features, $options = array()) {
  geophp_load();
  $store_features = array();
  $wkt = array();
  
  foreach ($wkt_features as $wkt_feature) {
    if (!isset($wkt_feature['WKT']) || empty($wkt_feature)) {
      continue;
    }
    $store_features[] = $wkt_feature['WKT'];
  }
  if ($store_features) {
    // If there is more than one value to save, wrap in GeometryCollection
    if (isset($store_features[1])) {
      $wkt = array('wkt' => sprintf('GEOMETRYCOLLECTION(%s)', implode(',', $store_features)));
    }
    else {
      $wkt = array('wkt' => $store_features[0]);
    }
  }
  
  return geoPHP::load($wkt['wkt'], 'wkt');
}

function geospatial_shapefile_field($field, $field_item) {
  if ($field['type'] == 'file') {
    if ($field_item['fid']) {
      $file = file_load($field_item['fid']);
      //$data = file_get_contents($file->uri);
      $features = geospatial_shapefile_get_wkt($file->uri);
      //$features = geospatial_file_parse_wkt_features($features);
      
      return geospatial_shapefile($features);
    } else {
      //if there's no file we want to put an empty value into the field.
      return geospatial_shapefile(array());
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
