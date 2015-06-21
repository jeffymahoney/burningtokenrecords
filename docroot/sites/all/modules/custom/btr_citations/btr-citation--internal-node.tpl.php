<?php

/**
 * @file btr-citation--internal-node.tpl.php
 * Template for a single internal node BTR Citation
 * 
 * Available variables:
 * $link
 *  - the citation link
 * $title
 *  - the title of the paper node
 * $created_datetime
 *  - the node creation date formatted for an HTML5 datetime attribute
 * $created_display
 *  - the node creation date formatted for display
 */
?>
<?php print $link; ?>
 <time class="entry-published" pubdate="" datetime="<?php print $created_datetime; ?>"><?php print $created_display; ?></time>
