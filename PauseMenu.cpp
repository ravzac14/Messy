//Pause screen duder

#include "stdafx.h"
#include "PauseMenu.h"

PauseMenu::MenuResult PauseMenu::show (sf::RenderWindow& window)
{
  sf::Image image;
  if (!image.loadFromFile("assets/360x265-ingame-menu-pause.png")) return NOTHING;

  sf::Texture texture;
  sf::Rect<int> area;
  texture.loadFromImage(image, area);
  sf::Sprite sprite(texture);
  
  sprite.setPosition(200.0f,200.0f);
  window.draw(sprite);
  window.display();

  return PauseMenu::getMenuResponse(window);
} 

PauseMenu::MenuResult PauseMenu::handleKey(sf::Keyboard::Key code)
{
  MenuResult result = NOTHING;
  switch (code) {
    case sf::Keyboard::Return: {
      result = PLAY;
    } break;
    case sf::Keyboard::Escape: {  
      result = EXIT;
    } break;
  }
  return result;
}

PauseMenu::MenuResult PauseMenu::getMenuResponse(sf::RenderWindow& window)
{
  sf::Event event;
  
  while (true) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        return EXIT;
      if (event.type == sf::Event::KeyPressed) {
        PauseMenu::MenuResult result = handleKey(event.key.code);
        if (result == NOTHING)
          break; 
        return result;
      }
    }
  }

}
