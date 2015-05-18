/* This holds the logic for the game loop
 * TODO:Maybe think about d-syncing the graphics update and logic update
 */

#include "stdafx.h"
#include "Game.h"
#include "SplashScreen.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "ConfirmExitMenu.h"
#include "LoadScreen.h"

#define SPRITE_DELAY .10  //This is sprite input delay, to simulate older fps
                          // .10 = 10 FPS, 0.033 = 30 FPS, .066 = 60 FPS, etc

void Game::start(void)
{
  //TODO: This buddy needs to have more added to it
  if (mGameState != Game::UNINIT)
    return;
 
  mMainWindow.create(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT,32),"Messy");
  mMainWindow.setFramerateLimit(60);
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

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//       Game handle key
//This is just for general playing key input (not sprite manipulation)
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void Game::handleKey()
{ 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
      mPreviousGameState = Game::PLAYING;
      mGameState = Game::PAUSED;
    }
} //handleKey

sf::RenderWindow& Game::getWindow ()
{
  return mMainWindow;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//      Helper functions  
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

bool Game::isInWindowBounds(float left, float top, float sWidth, float sHeight)
{
  float right = left + sWidth;
  float bottom = top + sHeight;

  return ((left >= 0) && 
          (right <= WINDOW_WIDTH) &&
          (top >= 0) &&
          (bottom <= WINDOW_HEIGHT));
}

void Game::delayBy(float duration)
{
  float currentTime = mGameClock.getElapsedTime().asSeconds();
  while ((mGameClock.getElapsedTime().asSeconds() - currentTime) <= duration) 
  { } //Do nothing but wait 
}

bool Game::isExiting()
{
  if (mGameState == Game::EXITING)
    return true;
  else
    return false;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//       GAME LOOP
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void Game::gameLoop()
{
  sf::Event currentEvent;
  
  //Pivot off of the current game state
  switch (mGameState) {
    case Game::SPLASH: {
      mMainWindow.setMouseCursorVisible(false);
      showSplash();
    } break;
    case Game::MENU: {
      mMainWindow.setMouseCursorVisible(true);
      showMenu();
    } break;
    case Game::LOADING: {
      mMainWindow.setMouseCursorVisible(false);
      showLoadScreen();
    } break;
    case Game::PAUSED: {
      mMainWindow.setMouseCursorVisible(false);
      showPauseMenu();
    } break;
    case Game::PLAYING: {  
      mMainWindow.clear(sf::Color(65,170,190));
      mMainWindow.setMouseCursorVisible(false);
      mGameObjectManager.drawAll(mMainWindow);
      mMainWindow.display();
      
      while (mMainWindow.pollEvent(currentEvent))
      {
        if (currentEvent.type == sf::Event::Closed) {
          mPreviousGameState = Game::PLAYING;
          mGameState = Game::CONFIRMING_EXIT;
        }
      }
      Game::handleKey();

//TODO:mElapsed gets thrown to screen

      if ((mGameClock.getElapsedTime().asSeconds() - mLastUpdate) >= SPRITE_DELAY){
        sf::Time oldTime = sf::seconds(mLastUpdate);
        mGameObjectManager.updateAll(mGameClock.getElapsedTime() - oldTime);
        mLastUpdate = mGameClock.getElapsedTime().asSeconds();
      } 
    } break;
    case Game::CONFIRMING_EXIT: {
      mMainWindow.setMouseCursorVisible(true);
      showConfirmExitMenu();
    } break;
  }//switch
}//gameLoop


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//       The showXX () methods
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void Game::showConfirmExitMenu()
{
  Game::delayBy(0.20f);
  ConfirmExitMenu ceMenu;
  ConfirmExitMenu::MenuResult result = ceMenu.show(mMainWindow);
  switch (result) {
    case ConfirmExitMenu::EXIT: {
      if (mPreviousGameState == Game::PAUSED) {
        mPreviousGameState = Game::CONFIRMING_EXIT;
        mGameState = Game::MENU;
      } else {
        mPreviousGameState = Game::CONFIRMING_EXIT;
        mGameState = Game::EXITING; 
      }
    } break;
    case ConfirmExitMenu::PLAY: {
      if (mPreviousGameState == Game::PAUSED) {
        mPreviousGameState = Game::CONFIRMING_EXIT;
        mGameState = Game::PAUSED;
      } else {
        mGameState = mPreviousGameState; 
        mPreviousGameState = Game::CONFIRMING_EXIT;
      }
    } break;
    case ConfirmExitMenu::HARD_EXIT: {
      mPreviousGameState = Game::CONFIRMING_EXIT;
      mGameState = Game::EXITING;
    }
  }
  Game::delayBy(0.20f);
}

void Game::showLoadScreen()
{
  LoadScreen load;
  load.show(mMainWindow);
  mPreviousGameState = Game::LOADING;
  mGameState = Game::PLAYING;
}

void Game::showPauseMenu()
{
  Game::delayBy(0.20f); //Was being weird about handling keys to quick
  PauseMenu pauseMenu;
  PauseMenu::MenuResult result = pauseMenu.show(mMainWindow);
  switch (result) {
    case PauseMenu::EXIT: {
      mPreviousGameState = Game::PAUSED;
      mGameState = Game::CONFIRMING_EXIT;
    } break;
    case PauseMenu::PLAY: {
      mPreviousGameState = Game::PAUSED;
      mGameState = Game::PLAYING;
    } break; 
    case PauseMenu::HARD_EXIT: {
      mPreviousGameState = Game::PAUSED;
      mGameState = Game::CONFIRMING_EXIT;
    } break;
  }//switch
  Game::delayBy(0.20f); //Same ^
}

void Game::showSplash()
{
  SplashScreen splash;
  splash.show(mMainWindow);
  mPreviousGameState = Game::SPLASH;
  mGameState = Game::MENU;
}

void Game::showMenu()
{
  Game::delayBy(0.20f);
  MainMenu mainMenu;
  MainMenu::MenuResult result = mainMenu.show(mMainWindow);
  switch (result) {
    case MainMenu::EXIT: {
      mPreviousGameState = Game::MENU;
      mGameState = Game::CONFIRMING_EXIT;
    } break;
    //TODO: case MainMenu::HIGHSCORE: {i
    //  mPreviouseGameState = Game::MENU;
    //  mGameState = Game::HIGHSCORING;
    //} break;
    case MainMenu::PLAY: {
      mPreviousGameState = Game::MENU;
      mGameState = Game::LOADING;
    } break;
  }
  Game::delayBy(0.20f);
}

//Make sure all the static memebers are init
float Game::mLastUpdate = 0;
float Game::mElapsedTime;
sf::Clock Game::mGameClock;
GameObjectManager Game::mGameObjectManager;
Game::GameState Game::mGameState = UNINIT;
Game::GameState Game::mPreviousGameState = UNINIT;
sf::RenderWindow Game::mMainWindow;
