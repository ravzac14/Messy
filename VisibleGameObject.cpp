/* Visible sprite base-class
 */

#include "stdafx.h"
#include "VisibleGameObject.h"

VisibleGameObject::VisibleGameObject () : mIsLoaded {false}
{ }

VisibleGameObject::~VisibleGameObject ()
{ }

void VisibleGameObject::load (std::string filename)
{
  if (mIsInitialized) {
    if (mImage.loadFromFile(filename) == false) {
      mFileName = "";
      mIsLoaded = false;
    } else {
      mFileName = filename;
      mTexture.loadFromImage(mImage, sf::Rect<int> {});
      mSprite.setTexture(mTexture);
      mIsLoaded = true;
    }
  } else {
    initializeActor();
    load(filename);
  }
}

void VisibleGameObject::update ()
{ }

sf::Vector2f VisibleGameObject::getPosition () const
{
  if (mIsLoaded)
    return mSprite.getPosition();
  return sf::Vector2f();
}

bool VisibleGameObject::isLoaded() const
{
  return mIsLoaded;
}

bool VisibleGameObject::isInitialized() const
{
  return mIsInitialized;
}

void VisibleGameObject::setInitialized(bool b)
{
  mIsInitialized = b;
}

sf::Sprite VisibleGameObject::getSprite ()
{
  return mSprite;
}

void VisibleGameObject::initializeActor()
{ };

void VisibleGameObject::draw (sf::RenderWindow& window)
{
  if (mIsLoaded) {
    window.draw(mSprite);
  } 
} 

void VisibleGameObject::setPosition (float x, float y)
{
  if (mIsLoaded) {
    mSprite.setPosition(x,y);
  }
}

void VisibleGameObject::move (float xOffset, float yOffset)
{
  if (mIsLoaded) { //TODO: Stipulations for walls and stuff would go here
    mSprite.move(xOffset,yOffset);
  }
}

