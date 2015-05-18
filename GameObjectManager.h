#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H

#include "IVisibleGameObject.h"

class GameObjectManager
{
  public:
    GameObjectManager();
    ~GameObjectManager();

    void add(std::string name, IVisibleGameObject* gameObject);
    void remove(std::string name);
    int getObjectCount() const;
    IVisibleGameObject* get(std::string name) const;

    void drawAll (sf::RenderWindow& window);
    void updateAll (sf::Time deltaTime);

  private:
    std::map<std::string, IVisibleGameObject*> mGameObjects;

    struct GameObjectDeallocator
    {
      void operator() (const std::pair<std::string, IVisibleGameObject*>& p) const
      {
        delete p.second;
      }
    };
};

#endif
