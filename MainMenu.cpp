/* Has the definitions for Main menus
 *
 * @author Zack Raver
 * @date 4/20/15
 */

#include "MainMenu.h"
#include "RectangularMenuItem.h"

MainMenu::MenuResult MainMenu::show(sf::RenderWindow& window)
{
  currentButton = nullptr;

  static RectangularMenuItem<MainMenu::MenuResult> playButton {sf::Rect<int> {MM_BUTTON_LEFT,MM_PLAY_BUTTON_TOP,MM_BUTTON_WIDTH,MM_BUTTON_HEIGHT}, PLAY};
  static RectangularMenuItem<MainMenu::MenuResult> hsButton {sf::Rect<int> {MM_BUTTON_LEFT,MM_HS_BUTTON_TOP,MM_BUTTON_WIDTH,MM_BUTTON_HEIGHT}, HIGHSCORE};
  static RectangularMenuItem<MainMenu::MenuResult> exitButton {sf::Rect<int> {MM_BUTTON_LEFT,MM_EXIT_BUTTON_TOP,MM_BUTTON_WIDTH,MM_BUTTON_HEIGHT}, EXIT};

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
        newImage = &MM_EXIT;
      } break;
      case PLAY: {
        newImage = &MM_PLAY;
      } break;
      case HIGHSCORE: {
        newImage = &MM_HS;
      } break;
    } 
  }
  else {  
    newImage = &MM_BASE;
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
  std::list<RectangularMenuItem<MainMenu::MenuResult>>::iterator itr;
  
  if (!MM_MOUSE_CONTAINED) {
    for (itr = mMenuItems.begin(); itr != mMenuItems.end(); itr++)
    {
      sf::Rect<int> menuItemRect = (*itr).mRect;
      if (menuItemRect.contains(x,y)) {
        currentButton = &(*itr);
        MM_MOUSE_CONTAINED = true;
      }
    } 
  } else {
    currentButton = nullptr;
    MM_MOUSE_CONTAINED = false;
  } 
  
  updateImage(window); 
}

MainMenu::MenuResult MainMenu::handleClick(int x, int y)
{

  std::list<RectangularMenuItem<MainMenu::MenuResult>>::iterator itr;

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
    std::list<RectangularMenuItem<MainMenu::MenuResult>>::iterator itr;

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
    else if (  (sf::Mouse::getPosition(window).x < MM_MIN_MOUSE_X_REACT)
            && (sf::Mouse::getPosition(window).y > MM_MAX_MOUSE_Y_REACT))
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
