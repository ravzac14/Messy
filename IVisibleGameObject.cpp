/* Visible sprite base-class
 */

#include "stdafx.h"
#include "IVisibleGameObject.h"

IVisibleGameObject::IVisibleGameObject () : mIsLoaded {false}
{ }

IVisibleGameObject::~IVisibleGameObject ()
{ }

void IVisibleGameObject::load (std::string filename)
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

void IVisibleGameObject::update ()
{ }

sf::Vector2f IVisibleGameObject::getPosition () const
{
  if (mIsLoaded)
    return mSprite.getPosition();
  return sf::Vector2f();
}

bool IVisibleGameObject::isLoaded() const
{
  return mIsLoaded;
}

bool IVisibleGameObject::isInitialized() const
{
  return mIsInitialized;
}

void IVisibleGameObject::setInitialized(bool b)
{
  mIsInitialized = b;
}

sf::Sprite& IVisibleGameObject::getSprite ()
{
  return mSprite;
}

void IVisibleGameObject::initializeActor()
{ };

void IVisibleGameObject::draw (sf::RenderWindow& window)
{
  if (mIsLoaded) {
    window.draw(mSprite);
  } 
} 

void IVisibleGameObject::setPosition (float x, float y)
{
  if (mIsLoaded) {
    mSprite.setPosition(x,y);
  }
}

void IVisibleGameObject::move (float xOffset, float yOffset)
{
  if (mIsLoaded) { //TODO: Stipulations for walls and stuff would go here
    mSprite.move(xOffset,yOffset);
  }
}

