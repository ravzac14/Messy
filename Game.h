#ifndef GAME_H
#define GAME_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Maid.h"
#include "GameObjectManager.h"

class Game
{
  public:
    static void start();
    static sf::RenderWindow& getWindow();
    static bool isInWindowBounds(float newX, float newY, float spriteWidth, float spriteHeight);
    static void delayBy (float duration);

    const static int WINDOW_HEIGHT = 680;
    const static int WINDOW_WIDTH = 920;

  private: 
    static bool isExiting();
    static void gameLoop();

    static void showLoadScreen();
    static void showPauseMenu();
    static void showSplash();
    static void showMenu();
    static void showConfirmExitMenu();

    //static void handleKey(sf::Keyboard::Key code);
    static void handleKey();

    enum GameState {UNINIT, SPLASH, MENU, LOADING, PAUSED, PLAYING, CONFIRMING_EXIT, EXITING};

    static GameState mGameState;
    static GameState mPreviousGameState;
    static sf::RenderWindow mMainWindow;
    static GameObjectManager mGameObjectManager;
    static sf::Clock mGameClock;
    static float mElapsedTime;
    static float mLastUpdate;
};

#endif
