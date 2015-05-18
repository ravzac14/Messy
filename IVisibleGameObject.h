#ifndef I_VISIBLE_GAME_OBJECT_H
#define I_VISIBLE_GAME_OBJECT_H

class IVisibleGameObject : public sf::Drawable, public sf::Transformable
{
  public:
    IVisibleGameObject();
    ~IVisibleGameObject();

    virtual void load(const std::string filename);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void move(float xOffset, float yOffset);
    virtual void initializeActor();
    virtual void update(sf::Time deltaTime);

    void setColor (const sf::Color& color);
    virtual bool isLoaded () const;
    virtual void setPosition(float x, float y);
    virtual sf::Vector2f getPosition () const;
    virtual bool isInitialized() const;
    virtual void setInitialized(bool b);

  protected:
    bool mIsLoaded;
    bool mIsInitialized;
    sf::Sprite& getSprite();

  private:
    sf::Sprite mSprite;
    sf::Texture mTexture;
    std::string mFileName;
    sf::Vertex mVertices[4];
};

#endif
