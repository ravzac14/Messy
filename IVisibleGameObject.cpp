/* Visible sprite base-class
 */

#include "stdafx.h"
#include "IVisibleGameObject.h"

IVisibleGameObject::IVisibleGameObject () : mIsLoaded {false}
{ }

IVisibleGameObject::~IVisibleGameObject ()
{ }

void IVisibleGameObject::load (const std::string filename)
{
  const sf::Rect<int> empty;
  if (mIsInitialized) {
    bool noErrorLoading = mTexture.loadFromFile(filename, empty); 
    if (!noErrorLoading) {
      mFileName = "";
      mIsLoaded = false;
    } else {
      mFileName = filename;
      mSprite.setTexture(mTexture);
      mIsLoaded = true;
    }
  } else {
    initializeActor();
    load(filename);
  }
}

void IVisibleGameObject::update (sf::Time deltaTime)
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

void IVisibleGameObject::setColor (const sf::Color& color)
{
  mVertices[0].color = color;
  mVertices[1].color = color;
  mVertices[2].color = color;
  mVertices[3].color = color;
}

void IVisibleGameObject::draw (sf::RenderTarget& target, sf::RenderStates states) const
{
  if (mIsLoaded) {
    target.draw(mSprite);
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

