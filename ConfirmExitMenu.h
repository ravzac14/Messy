#ifndef CONFIRM_EXIT_H
#define CONFIRM_EXIT_H

#include "RectangularMenuItem.h"

//const int CEM_MIN_MOUSE_REACT = ;
//const int CEM_MAX_MOUSE_REACT = ;
const std::string EXIT_BASE = "assets/280x206-confirm-exit-menu-null.png";
const std::string EXIT_EXIT = "assets/280x206-confirm-exit-menu-exit.png";
const std::string EXIT_PLAY = "assets/280x206-confirm-exit-menu-play.png";
const float CEM_TOP = 240.0f;
const float CEM_LEFT = 240.0f;
const float CEM_EXIT_BUTTON_LEFT = 38.0f;
const float CEM_BUTTON_TOP = 138.0f;
const float CEM_PLAY_BUTTON_LEFT = 143.0f;
static bool CEM_MOUSE_CONTAINED = false;

class ConfirmExitMenu
{
  public:
    enum MenuResult {NOTHING, HARD_EXIT, EXIT, CONTINUE};
    MenuResult show (sf::RenderWindow& window);

  private:
    std::list<RectangularMenuItem<MenuResult>> mMenuItems;
    RectangularMenuItem<MenuResult>* currentButton;
    
    void updateImage(sf::RenderWindow& window);
    MenuResult handleKey (sf::Keyboard::Key code);
    MenuResult getMenuResponse (sf::RenderWindow& window);
    void handleHover (int x, int y, sf::RenderWindow& window);
    MenuResult handleClick (int x, int y);
};

#endif
