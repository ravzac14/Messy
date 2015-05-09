/* This menu pops up any time you want to quit
 *
 */ 

#include "ConfirmExitMenu.h"
#include "stdafx.h"

ConfirmExitMenu::MenuResult ConfirmExitMenu::show (sf::RenderWindow& window)
{
  currentButton = nullptr;

  static RectangularMenuItem<ConfirmExitMenu::MenuResult> exitButton {sf::Rect<int> {CEM_EXIT_BUTTON_LEFT,CEM_BUTTON_TOP,CEM_BUTTON_WIDTH,CEM_BUTTON_HEIGHT}, EXIT};
  static RectangularMenuItem<ConfirmExitMenu::MenuResult> playButton {sf::Rect<int> {CEM_PLAY_BUTTON_LEFT,CEM_BUTTON_TOP,CEM_BUTTON_WIDTH,CEM_BUTTON_HEIGHT}, PLAY};

  mMenuItems.push_back(exitButton);
  mMenuItems.push_back(playButton);

  updateImage(window);

  return getMenuResponse(window);
}

void ConfirmExitMenu::updateImage(sf::RenderWindow& window) 
{
  const std::string* newImage = nullptr;
  if (currentButton) {
    switch (currentButton->mAction) {
      case EXIT: {
        newImage = &CEM_EXIT;
      } break;
      case PLAY: {
        newImage = &CEM_PLAY;
      } break;
    }
  }
  else {
    newImage = &CEM_BASE;
  }

  sf::Image image;
  if (!image.loadFromFile(*newImage)) return;

  sf::Texture texture;
  sf::Rect<int> empty;
  texture.loadFromImage(image, empty);
  sf::Sprite sprite(texture);
  sprite.setPosition(CEM_LEFT,CEM_TOP);

  window.draw(sprite);
  window.display();
}

ConfirmExitMenu::MenuResult ConfirmExitMenu::handleKey (sf::Keyboard::Key code, sf::RenderWindow& window)
{
  std::list<RectangularMenuItem<ConfirmExitMenu::MenuResult>>::iterator itr;
  switch (code) {
    case sf::Keyboard::Return: {
      if (!currentButton) 
        currentButton = &(*(++mMenuItems.begin())); //ie cancel
      else
        return currentButton->mAction;
    } break;
    case sf::Keyboard::Escape: {
      if (!currentButton) 
        currentButton = &(*(mMenuItems.begin())); //ie quit
      else
        return NOTHING;
    } break;
    case sf::Keyboard::Left: {
      if (!currentButton) 
        currentButton = &(*(++mMenuItems.begin())); //ie cancel
      else {
        switch (currentButton->mAction) {
          case EXIT: {
            return NOTHING; 
          } break;
          case PLAY: {
            currentButton = &(*(mMenuItems.begin())); //ie quit
          } break;
        }
      }
    } break;
    case sf::Keyboard::Right: {
      if (!currentButton) 
        currentButton = &(*(mMenuItems.begin())); //ie quit
      else {
        switch (currentButton->mAction) {
          case EXIT: {
            currentButton = &(*(++mMenuItems.begin())); //ie cancel
          } break;
          case PLAY: {
            return NOTHING;
          } break;
        }
      }
    } break;
  } //switch
  updateImage(window);
  return NOTHING;
}

ConfirmExitMenu::MenuResult ConfirmExitMenu::handleClick (int x, int y)
{
  std::list<RectangularMenuItem<ConfirmExitMenu::MenuResult>>::iterator itr;
  for (itr = mMenuItems.begin(); itr != mMenuItems.end(); itr++) 
  {
    sf::Rect<int> menuItemRect = itr->mRect;
    if (menuItemRect.contains(x,y))
      return itr->mAction;
  }
  return NOTHING;
}

void ConfirmExitMenu::handleHover (int x, int y, sf::RenderWindow& window)
{
  std::list<RectangularMenuItem<ConfirmExitMenu::MenuResult>>::iterator itr;
  if (!CEM_MOUSE_CONTAINED) {
    for (itr = mMenuItems.begin(); itr != mMenuItems.end(); itr++)
    {
      sf::Rect<int> menuItemRect = itr->mRect;
      if (menuItemRect.contains(x,y)) {
        currentButton = &(*itr);
        CEM_MOUSE_CONTAINED = true;
      }
    }
  }
  else {
    currentButton = nullptr;
    CEM_MOUSE_CONTAINED = false;
  }
  updateImage(window);
}

ConfirmExitMenu::MenuResult ConfirmExitMenu::getMenuResponse (sf::RenderWindow& window)
{
  sf::Event event;
  while (true) {
    //HandleHover
    if (currentButton) 
    {
      if (!currentButton->mRect.contains(sf::Mouse::getPosition(window)))
        handleHover(event.mouseMove.x, event.mouseMove.y, window);
    }
    else if (  (sf::Mouse::getPosition(window).x > CEM_MIN_MOUSE_X_REACT)
            && (sf::Mouse::getPosition(window).x < CEM_MAX_MOUSE_X_REACT)
            && (sf::Mouse::getPosition(window).y > CEM_MIN_MOUSE_Y_REACT)
            && (sf::Mouse::getPosition(window).y < CEM_MAX_MOUSE_Y_REACT))
    {
      handleHover(event.mouseMove.x, event.mouseMove.y, window);
    }

    //handleEvents
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::MouseButtonPressed)
        return handleClick(event.mouseButton.x, event.mouseButton.y);
      if (event.type == sf::Event::KeyPressed) {
        ConfirmExitMenu::MenuResult result = handleKey(event.key.code, window);
        if (result == NOTHING)
          break;
        return result;
      }
      if (event.type == sf::Event::Closed) 
        return HARD_EXIT;
    } //while poll
  } //while true
}
