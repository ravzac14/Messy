/* Has the definitions for Main menus
 *
 * @author Zack Raver
 * @date 4/20/15
 */

#include "MainMenu.h"

MainMenu::MenuResult MainMenu::show(sf::RenderWindow& window)
{
  //setup clickable regions

  //play menu item coordinates
  MenuItem playButton;
  playButton.mRect.left = 5;
  playButton.mRect.width = 200;
  playButton.mRect.top = 325;
  playButton.mRect.height = 150;
  playButton.mAction = PLAY;

  //Exit menu item
  MenuItem exitButton;
  exitButton.mRect.left = 5;
  exitButton.mRect.width = 200;
  exitButton.mRect.top = 480;
  exitButton.mRect.height = 150;
  exitButton.mAction = EXIT;

  mMenuItems.push_back(playButton);
  mMenuItems.push_back(exitButton);
 
  //load menu imag from file
  sf::Image image;
  if (!image.loadFromFile("assets/680x680-mainmenu-null.png")) { return EXIT; } // Problem loading image
  
  sf::Texture texture;
  sf::Rect<int> empty;
  texture.loadFromImage(image, empty);
  sf::Sprite sprite(texture);

  window.draw(sprite);
  window.display();

  return getMenuResponse(window);
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

MainMenu::MenuResult MainMenu::getMenuResponse(sf::RenderWindow& window)
{
  sf::Event menuEvent;

  while(true)
  {
    while (window.pollEvent(menuEvent))
    {
      if (menuEvent.type == sf::Event::MouseButtonPressed)
        return handleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
      if (menuEvent.type == sf::Event::Closed)
        return EXIT;
    }
  }
}
