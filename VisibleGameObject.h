#ifndef VISIBLE_GAME_OBJECT_H
#define VISIBLE_GAME_OBJECT_H

class VisibleGameObject
{
  public:
    VisibleGameObject();
    virtual ~VisibleGameObject();

    virtual void load(std::string filename);
    virtual void draw(sf::RenderWindow& window);
    virtual void move(float xOffset, float yOffset);
    virtual void initializeActor();
    virtual void update();

    virtual bool isLoaded () const;
    virtual void setPosition(float x, float y);
    virtual sf::Vector2f getPosition () const;
    virtual bool isInitialized() const;
    virtual void setInitialized(bool b);
    
  protected:
    bool mIsLoaded;
    bool mIsInitialized;
    sf::Sprite getSprite();

  private:
    sf::Sprite mSprite;
    sf::Image mImage;
    sf::Texture mTexture;
    std::string mFileName;
};

#endif
