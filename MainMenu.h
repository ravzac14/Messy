#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "stdafx.h"
#include "RectangularMenuItem.h"

const int MM_MIN_MOUSE_X_REACT = 205; //As in, only if the mouse is moving around in less than this, will we handle the movment
const int MM_MAX_MOUSE_Y_REACT = 435; //Same ^ but more than
const std::string MM_EXIT = "assets/920x680-mainmenu-exit.png" ;
const std::string MM_PLAY = "assets/920x680-mainmenu-play.png" ;
const std::string MM_HS = "assets/920x680-mainmenu-hs.png" ;
const std::string MM_BASE = "assets/920x680-mainmenu-null.png" ;
const int MM_PLAY_BUTTON_TOP = 440;
const int MM_HS_BUTTON_TOP = 505;
const int MM_EXIT_BUTTON_TOP = 570;
const int MM_BUTTON_LEFT = 40;
const int MM_BUTTON_HEIGHT = 60;
const int MM_BUTTON_WIDTH = 160;
static bool MM_MOUSE_CONTAINED = false;

class MainMenu
{
  public: 
    enum MenuResult {NOTHING,EXIT,HIGHSCORE,PLAY};
    MenuResult show(sf::RenderWindow& window);

  private:
    MenuResult getMenuResponse(sf::RenderWindow& window);
    MenuResult handleClick(int x, int y);
    MenuResult handleKey(sf::Keyboard::Key code, sf::RenderWindow& window);
    void handleHover(int x, int y, sf::RenderWindow& window);
    std::list<RectangularMenuItem<MenuResult>> mMenuItems;
    void updateImage(sf::RenderWindow& window);
    RectangularMenuItem<MenuResult>* currentButton;
};

#endif
