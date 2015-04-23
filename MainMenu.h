#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "stdafx.h"

class MainMenu
{
  public: 
    enum MenuResult {NOTHING,EXIT,HIGHSCORE,PLAY};

    struct MenuItem {
      public:
        sf::Rect<int> mRect;
        MenuResult mAction;
    };

    MenuResult show(sf::RenderWindow& window);

  private:
    MenuResult getMenuResponse(sf::RenderWindow& window);
    MenuResult handleClick(int x, int y);
    MenuResult handlekey(sf::Keyboard::Key code, sf::RenderWindow& window);
    MenuResult handleHover(int x, int y, sf::RenderWindow& window);
    std::list<MenuItem> mMenuItems;
    void updateImage(const std::string& s, sf::RenderWindow& window);
    std::string currentImage;
    sf::Rect<int>* currentRect;
};

#endif
