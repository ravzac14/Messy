#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "stdafx.h"

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
static bool MOUSE_CONTAINED = false;

class MainMenu
{
  public: 
    enum MenuResult {NOTHING,EXIT,HIGHSCORE,PLAY};

    class MenuItem {
      public:
        sf::Rect<int> mRect;
        MenuResult mAction;
        
        MenuItem (sf::Rect<int>& r, MenuResult a);
        MenuItem (sf::Rect<int>&& r, MenuResult a);

        bool operator== (const MenuItem& rhs);
        MenuItem& operator= (const MenuItem& rhs);
        MenuItem& operator= (MenuItem& rhs);
    };

    MenuResult show(sf::RenderWindow& window);

  private:
    MenuResult getMenuResponse(sf::RenderWindow& window);
    MenuResult handleClick(int x, int y);
    MenuResult handleKey(sf::Keyboard::Key code, sf::RenderWindow& window);
    void handleHover(int x, int y, sf::RenderWindow& window);
    std::list<MenuItem> mMenuItems;
    void updateImage(sf::RenderWindow& window);
    MenuItem* currentButton;
};

#endif
