/* Has the logic for the player actor, the maid
 */

#include "stdafx.h"
#include "Maid.h"
#include "Game.h"

Maid::Maid () : mVelocity {10.0f}
{ 
  initializeActor();
  assert(isInitialized());
}

Maid::~Maid ()
{ }

void Maid::handleKey()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { // --Up
    if (getFace() == Maid::UP) {
      move(0,-mVelocity);
     } else 
      setFace(Maid::UP);
  } 
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { // -- Down
    if (getFace() == Maid::DOWN)
      move(0,mVelocity);
    else
      setFace(Maid::DOWN);
    }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { // --Left
    if (getFace() == Maid::LEFT)
      move(-mVelocity,0);
    else
      setFace(Maid::LEFT);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { // --Right
    if (getFace() == Maid::RIGHT)
      move(mVelocity,0);
    else
      setFace(Maid::RIGHT);
  } 
} //handleKey

void Maid::update ()
{
    handleKey();
} //update

Maid::ActorFace Maid::getFace () 
{
  return mFace;
}

float Maid::getVelocity () const
{
  return mVelocity;
}

void Maid::setFace (ActorFace f)
{
  mFace = f;
  std::string newImage = getAnimation();
  load(newImage);
}

void Maid::move (float xOffset, float yOffset)
{
  if (mFoot == L)
    mFoot = R;
  else
    mFoot = L;
  std::string newImage = getAnimation();
  load(newImage);
 
  if (isLegalMove(getPosition().x + xOffset, getPosition().y + yOffset)) 
    getSprite().move(xOffset,yOffset);
}

bool Maid::isLegalMove(float newX, float newY)
{
  return (Game::isInWindowBounds(newX,newY,WIDTH,HEIGHT));
      //TODO: && getLevelManager().isInLevelBounds(newX,newY,WIDTH,HEIGHT)
}

std::string Maid::getAnimation ()
{
  switch (mFace) {
    case UP: {
      switch (mFoot) {
        case L: {
          return UP_L;
        } break;
        case R: {
          return UP_R;
        } break;
      } //switch mFoot
    } break;
    case DOWN: {
      switch (mFoot) {
        case L: {
          return DOWN_L;
        } break;
        case R: {
          return DOWN_R;
        } break;
      } //switch mFoot
    } break;
    case LEFT: {
      switch (mFoot) {
        case L: {
          return LEFT_L;
        } break;
        case R: {
          return LEFT_R;
        } break;
      } //switch mFoot
    } break;
    case RIGHT: {
      switch (mFoot) {
        case L: {
          return RIGHT_L;
        } break;
        case R: {
          return RIGHT_R;
        } break;
      } //switch mFoot
    } break;
  } //switch mFace
} //getAnimation

void Maid::initializeActor ()
{
  setInitialized(true);
  mFace = DOWN;
  mFoot = L;
  std::string newImage = getAnimation();
  load(newImage);
}
