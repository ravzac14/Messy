/* Has the definitions for Main menus
 *
 * @author Zack Raver
 * @date 4/20/15
 */

#include "MainMenu.h"

MainMenu::MenuItem::MenuItem (sf::Rect<int>& r, MainMenu::MenuResult a) : mRect {r}, mAction {a} 
{ }

MainMenu::MenuItem::MenuItem (sf::Rect<int>&& r, MainMenu::MenuResult a) : mRect {std::move(r)}, mAction {a} 
{ }

bool MainMenu::MenuItem::operator== (const MainMenu::MenuItem& rhs) 
{
  return (this->mAction == rhs.mAction);
}

MainMenu::MenuItem& MainMenu::MenuItem::operator= (const MainMenu::MenuItem& rhs) 
{
  MenuItem copy = rhs;
  std::swap(*this,copy);
  return *this;
}

MainMenu::MenuItem& MainMenu::MenuItem::operator= (MainMenu::MenuItem& rhs) 
{
  std::swap(mAction,rhs.mAction);
  std::swap(mRect,rhs.mRect);
  return *this;
}

MainMenu::MenuResult MainMenu::show(sf::RenderWindow& window)
{
  currentButton = nullptr;

  static MainMenu::MenuItem playButton {sf::Rect<int> {BUTTON_LEFT_EDGE,PLAY_TOP,BUTTON_WIDTH,BUTTON_HEIGHT}, PLAY};
  static MainMenu::MenuItem hsButton {sf::Rect<int> {BUTTON_LEFT_EDGE,HS_TOP,BUTTON_WIDTH,BUTTON_HEIGHT}, HIGHSCORE};
  //hsButton.mRect.left = BUTTON_LEFT_EDGE;
  //hsButton.mRect.top = HS_TOP;
  //hsButton.mRect.width = BUTTON_WIDTH;
  //hsButton.mRect.height = BUTTON_HEIGHT;
  //hsButton.mAction = HIGHSCORE; //TODO this is nothing for now, eventually it should be HIGHSCORE

  static MainMenu::MenuItem exitButton {sf::Rect<int> {BUTTON_LEFT_EDGE,EXIT_TOP,BUTTON_WIDTH,BUTTON_HEIGHT}, EXIT};

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
  if (currentButton) //if not a nullptr
  {
    switch (currentButton->mAction) {
      case EXIT: {
        newImage = &MENU_EXIT;
      } break;
      case PLAY: {
        newImage = &MENU_PLAY;
      } break;
      case HIGHSCORE: {
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

void MainMenu::handleHover(int x, int y, sf::RenderWindow& window)
{
  std::list<MainMenu::MenuItem>::iterator itr;
  
  if (!MOUSE_CONTAINED) {
    for (itr = mMenuItems.begin(); itr != mMenuItems.end(); itr++)
    {
      sf::Rect<int> menuItemRect = (*itr).mRect;
      if (menuItemRect.contains(x,y)) {
        currentButton = &(*itr);
        MOUSE_CONTAINED = true;
      }
    } 
  } else {
    currentButton = nullptr;
    MOUSE_CONTAINED = false;
  } 
  
  updateImage(window); 
}

MainMenu::MenuResult MainMenu::handleClick(int x, int y)
{

  std::list<MainMenu::MenuItem>::iterator itr;

  for (itr = mMenuItems.begin(); itr != mMenuItems.end(); itr++)
  {
    sf::Rect<int> menuItemRect = itr->mRect;
    if (menuItemRect.contains(x,y))
      return itr->mAction;
  }
  return NOTHING;
}

MainMenu::MenuResult MainMenu::handleKey(sf::Keyboard::Key code, sf::RenderWindow& window)
{
    std::list<MainMenu::MenuItem>::iterator itr;

    switch (code) {
    case sf::Keyboard::Return: {  //KEY - ENTER
      if (!currentButton) {                      
        currentButton = &(*mMenuItems.begin());   
      }
      else 
        return currentButton->mAction;    
    } break;
    case sf::Keyboard::Escape: {  //KEY - ESCAPE
      //TODO:return CONFIRM_EXIT
    } break;
    case sf::Keyboard::Up: {  //KEY - UP
      if (!currentButton) {                     
        currentButton = &(*mMenuItems.begin());   
      }
      else {
        switch (currentButton->mAction) {
          case PLAY: {
            return NOTHING;
          } break;
          case HIGHSCORE: {
            currentButton = &(*mMenuItems.begin());
          } break;
          case EXIT: {
            itr = mMenuItems.begin(); //This is play
            itr++; //Now its HS
            currentButton = &(*itr);
          } break; 
        }
      }
    } break;
    case sf::Keyboard::Down: {  //KEY - DOWN
      if (!currentButton)  {                  
        currentButton = &(*(--mMenuItems.end()));  
      }
      else {
        switch (currentButton->mAction) {
          case PLAY: {
            itr = --mMenuItems.end(); //This is exit
            itr--; //Now its HS
            currentButton = &(*itr); 
          } break;
          case HIGHSCORE: {
            currentButton = &(*(--mMenuItems.end()));
          } break;
          case EXIT: {
            return NOTHING; 
          } break; 
        }
      } 
    } break;
  } //switch

  //Will only get here if you pressed up or down
  updateImage(window); 
  return NOTHING;
}

MainMenu::MenuResult MainMenu::getMenuResponse(sf::RenderWindow& window)
{
  sf::Event menuEvent;

  while(true)
  {
    //Check mouse positioning for menu highlighting  
    if (currentButton)
    {
      if (!currentButton->mRect.contains(sf::Mouse::getPosition(window)))
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
      if (menuEvent.type == sf::Event::KeyPressed) {
        MainMenu::MenuResult result = handleKey(menuEvent.key.code, window);
        if (result == NOTHING)
          break;
        return result;
      }
      if (menuEvent.type == sf::Event::Closed)
        return EXIT;
    }
  }
}
