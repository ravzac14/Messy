/* Logic on how to show a splash screen
 * @author Zack Raver
 * @date 4/20/15
 */

#include "stdafx.h"
#include "SplashScreen.h"

void SplashScreen::show(sf::RenderWindow& window)
{
  sf::Image image;
  if (!image.loadFromFile("assets/butt640x640.png")) { return; } //Problem loading the image
  
  sf::Texture texture;
  sf::Rect<int> area; //Empty means the whole image
  texture.loadFromImage(image, area);
  sf::Sprite sprite(texture);

  window.draw(sprite);
  window.display();

  sf::Event event;
  while (true)
  {
    while (window.pollEvent(event))
    {
      if (  event.type == sf::Event::KeyPressed 
         || event.type == sf::Event::MouseButtonPressed
         || event.type == sf::Event::Closed)
      {
        return;
      }
    }
  }
}
