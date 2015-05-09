/* This menu pops up any time you want to quit
 *
 */ 

#include "ConfirmExitMenu.h"

ConfirmExitMenu::MenuResult ConfirmExitMenu::show (sf::RenderWindow& window)
{

}

ConfirmExitMenu::MenuResult ConfirmExitMenu::handleKey (sf::Keyboard::Key code)
{
  switch (code) {

  } //switch
}

ConfirmExitMenu::MenuResult ConfirmExitMenu::handleClick (int x, int y)
{

}

void ConfirmExitMenu::handleHover (int x, int y, sf::RenderWindow& window)
{

}

ConfirmExitMenu::MenuResult ConfirmExitMenu::getMenuResponse (sf::RenderWindow& window)
{
  sf::Event event;
  while (true) {
    //HandleHover

    //handleEvents
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::MouseButtonPressed)
        return handleClick(event.mouseButton.x, event.mouseButton.y);
      if (event.type == sf::Event::KeyPressed) {
        ConfirmExitMenu::MenuResult result = handleKey(event.key.code, sf::RenderWindow& window);
        if (result == NOTHING)
          break;
        return result;
      }
      if (event.type == sf::Event::Closed) 
        return HARD_EXIT;
    } //while poll
  } //while true
}
