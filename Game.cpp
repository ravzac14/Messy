/* This holds the logic for the game loop
 * TODO:Maybe think about d-syncing the graphics update and logic update
 */

#include "stdafx.h"
#include "Game.h"
#include "SplashScreen.h"
#include "MainMenu.h"

void Game::start(void)
{
  //TODO: This buddy needs to have more added to it
  if (mGameState != Game::UNINIT)
    return;
 
  mMainWindow.create(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT,32),"Messy");

  mGameState = Game::SPLASH;

  //Load first level

  //Load the actor
  Maid* actor = new Maid();
  actor->setPosition(WINDOW_WIDTH-320,20); //TODO: Here would be different for each level, so this init may move
  mGameObjectManager.add("Maid", actor);

  mGameClock.restart();

  //Start the loop
  while (!isExiting())
  {
    gameLoop();
  }
  mMainWindow.close();
}//Game::Start

//This is just for general playing key input (not sprite manipulation)
void Game::handleKey()
{ 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
      showMenu();
    } 
} //handleKey

sf::RenderWindow& Game::getWindow ()
{
  return mMainWindow;
}

bool Game::isExiting()
{
  if (mGameState == Game::EXITING)
    return true;
  else
    return false;
}

void Game::gameLoop()
{
  sf::Event currentEvent;
  
  //Pivot off of the current game state
  switch (mGameState) {
    case Game::SPLASH: {
      showSplash();
    } break;
    case Game::MENU: {
      showMenu();
    } break;
    case Game::PLAYING: {  
      mMainWindow.clear(sf::Color(65,170,190));
      mGameObjectManager.drawAll(mMainWindow);
      mMainWindow.display();
      
      while (mMainWindow.pollEvent(currentEvent))
      {
        if (currentEvent.type == sf::Event::Closed) 
          mGameState = Game::EXITING;
      }
      Game::handleKey();
//TODO: Movement is broked

//TODO:mElapsed gets thrown to screen

//TODO: Pull out event handling in MainMenu

      if ((mGameClock.getElapsedTime().asSeconds() - mLastUpdate) >= .03){
        mGameObjectManager.updateAll();
        mLastUpdate = mGameClock.getElapsedTime().asSeconds();
      } 
    } break;

  }//switch
}//gameLoop

void Game::showSplash()
{
  SplashScreen splash;
  splash.show(mMainWindow);
  mGameState = Game::MENU;
}

void Game::showMenu()
{
  MainMenu mainMenu;
  MainMenu::MenuResult result = mainMenu.show(mMainWindow);
  switch (result) {
    case MainMenu::EXIT: {
      mGameState = Game::EXITING;
    } break;
    //case MainMenu::HIGHSCORE: {
    //  mGameState = Game::HIGHSCORING;
    //} break;
    case MainMenu::PLAY: {
      mGameState = Game::PLAYING;
    } break;
  }
}

//Make sure all the static memebers are init
float Game::mLastUpdate = 0;
float Game::mElapsedTime;
sf::Clock Game::mGameClock;
GameObjectManager Game::mGameObjectManager;
Game::GameState Game::mGameState = UNINIT;
sf::RenderWindow Game::mMainWindow;
