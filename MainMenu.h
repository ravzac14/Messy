#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "stdafx.h"

class MainMenu
{
  public: 
    enum MenuResult {NOTHING,EXIT,PLAY};

    struct MenuItem {
      public:
        sf::Rect<int> mRect;
        MenuResult mAction;
    };

    MenuResult show(sf::RenderWindow& window);

  private:
    MenuResult getMenuResponse(sf::RenderWindow& window);
    MenuResult handleClick(int x, int y);
    std::list<MenuItem> mMenuItems;
};

#endif
