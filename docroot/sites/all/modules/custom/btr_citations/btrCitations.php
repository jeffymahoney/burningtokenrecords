<?php

/**
 * A class to handle citations 
 */
class btrCitations {

  private $citations = array();

  public function __construct($citations = array()) {
    $this->citations = $citations;
  }

  /**
   * Return themed citations
   * @return array of rendered citations
   */
  public function theme() {
    $citations = array();
    foreach ($this->citations as $tmp_citation) {
      $tmp_citation = $this->theme_single($tmp_citation);
      $title = $tmp_citation['title'];
      $markup = $tmp_citation['markup'];
      $citations[$title][] = $markup;
    }
    if (isset($citations['Paper'])) {
      $temppp = $citations['Paper'];
      unset($citations['Paper']);
      $citations['Paper'] = $temppp;
    }
    if (isset($citations['Other'])) {
      $temppp = $citations['Other'];
      unset($citations['Other']);
      $citations['Other'] = $temppp;
    }
    if (isset($citations['External'])) {
      $temppp = $citations['External'];
      unset($citations['External']);
      $citations['External'] = $temppp;
    }
    return $citations;
  }

  /**
   * Themes a single BTR Citation
   * @param array $citation
   *   A BTR Citation array
   *  @see btr_citations_field_widget_form().
   * @return themed output
   */
  public function theme_single($citation) {
    $output = array();
    if (isset($citation['external_uri'])) {
      $output['title'] = 'External';
      $output['markup'] = $this->theme_external($citation);
    } elseif (isset($citation['internal_uri'])) {
      $type = $this->internal_type($citation);
      $types = node_type_get_types();
      if (array_key_exists($type, $types)) {
        $title = $types[$type]->name;
      }
      else {
        $title = 'Other';
      }

      $output['title'] = $title;
      $output['markup'] = $this->theme_internal($citation);
    }
    return $output;
  }

  /**
   * Helper function for theme_single().
   */
  protected function theme_external($citation) {
    try {
      $link = $citation['external_uri'];
    } catch (Exception $exc) {
      watchdog('btrCitations', $exc->getTraceAsString());
      return '';
    }
    $link_text = '';
    if (!empty($citation['link_rel'])) {
      $link_text = $citation['link_rel'];
    } elseif (!empty($citation['link_text'])) {
      $link_text = $citation['link_text'];
    }
    $output = theme('btr_citation_external', array('link' => $link, 'link_text' => $link_text));
    return $output;
  }

  /**
   * Helper function for theme_single().
   */
  protected function theme_internal($citation) {
    if ($citation['nid'] && !$this->nodeExists($citation['nid'])) {
      return '';
    }
    if ($citation['link_attributes']) {
      if (!is_array($citation['link_attributes'])) {
        $citation['link_attributes'] = unserialize($citation['link_attributes']);
      }
    }else {
      $citation['link_attributes'] = array();
    }

    if (!empty($citation['node_type'])) {
      $output = theme('btr_citation_internal_node', array('nid' => $citation['nid'], 'link_attributes' => $citation['link_attributes']));
    } else {
      try {
        $link = ltrim($citation['internal_uri'], '/');
      } catch (Exception $exc) {
        watchdog('btrCitations', $exc->getTraceAsString());
        return '';
      }
      $link_text = '';
      if (!empty($citation['link_rel'])) {
        $link_text = $citation['link_rel'];
      } elseif (!empty($citation['link_text'])) {
        $link_text = $citation['link_text'];
      }
      $output = theme('btr_citation_internal_misc', array('link' => $link, 'link_text' => $link_text, 'link_attributes' => $citation['link_attributes']));
    }
    return $output;
  }

  /**
   * Get the type of link from a citation
   * @param array $citation
   *   A BTR Citation array
   *  @see btr_citations_field_widget_form().
   * @return string
   *  the type of link (node type or misc)
   */
  protected function internal_type($citation) {
    if (isset($citation['node_type'])) {
      return $citation['node_type'];
    }
    return 'misc';
  }

  /**
   * Checks if a node exists based on a node ID.
   *
   * @param $nid A node ID
   * @return bool True if a node exists, FALSE otherwise.
   */
  protected function nodeExists($nid) {
    if (!ctype_digit((string) $nid)) {
      return FALSE;
    }
    $result = db_select('node', 'nid')
      ->fields('nid', array('nid'))
      ->condition('nid', $nid)
      ->range(0, 1)
      ->execute()
      ->rowCount();
    if ($result) {
      $exists = TRUE;
    } else {
      $exists = FALSE;
    }
    return $exists;
  }

}
