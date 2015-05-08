#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

class PauseMenu
{
  public:
    enum MenuResult {NOTHING, EXIT, PLAY};
    
    MenuResult show(sf::RenderWindow& window);
  
  private:
    MenuResult handleKey (sf::Keyboard::Key code);
    MenuResult getMenuResponse(sf::RenderWindow& window);
};

#endif
