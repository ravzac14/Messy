#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include "stdafx.h"

const std::string PM_BASE = "assets/360x265-ingame-menu-pause.png";
const float PM_LEFT = 200.0f;
const float PM_TOP = 200.0f;

class PauseMenu
{
  public:
    enum MenuResult {NOTHING, HARD_EXIT, EXIT, PLAY};
    
    MenuResult show(sf::RenderWindow& window);
  
  private:
    MenuResult handleKey (sf::Keyboard::Key code);
    MenuResult getMenuResponse(sf::RenderWindow& window);
};

#endif
