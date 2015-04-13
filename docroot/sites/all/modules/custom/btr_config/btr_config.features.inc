<?php
/**
 * @file
 * btr_config.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function btr_config_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function btr_config_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function btr_config_image_default_styles() {
  $styles = array();

  // Exported image style: 1280x720.
  $styles['1280x720'] = array(
    'label' => '1280x720',
    'effects' => array(
      3 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 1280,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => -10,
      ),
      1 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => '',
          'height' => 720,
          'upscale' => 1,
        ),
        'weight' => -9,
      ),
    ),
  );

  // Exported image style: 128x72.
  $styles['128x72'] = array(
    'label' => '128x72',
    'effects' => array(
      3 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 128,
          'height' => 72,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: 640x360.
  $styles['640x360'] = array(
    'label' => '640x360',
    'effects' => array(
      3 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 640,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
      4 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => '',
          'height' => 360,
          'upscale' => 1,
        ),
        'weight' => 2,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function btr_config_node_info() {
  $items = array(
    'article' => array(
      'name' => t('Article'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'band' => array(
      'name' => t('Band'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'city' => array(
      'name' => t('City'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'release' => array(
      'name' => t('Release'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'venue' => array(
      'name' => t('Venue'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'video' => array(
      'name' => t('Video'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
