<?php
/**
 * @file
 * btr_config.ds.inc
 */

/**
 * Implements hook_ds_view_modes_info().
 */
function btr_config_ds_view_modes_info() {
  $export = array();

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'attachment';
  $ds_view_mode->label = 'Attachment';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['attachment'] = $ds_view_mode;

  return $export;
}
