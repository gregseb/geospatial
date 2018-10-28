<?php
/**
 * @file
 * geospatial.admin.inc
 */

/**
 * GeoSpatial Admin settings form.
 */
function geospatial_admin_settings() {
  $form = array();

  $form['ogr2ogr'] = array(
    '#type' => 'fieldset',
    '#title' => t('ogr2ogr'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['ogr2ogr']['geospatial_ogr2ogr_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Path'),
    '#description' => t('GeoSpatial will attempt to locate the ogr2ogr binary automatically, however the process of doing so is not reliable.  Please set the value here.'),
    '#default_value' => variable_get('geospatial_ogr2ogr_path', exec('which ogr2ogr')),
  );

  return system_settings_form($form);
}
