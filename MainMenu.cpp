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
const int PLAY_TOP = 440;
const int HS_TOP = 505;
const int EXIT_TOP = 570;
const int BUTTON_LEFT_EDGE = 40;
const int BUTTON_HEIGHT = 60;
const int BUTTON_WIDTH = 160;

MainMenu::MenuResult MainMenu::show(sf::RenderWindow& window)
{
  //setup clickable regions
  currentRect = nullptr;

  //play menu item coordinates
  MenuItem playButton;
  playButton.mRect.left = BUTTON_LEFT_EDGE;
  playButton.mRect.width = BUTTON_WIDTH;
  playButton.mRect.top = PLAY_TOP;
  playButton.mRect.height = BUTTON_HEIGHT;
  playButton.mAction = PLAY;
  
  //High score menu item coordinates
  MenuItem hsButton;
  hsButton.mRect.left = BUTTON_LEFT_EDGE;
  hsButton.mRect.top = HS_TOP;
  hsButton.mRect.width = BUTTON_WIDTH;
  hsButton.mRect.height = BUTTON_HEIGHT;
  hsButton.mAction = NOTHING; //TODO this is nothing for now, eventually it should be HIGHSCORE

  //Exit menu item
  MenuItem exitButton;
  exitButton.mRect.left = BUTTON_LEFT_EDGE;
  exitButton.mRect.width = BUTTON_WIDTH;
  exitButton.mRect.top = EXIT_TOP;
  exitButton.mRect.height = BUTTON_HEIGHT;
  exitButton.mAction = EXIT;

  mMenuItems.push_back(playButton);
  mMenuItems.push_back(hsButton);
  mMenuItems.push_back(exitButton);
 
  //Set the image
  updateImage(window);
  
  return getMenuResponse(window);
}

void MainMenu::updateImage(sf::RenderWindow& window)
{
  const std::string* newImage = nullptr;
  if (currentRect) //if not a nullptr
  {
    switch (currentRect->top) {
      case EXIT_TOP: {
        newImage = &MENU_EXIT;
      } break;
      case PLAY_TOP: {
        newImage = &MENU_PLAY;
      } break;
      case HS_TOP: {
        newImage = &MENU_HS;
      } break;
    } 
  }
  else {  
    newImage = &MENU_BASE;
  }
 
  sf::Image image; 
  //load image from file
  if (!image.loadFromFile(*newImage)) { return; } // Problem loading image
  
  sf::Texture texture;
  sf::Rect<int> empty; // Initializes the image to the whole window
  texture.loadFromImage(image, empty);
  sf::Sprite sprite(texture);
  
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
      updateImage(window); 
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

//TODO: write some utility functions rect* to action, rect* to menuItem, etc

MainMenu::MenuResult MainMenu::handleKey(sf::Keyboard::Key code, sf::RenderWindow& window)
{
    std::list<MainMenu::MenuItem>::iterator itr;

    switch (code) {
    case sf::Keyboard::Enter: {  //KEY - ENTER
      if (!currentRect)                      // if its nullptr (nothing is highlighted)
        currentRect = mMenuItems.begin().mRect;    // Highlight the first item in the menu
      else 
        return currentRect->mAction;         //otherwise select the current action
    } break;
    case sf::Keyboard::Escape: {  //KEY - ESCAPE
      //TODO:return CONFIRM_EXIT
    } break;
    case sf::Keyboard::Up: {  //KEY - UP
      if (!currentRect)                      // if its nullptr (nothing is highlighted)
        itr = mMenuItems.begin(); 
        currentRect = &(*itr).mRect;    // Highlight the first item in the menu
      else {
        switch (currentRect->top) {
          case PLAY_TOP: {
            return NOTHING;
          } break;
          case HS_TOP: {
            itr = mMenuItems.begin(); //This is play
            currentRect = &(itr*).mRect;
          } break;
          case EXIT_TOP: {
            itr = mMenuItems.begin(); //This is play
            itr++; //Now its HS
            currentRect = &(itr*).mRect;
          } break; 
        }
      }
    } break;
    case sf::Keyboard::Down: {  //KEY - DOWN
      if (!currentRect)                      // if its nullptr (nothing is highlighted)
        itr = mMenuItems.end(); 
        currentRect = &(*itr).mRect;    // Highlight the last item in the menu
      else {
        switch (currentRect->top) {
          case PLAY_TOP: {
            itr = mMenuItems.end(); //This is exit
            itr--; //Now its HS
            currentRect = &(itr*).mRect; 
          } break;
          case HS_TOP: {
            itr = mMenuItems.end(); //This is play
            currentRect = &(itr*).mRect;
          } break;
          case EXIT_TOP: {
            return NOTHING; 
          } break; 
        }
      }
      
    } break;
  }

  updateImage(window) //will only get here if you pressed up or down
  return NOTHING;
}

MainMenu::MenuResult MainMenu::getMenuResponse(sf::RenderWindow& window)
{
  sf::Event menuEvent;

  while(true)
  {
    //Check mouse positioning for menu highlighting  
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

    //Handle events
    while (window.pollEvent(menuEvent))
    {
      if (menuEvent.type == sf::Event::MouseButtonPressed)
        return handleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
      if (menuEvent.type == sf::Event::KeyPressed)
        return handleKey(menuEvent.key.code, window);
      if (menuEvent.type == sf::Event::Closed)
        return EXIT;
    }
  }
}
