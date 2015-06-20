<div id="page">
  <header class="header" id="header" role="banner">
    <?php if ($is_front): ?>
      <img src="<?php print $logo; ?>" alt="<?php print $site_name; ?>" class="header__logo-image"/>
    <?php else: ?>
      <a href="<?php print $front_page; ?>" title="<?php print $site_name; ?>" rel="home" class="header__logo" id="logo"><img src="<?php print $logo; ?>" alt="<?php print $site_name; ?>" class="header__logo-image"/></a>
    <?php endif; ?>
  </header>
  <div id="main-content" role="main">
    <?php print render($title_prefix); ?>
    <?php print $messages; ?>
    <?php print render($tabs); ?>
    <?php print render($page['help']); ?>
    <?php if ($action_links): ?>
      <ul class="action-links"><?php print render($action_links); ?></ul>
    <?php endif; ?>
    <?php print render($page['content']); ?>
  </div>
</div>
