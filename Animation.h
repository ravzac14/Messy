#ifndef ANIMATION_H
#define ANIMATION_H

//Thanks to Maximilian Wagenbach

#include <vector>

class Animation
{
  public:
    Animation ();

    void addFrame (sf::Rect<int> rect);
    void setSpriteSheet (const sf::Texture& texture);
    const sf::Texture* getSpriteSheet () const;
    std::size_t getSize () const;
    const sf::Rect<int>& getFrame (std::size_t n) const;

  private:
    std::vector<sf::Rect<int> mFrames;
    const sf::Texture* mTexture;
};

#endif
