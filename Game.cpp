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
 
  //Init the static data members
  mMainWindow.create(sf::VideoMode(920,680,32),"Messy");
  mGameState = Game::SPLASH;
  
  //Start the loop
  while (!isExiting())
  {
    gameLoop();
  }
  mMainWindow.close();
}//Game::Start

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
  while (mMainWindow.pollEvent(currentEvent))
  {
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
        mMainWindow.display();

        if (currentEvent.type == sf::Event::Closed) 
          mGameState = Game::EXITING;
      } break;
    }
  }
}

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
    case MainMenu::PLAY: {
      mGameState = Game::PLAYING;
    } break;
  }
}

//Make sure all the static memebers are init
Game::GameState Game::mGameState = UNINIT;
sf::RenderWindow Game::mMainWindow;
