Feature: Anonymous Users
  To make sure the majority of users have a good experience
  As an anonymous user
  I should be able to browse around and use particular features

  Background:
    Given I am on the homepage

  @javascript
  Scenario: Various features are working
    Then I should not see text matching "No front page content has been created yet."
