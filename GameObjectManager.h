#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H

#include "VisibleGameObject.h"

class GameObjectManager
{
  public:
    GameObjectManager();
    ~GameObjectManager();

    void add(std::string name, VisibleGameObject* gameObject);
    void remove(std::string name);
    int getObjectCount() const;
    VisibleGameObject* get(std::string name) const;

    void drawAll(sf::RenderWindow& window);
    void updateAll ();

  private:
    std::map<std::string, VisibleGameObject*> mGameObjects;

    struct GameObjectDeallocator
    {
      void operator() (const std::pair<std::string, VisibleGameObject*>& p) const
      {
        delete p.second;
      }
    };
};

#endif
