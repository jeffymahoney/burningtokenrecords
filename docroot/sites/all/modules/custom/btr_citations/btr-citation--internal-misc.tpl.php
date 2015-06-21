<?php

/**
 * @file btr-citation--internal-misc.tpl.php
 * Template for a single internal miscellaneous (non-node) BTR Citation
 * 
 * Available variables:
 * $link
 *  - The citation link
 * $link_text
 *  - The text to display for the link
 * $link_attributes
 */
?>
<?php print l($link_text, $link, $link_attributes); ?>