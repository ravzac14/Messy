#ifndef CONFIRM_EXIT_H
#define CONFIRM_EXIT_H

#include "stdafx.h"
#include "RectangularMenuItem.h"

const int CEM_MIN_MOUSE_X_REACT = 270;
const int CEM_MAX_MOUSE_X_REACT = 550;
const int CEM_MIN_MOUSE_Y_REACT = 370;
const int CEM_MAX_MOUSE_Y_REACT = 470;
const std::string CEM_BASE = "assets/280x206-confirm-exit-menu-null.png";
const std::string CEM_EXIT = "assets/280x206-confirm-exit-menu-exit.png";
const std::string CEM_PLAY = "assets/280x206-confirm-exit-menu-play.png";
const float CEM_TOP = 240.0f;
const float CEM_LEFT = 240.0f;
const int CEM_EXIT_BUTTON_LEFT = 38 + CEM_LEFT;
const int CEM_BUTTON_TOP = 138 + CEM_TOP;
const int CEM_PLAY_BUTTON_LEFT = 143 + CEM_LEFT;
const int CEM_BUTTON_HEIGHT = 41;
const int CEM_BUTTON_WIDTH = 88;
static bool CEM_MOUSE_CONTAINED = false;


class ConfirmExitMenu
{
  public:
    enum MenuResult {NOTHING, HARD_EXIT, EXIT, PLAY};
    MenuResult show (sf::RenderWindow& window);

  private:
    std::list<RectangularMenuItem<MenuResult>> mMenuItems;
    RectangularMenuItem<MenuResult>* currentButton;
    
    void updateImage(sf::RenderWindow& window);
    MenuResult handleKey (sf::Keyboard::Key code, sf::RenderWindow& window);
    MenuResult getMenuResponse (sf::RenderWindow& window);
    void handleHover (int x, int y, sf::RenderWindow& window);
    MenuResult handleClick (int x, int y);
};

#endif
