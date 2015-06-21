<?php
/**
 * @file btr-citations.tpl.php
 * Template for BTR Citations
 * 
 * Available variables:
 * $field
 *  - contains the full render array
 * $citations
 *  - array of rendered citations
 */
?>
<section id="references" class="panel-pane">
  <h1 class="pane-title">References</h1>
  <?php if (!empty($citations)): ?>
    <?php
    foreach ($citations as $citation_title => $citation_set):
      switch ($citation_set):
        case 'Paper':
          ?>
          <h2 class="pane-subtitle">Paper Citations</h2>
          <ol class="hfeed">
            <?php foreach ($citation_set as $citation): ?>
              <li class="hentry paper">
                <?php print $citation; ?>
              </li>
            <?php endforeach; ?>
          </ol>    

          <?php
          break;
        default:
          ?>
          <h2 class="pane-subtitle"><?php print $citation_title ?> Citations</h2>
          <ol class="hfeed">
            <?php foreach ($citation_set as $citation): ?>
              <li class="hentry news">
                <?php print $citation; ?>
              </li>
            <?php endforeach; ?>
          </ol>    
          <?php
          break;
      endswitch;
    endforeach;
    ?>
  <?php else: ?>
	<p>No Available References</p>
  <?php endif; ?>
</section>