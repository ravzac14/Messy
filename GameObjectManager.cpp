/* Holds all the logic for the object manager
 */

#include "stdafx.h"
#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{ }

GameObjectManager::~GameObjectManager()
{
  std::for_each(mGameObjects.begin(),mGameObjects.end(),GameObjectDeallocator());
}

void GameObjectManager::add (std::string name, IVisibleGameObject* gameObject)
{
  mGameObjects.insert(std::pair<std::string,IVisibleGameObject*>(name,gameObject));
}

void GameObjectManager::remove (std::string name)
{
  std::map<std::string, IVisibleGameObject*>::iterator results = mGameObjects.find(name);
  if (results != mGameObjects.end()) {
    delete results->second;
    mGameObjects.erase(results);
  }
}

void GameObjectManager::updateAll (sf::Time deltaTime) 
{
  std::map<std::string, IVisibleGameObject*>::const_iterator itr = mGameObjects.begin();
  while (itr != mGameObjects.end()) {
    itr->second->update(deltaTime);
    itr++;
  }
}

IVisibleGameObject* GameObjectManager::get (std::string name) const
{
  std::map<std::string, IVisibleGameObject*>::const_iterator results = mGameObjects.find(name);
  if (results == mGameObjects.end())
    return nullptr;
  return results->second;
}

int GameObjectManager::getObjectCount () const
{
  return mGameObjects.size();
}

void GameObjectManager::drawAll (sf::RenderWindow& window)
{
  std::map<std::string, IVisibleGameObject*>::const_iterator itr = mGameObjects.begin();
  while (itr != mGameObjects.end()) {
    itr->second->draw(window,sf::RenderStates::Default);
    itr++;
  }
}
