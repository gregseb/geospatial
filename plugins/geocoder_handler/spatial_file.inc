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
  'title' => t("Spatial file"),
  'description' => t('Get the geometry out of a spatially enabled file, such as kml, kmz, or shpz.'),
  'callback' => 'geospatial_spatial_file',
  'field_types' => array('file'),
  'field_callback' => 'geospatial_spatial_file_field',
);

/**
 * Process Markup
 */
function geospatial_spatial_file($wkt_features, $options = array()) {
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

function geospatial_spatial_file_field($field, $field_item) {
  if ($field['type'] == 'file') {
    if ($field_item['fid']) {
      $file = file_load($field_item['fid']);
      //$data = file_get_contents($file->uri);
      $features = geospatial_spatial_file_get_wkt($file->uri);
      //$features = geospatial_file_parse_wkt_features($features);

      return geospatial_spatial_file($features);
    } else {
      //if there's no file we want to put an empty value into the field.
      return geospatial_spatial_file(array());
    }
  } else {
    // Something has gone wrong...
  }
}

/**
 * extract geodata from spatial_file.
 */
function geospatial_spatial_file_get_wkt($spatial_file_uri) {
  if ($spatial_file = geospatial_spatial_file_open($spatial_file_uri)) {
    if ($spatial_features = $spatial_file->process()) {
      return $spatial_features;
    }
  }

  return NULL;
}

/**
 * Open a stream to a Spatial_File
 */
function geospatial_spatial_file_open($uri) {
  module_load_include('inc', 'geospatial', 'geospatial_spatial_file.class');
  if ($spatial_file = new SpatialSpatial_File($uri)) {
    return $spatial_file;
  }
}
