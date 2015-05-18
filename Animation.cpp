/* Animations
 *
 * Thanks to Maximilian Wagenbach
 */

#include "Animation.h"
#include "stdafx.h"

Animation::Animation () : mTexture (nullptr)
{ }

void Animation::addFrame (sf::Rect<int> rect)
{
  mFrames.push_back(rect);
}

void Animation::setSpriteSheet (const sf::Texture& texture)
{
  mTexture = &texture;
}

std::size_t Animation::getSize () const
{
  return mFrames.size();
}

const sf::Rect<int>& Animation::getFrame (std::size_t n) const
{
  return mFrames[n];
}
