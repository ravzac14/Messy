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

void Maid::update (sf::Time deltaTime)
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
  std::string newImage = getWalkAnimation();
  load(newImage);
}

void Maid::move (float xOffset, float yOffset)
{
  changeFooting();
  std::string newImage = getWalkAnimation();
  load(newImage);
 
  if (isLegalMove(getPosition().x + xOffset, getPosition().y + yOffset)) 
    getSprite().move(xOffset,yOffset);
}

void Maid::changeFooting ()
{
  if (mFoot == LL) { // --LL
    mFoot = LN;
    mPreviousFoot = LL;
  } else if (mFoot == LN && mPreviousFoot == LL) { // --LN --LL
    mFoot = N;
    mPreviousFoot = LN;
  } else if (mFoot == LN && mPreviousFoot == N) { // --LN --N
    mFoot = LL;
    mPreviousFoot = LN;
  } else if (mFoot == N && mPreviousFoot == LN) { // --N --LN
    mFoot = RN;
    mPreviousFoot = N;
  } else if (mFoot == N && mPreviousFoot == RN) { // --N --RN
    mFoot = LN;
    mPreviousFoot = N;
  } else if (mFoot == RN && mPreviousFoot == N) { // --RN --N
    mFoot = RR;
    mPreviousFoot = RN;
  } else if (mFoot == RN && mPreviousFoot == RR) { // --RN --RR
    mFoot = N;
    mPreviousFoot = RN;
  } else if (mFoot == RR) { // --RR
    mFoot = RN;
    mPreviousFoot = RR;
  }
}

bool Maid::isLegalMove(float newX, float newY)
{
  return (Game::isInWindowBounds(newX,newY,WIDTH,HEIGHT));
      //TODO: && getLevelManager().isInLevelBounds(newX,newY,WIDTH,HEIGHT)
}

std::string Maid::getWalkAnimation ()
{
  switch (mFace) {
    case UP: {
      switch (mFoot) {
        case LL: {
          return UP_LL;
        } break;
        case LN: {
          return UP_LN;
        } break;
        case N: {
          return UP_N;
        } break;
        case RN: {
          return UP_RN;
        } break;
        case RR: {
          return UP_RR;
        } break;
      } //switch mFoot
    } break;
    case DOWN: {
      switch (mFoot) {
        case LL: {
          return DOWN_LL;
        } break;
        case LN: {
          return DOWN_LN;
        } break;
        case N: {
          return DOWN_N;
        } break;
        case RN: {
          return DOWN_RN;
        } break;
        case RR: {
          return DOWN_RR;
        } break;
      } //switch mFoot
    } break;
    case LEFT: {
      switch (mFoot) {
        case LL: {
          return LEFT_LL;
        } break;
        case LN: {
          return LEFT_LN;
        } break;
        case N: {
          return LEFT_N;
        } break;
        case RN: {
          return LEFT_RN;
        } break;
        case RR: {
          return LEFT_RR;
        } break;
      } //switch mFoot
    } break;
    case RIGHT: {
      switch (mFoot) {
        case LL: {
          return RIGHT_LL;
        } break;
        case LN: {
          return RIGHT_LN;
        } break;
        case N: {
          return RIGHT_N;
        } break;
        case RN: {
          return RIGHT_RN;
        } break;
        case RR: {
          return RIGHT_RR;
        } break;
      } //switch mFoot
    } break;
  } //switch mFace
} //getWalkAnimation

void Maid::initializeActor ()
{
  setInitialized(true);
  mFace = DOWN;
  mFoot = N;
  mPreviousFoot = RN;
  std::string newImage = getWalkAnimation();
  load(newImage);
}
