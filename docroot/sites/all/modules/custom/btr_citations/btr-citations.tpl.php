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
<?php if (!empty($citations)): ?>
  <section id="references" class="panel-pane">
    <h1 class="pane-title">References</h1>
    <?php
    foreach ($citations as $citation_title => $citation_set):
      switch ($citation_title):
        case 'External':
          ?><h2>External links</h2><?php
          break;
        case 'Other':
          ?><h2>General Pages</h2><?php
          break;
        default:
          ?><h2><?php print $citation_title ?>s</h2><?php
          break;
      endswitch; ?>
      <ul>
        <?php foreach ($citation_set as $citation): ?>
          <li>
            <?php print $citation; ?>
          </li>
        <?php endforeach; ?>
      </ul>
    <?php endforeach; ?>
  </section>
<?php endif; ?>
