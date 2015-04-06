#!/bin/sh
export BEHAT_PARAMS='{"extensions":{"Behat\\MinkExtension":{"base_url":"http://devlocal.burningtokenrecords.com"},"Drupal\\DrupalExtension":{"drupal":{"drupal_root":"/Applications/MAMP/htdocs/burningtokenrecords/docroot"},"drush":{"alias":"devlocal.burningtokenrecords.com"},"subcontexts":{"paths":["/Applications/MAMP/htdocs/burningtokenrecords/docroot/sites/all"]}}}}'
echo "Behat environment variables set. Remember to start Phantom."
