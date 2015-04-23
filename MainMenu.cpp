/* Has the definitions for Main menus
 *
 * @author Zack Raver
 * @date 4/20/15
 */

#include "MainMenu.h"

const int MIN_MOUSE_X_REACT = 205; //As in, only if the mouse is moving around in less than this, will we handle the movment
const int MAX_MOUSE_Y_REACT = 435; //Same ^ but more than
const std::string MENU_EXIT = "assets/920x680-mainmenu-exit.png" ;
const std::string MENU_PLAY = "assets/920x680-mainmenu-play.png" ;
const std::string MENU_HS = "assets/920x680-mainmenu-hs.png" ;
const std::string MENU_BASE = "assets/920x680-mainmenu-null.png" ;

MainMenu::MenuResult MainMenu::show(sf::RenderWindow& window)
{
  //setup clickable regions
  currentRect = nullptr;

  //play menu item coordinates
  MenuItem playButton;
  playButton.mRect.left = 40;
  playButton.mRect.width = 160;
  playButton.mRect.top = 440;
  playButton.mRect.height = 60;
  playButton.mAction = PLAY;

  MenuItem hsButton;
  hsButton.mRect.left = 40;
  hsButton.mRect.top = 505;
  hsButton.mRect.width = 160;
  hsButton.mRect.height = 60;
  hsButton.mAction = HIGHSCORE;

  //Exit menu item
  MenuItem exitButton;
  exitButton.mRect.left = 40;
  exitButton.mRect.width = 160;
  exitButton.mRect.top = 570;
  exitButton.mRect.height = 60;
  exitButton.mAction = EXIT;

  mMenuItems.push_back(playButton);
  mMenuItems.push_back(hsButton);
  mMenuItems.push_back(exitButton);
 
  //Set the image
  updateImage(MENU_BASE,window);
  
  return getMenuResponse(window);
}

void MainMenu::updateImage(const std::string& newImage, sf::RenderWindow& window)
{
  //load default menu imag from file
  sf::Image image;
  if (!image.loadFromFile(newImage)) { return; } // Problem loading image
  
  sf::Texture texture;
  sf::Rect<int> empty;
  texture.loadFromImage(image, empty);
  sf::Sprite sprite(texture);
  
  currentImage = newImage;
  window.draw(sprite);
  window.display();
}

MainMenu::MenuResult MainMenu::handleHover(int x, int y, sf::RenderWindow& window)
{
  std::list<MainMenu::MenuItem>::iterator itr;
  bool wasContained = false;
  for (itr = mMenuItems.begin(); itr != mMenuItems.end(); itr++)
  {
    sf::Rect<int> menuItemRect = (*itr).mRect;
    if (menuItemRect.contains(x,y))
    {
      currentRect = &(*itr).mRect;
      wasContained = true;
      
      switch ((*itr).mAction) {
        case EXIT: {
          //if (currentImage.compare(MENU_EXIT))
            updateImage(MENU_EXIT, window);
        } break;
        case PLAY: {
          //if (currentImage.compare(MENU_PLAY))
            updateImage(MENU_PLAY, window);
        } break;
        case HIGHSCORE: {
          //if (currentImage.compare(MENU_HS))
            updateImage(MENU_HS, window);
        } break;
      }
    }
  } 
  if (!wasContained)
    currentRect = nullptr;
    //TODO figure out how to get back to un highlighted: updateImage(MENU_BASE, window);
  
  return NOTHING; //This doesnt have to do anything, just update the image  
}

MainMenu::MenuResult MainMenu::handleClick(int x, int y)
{
  std::list<MainMenu::MenuItem>::iterator itr;

  for (itr = mMenuItems.begin(); itr != mMenuItems.end(); itr++)
  {
    sf::Rect<int> menuItemRect = (*itr).mRect;
    if (menuItemRect.contains(x,y))
      return (*itr).mAction;
  }
  return NOTHING;
}

MainMenu::MenuResult MainMenu::handleKey(sf::Keyboard::Key code, sf::RenderWindow& window)
{
  switch (code) {
    case sf::Keyboard::Enter: {
      
    } break;
    case sf::Keyboard::Escape: {
      //TODO:return CONFIRM_EXIT
    } break;
    case sf::Keyboard::Up: {
      //TODO:decrement where in the menuItems list currentRect is, updateImage
    } break;
    case sf::Keyboard::Down: {
      //TODO:increment where in the menuItems list currentRect is, updateImage

    } break;
  }
  return NOTHING;
}

MainMenu::MenuResult MainMenu::getMenuResponse(sf::RenderWindow& window)
{
  sf::Event menuEvent;

  while(true)
  {
    if (currentRect) //ie If not nullptr
    {
      if (!currentRect->contains(sf::Mouse::getPosition(window)))
        handleHover(menuEvent.mouseMove.x, menuEvent.mouseMove.y, window);
    } 
    else if (  (sf::Mouse::getPosition(window).x < MIN_MOUSE_X_REACT)
            && (sf::Mouse::getPosition(window).y > MAX_MOUSE_Y_REACT))
    {
      handleHover(menuEvent.mouseMove.x, menuEvent.mouseMove.y, window);
    }
    while (window.pollEvent(menuEvent))
    {
      if (menuEvent.type == sf::Event::MouseButtonPressed)
        return handleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
      if (menuEvent.type == sf::Event::KeyPressed)
        return handleKey(menuEvent.Keyboard::Key.code, window);
      if (menuEvent.type == sf::Event::Closed)
        return EXIT;
    }
  }
}
