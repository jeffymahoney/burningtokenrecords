<?php

/**
 * @file
 * Advanced CSS/JS aggregation module.
 *
 * File used to store hook_advagg_* hooks.
 */

// @ignore sniffer_commenting_functioncomment_hookparamdoc:11
/**
 * Implements hook_advagg_save_aggregate_alter().
 *
 * Used to add in a .gz file if none exits.
 *
 * @param array $files_to_save
 *   Array($uri => $contents).
 * @param array $aggregate_settings
 *   Array of settings.
 * @param array $other_parameters
 *   Array of containing $files & $type.
 */
function advagg_advagg_save_aggregate_alter(array &$files_to_save, array $aggregate_settings, array $other_parameters) {
  // Return if gzip is disabled.
  if (empty($aggregate_settings['variables']['advagg_gzip'])) {
    return;
  }

  // See if a .gz file already exists.
  $gzip_exists = FALSE;
  foreach ($files_to_save as $uri => $contents) {
    // See if this uri contains .gz near the end of it.
    $pos = strripos($uri, '.gz', 91 + strlen(ADVAGG_SPACE) * 3);
    if (!empty($pos)) {
      $len = strlen($uri);
      // .gz file exists, exit loop.
      if ($pos == $len - 3) {
        $gzip_exists = TRUE;
        break;
      }
    }
  }

  // If a .gz file does not exist, create one.
  if (!$gzip_exists) {
    // Use the first file in the array.
    $data = reset($files_to_save);
    $uri = key($files_to_save);
    // Compress it and add it to the $files_to_save array.
    $compressed = gzencode($data, 9, FORCE_GZIP);
    $files_to_save[$uri . '.gz'] = $compressed;
  }
}

// @ignore sniffer_commenting_functioncomment_hookparamdoc:10
/**
 * Implements hook_advagg_build_aggregate_plans_alter().
 *
 * Used to alter the plan so it has the same grouping as cores.
 *
 * @param array $files
 *   List of files in the aggregate as well as the aggregate name.
 * @param bool $modified
 *   Change this to TRUE if $files has been changed.
 * @param string $type
 *   String containing css or js.
 */
function advagg_advagg_build_aggregate_plans_alter(array &$files, &$modified, $type) {
  // Do nothing if core grouping is disabled.
  if (!variable_get('advagg_core_groups', ADVAGG_CORE_GROUPS)) {
    return;
  }

  $temp_new_files = array();
  $counter = 0;
  foreach ($files as $data) {
    $group = NULL;
    $every_page = NULL;
    foreach ($data['files'] as $fileinfo) {
      // Grouped by group & every_page variables.
      if (is_null($group)) {
        $group = $fileinfo['group'];
      }
      if (is_null($every_page)) {
        $every_page = $fileinfo['every_page'];
      }

      // Bump Counter if group/every_page has changed from the last one.
      if ($group != $fileinfo['group'] || $every_page != $fileinfo['every_page']) {
        ++$counter;
        $group = $fileinfo['group'];
        $every_page = $fileinfo['every_page'];
        $modified = TRUE;
      }
      $temp_new_files[$counter][] = $fileinfo;
    }
    ++$counter;
  }

  // Replace $files array with new aggregate filenames.
  $files = advagg_generate_filenames(array($temp_new_files), $type);
}


/**
 * Implements hook_advagg_context_alter().
 */
