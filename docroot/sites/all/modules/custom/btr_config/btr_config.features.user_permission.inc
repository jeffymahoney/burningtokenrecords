<?php
/**
 * @file
 * btr_config.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function btr_config_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create article content'.
  $permissions['create article content'] = array(
    'name' => 'create article content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'create artist content'.
  $permissions['create artist content'] = array(
    'name' => 'create artist content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'create video content'.
  $permissions['create video content'] = array(
    'name' => 'create video content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any article content'.
  $permissions['delete any article content'] = array(
    'name' => 'delete any article content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any artist content'.
  $permissions['delete any artist content'] = array(
    'name' => 'delete any artist content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any video content'.
  $permissions['delete any video content'] = array(
    'name' => 'delete any video content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own article content'.
  $permissions['delete own article content'] = array(
    'name' => 'delete own article content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own artist content'.
  $permissions['delete own artist content'] = array(
    'name' => 'delete own artist content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own video content'.
  $permissions['delete own video content'] = array(
    'name' => 'delete own video content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete terms in cities'.
  $permissions['delete terms in cities'] = array(
    'name' => 'delete terms in cities',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in venues'.
  $permissions['delete terms in venues'] = array(
    'name' => 'delete terms in venues',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit any article content'.
  $permissions['edit any article content'] = array(
    'name' => 'edit any article content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any artist content'.
  $permissions['edit any artist content'] = array(
    'name' => 'edit any artist content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any video content'.
  $permissions['edit any video content'] = array(
    'name' => 'edit any video content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit own article content'.
  $permissions['edit own article content'] = array(
    'name' => 'edit own article content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit own artist content'.
  $permissions['edit own artist content'] = array(
    'name' => 'edit own artist content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit own video content'.
  $permissions['edit own video content'] = array(
    'name' => 'edit own video content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit terms in cities'.
  $permissions['edit terms in cities'] = array(
    'name' => 'edit terms in cities',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in venues'.
  $permissions['edit terms in venues'] = array(
    'name' => 'edit terms in venues',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'use text format full_html'.
  $permissions['use text format full_html'] = array(
    'name' => 'use text format full_html',
    'roles' => array(),
    'module' => 'filter',
  );

  return $permissions;
}
