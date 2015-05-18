/* Load screen, with controls
 *
 */

#include "stdafx.h"
#include "LoadScreen.h"

void LoadScreen::show (sf::RenderWindow& window)
{
  sf::Image image;
  if (!image.loadFromFile("assets/920x680-controls.png")) return;

  sf::Texture texture;
  sf::Rect<int> empty;
  texture.loadFromImage(image,empty);
  sf::Sprite sprite(texture);

  window.draw(sprite);
  window.display();

  sf::Event event;
  while (true) {
    while (window.pollEvent(event)) {
      if (  event.type == sf::Event::KeyPressed 
         || event.type == sf::Event::MouseButtonPressed
         || event.type == sf::Event::Closed)
        return;
    }
  }
}