function advagg_advagg_context_alter(&$original, $aggregate_settings, $mode) {
  if ($mode == 0) {
    // Change context.
    $original['base_root'] = $GLOBALS['base_root'];
    $original['base_url'] = $GLOBALS['base_url'];
    $original['base_path'] = $GLOBALS['base_path'];
    $original['is_https'] = $GLOBALS['is_https'];
    $original['language'] = isset($GLOBALS['language']) ? $GLOBALS['language'] : NULL;

    $GLOBALS['is_https'] = $aggregate_settings['variables']['is_https'];
    if ($aggregate_settings['variables']['is_https']) {
      $GLOBALS['base_root'] = str_replace('http://', 'https://', $GLOBALS['base_root']);
      $GLOBALS['base_url'] = str_replace('http://', 'https://', $GLOBALS['base_url']);
    }
    else {
      $GLOBALS['base_root'] = str_replace('https://', 'http://', $GLOBALS['base_root']);
      $GLOBALS['base_url'] = str_replace('https://', 'http://', $GLOBALS['base_url']);
    }
    $GLOBALS['base_path'] = $aggregate_settings['variables']['base_path'];

    if (isset($aggregate_settings['variables']['language'])) {
      $languages = language_list();
      if (isset($languages[$aggregate_settings['variables']['language']])) {
        $GLOBALS['language'] = $languages[$aggregate_settings['variables']['language']];
      }
    }
  }
  elseif ($mode == 1) {
    // Change context back.
    if (isset($original['base_root'])) {
      $GLOBALS['base_root'] = $original['base_root'];
    }
    if (isset($original['base_url'])) {
      $GLOBALS['base_url'] = $original['base_url'];
    }
    if (isset($original['base_path'])) {
      $GLOBALS['base_path'] = $original['base_path'];
    }
    if (isset($original['is_https'])) {
      $GLOBALS['is_https'] = $original['is_https'];
    }
    if (isset($original['language'])) {
      $GLOBALS['language'] = $original['language'];
    }
  }

  // Moved this in here due to incomplete bug reports from
  // https://www.drupal.org/node/1942230. I can not reproduce the reported
  // issues with the patch for the CDN module so I've moved the code into
  // advagg.
  if (!function_exists('cdn_advagg_context_alter') && module_exists('cdn')) {
    if ($mode == 0) {
      // Save original context.
      $original[CDN_MODE_VARIABLE] = variable_get(CDN_MODE_VARIABLE, CDN_MODE_BASIC);
      $original[CDN_BASIC_FARFUTURE_VARIABLE] = variable_get(CDN_BASIC_FARFUTURE_VARIABLE, CDN_BASIC_FARFUTURE_DEFAULT);
      $original[CDN_HTTPS_SUPPORT_VARIABLE] = variable_get(CDN_HTTPS_SUPPORT_VARIABLE, FALSE);
      $original[CDN_STATUS_VARIABLE] = variable_get(CDN_STATUS_VARIABLE, CDN_DISABLED);

      // Set context for file_create_url()/cdn_file_url_alter().
      $GLOBALS['conf'][CDN_MODE_VARIABLE] = isset($aggregate_settings['variables'][CDN_MODE_VARIABLE])
        ? $aggregate_settings['variables'][CDN_MODE_VARIABLE]
        : variable_get(CDN_MODE_VARIABLE, CDN_MODE_BASIC);
      $GLOBALS['conf'][CDN_BASIC_FARFUTURE_VARIABLE] = isset($aggregate_settings['variables'][CDN_BASIC_FARFUTURE_VARIABLE])
        ? $aggregate_settings['variables'][CDN_BASIC_FARFUTURE_VARIABLE]
        : variable_get(CDN_BASIC_FARFUTURE_VARIABLE, CDN_BASIC_FARFUTURE_DEFAULT);
      $GLOBALS['conf'][CDN_HTTPS_SUPPORT_VARIABLE] = isset($aggregate_settings['variables'][CDN_HTTPS_SUPPORT_VARIABLE])
        ? $aggregate_settings['variables'][CDN_HTTPS_SUPPORT_VARIABLE]
        : variable_get(CDN_HTTPS_SUPPORT_VARIABLE, FALSE);
      $GLOBALS['conf'][CDN_STATUS_VARIABLE] = isset($aggregate_settings['variables'][CDN_STATUS_VARIABLE])
        ? $aggregate_settings['variables'][CDN_STATUS_VARIABLE]
        : variable_get(CDN_STATUS_VARIABLE, CDN_DISABLED);

      // Disable CDN if cdn_check_drupal_path is FALSE.
      if (empty($aggregate_settings['variables']['cdn_check_drupal_path'])) {
        $original[CDN_STATUS_VARIABLE] = CDN_DISABLED;
      }

      // Handle HTTPS.
      if (!empty($aggregate_settings['variables']['cdn_request_is_https']) && !cdn_request_is_https()) {
        if (isset($_SERVER['HTTPS'])) {
          $original['HTTPS'] = $_SERVER['HTTPS'];
        }
        else {
          $original['HTTPS'] = FALSE;
        }
        $_SERVER['HTTPS'] = 'on';
      }
    }
    elseif ($mode == 1) {
      // Set context back.
      $GLOBALS['conf'][CDN_MODE_VARIABLE] = $original[CDN_MODE_VARIABLE];
      $GLOBALS['conf'][CDN_BASIC_FARFUTURE_VARIABLE] = $original[CDN_BASIC_FARFUTURE_VARIABLE];
      $GLOBALS['conf'][CDN_HTTPS_SUPPORT_VARIABLE] = $original[CDN_HTTPS_SUPPORT_VARIABLE];
      $GLOBALS['conf'][CDN_STATUS_VARIABLE] = $original[CDN_STATUS_VARIABLE];

      // Handle HTTPS.
      if (isset($original['HTTPS']) && !is_null($original['HTTPS'])) {
        $_SERVER['HTTPS'] = $original['HTTPS'];
      }
    }
  }
}

/**
 * Implements hook_advagg_get_info_on_files_alter().
 *
 * Used to make sure the info is up to date in the cache.
 */
function advagg_advagg_get_info_on_files_alter(&$return, $cached_data, $bypass_cache) {
  // Do nothing if the ie_css_selector_limiter is disabled.
  if (!variable_get('advagg_ie_css_selector_limiter', ADVAGG_IE_CSS_SELECTOR_LIMITER)) {
    return;
  }
  $limit_value = variable_get('advagg_ie_css_selector_limiter_value', ADVAGG_IE_CSS_SELECTOR_LIMITER_VALUE);

  // Get the css path.
  list($css_path) = advagg_get_root_files_dir();
  $parts_path = $css_path[1] . '/parts';

  foreach ($return as &$info) {
    // Skip if not a css file.
    if (empty($info['fileext']) || $info['fileext'] !== 'css') {
      continue;
    }

    // Check if this is a split css file.
    if (strpos($info['data'], $parts_path) === 0) {
      $info['split'] = TRUE;
    }
    // Break large file into multiple small files if needed.
    elseif ($info['linecount'] > $limit_value) {
      advagg_split_css_file($info);
    }
  }
  unset($info);
}
