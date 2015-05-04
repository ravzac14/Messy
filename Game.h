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

    const static int WINDOW_HEIGHT = 680;
    const static int WINDOW_WIDTH = 920;

  private: 
    static bool isExiting();
    static void gameLoop();

    static void showSplash();
    static void showMenu();

    //static void handleKey(sf::Keyboard::Key code);
    static void handleKey();

    enum GameState {UNINIT, SPLASH, PAUSED, MENU, PLAYING, EXITING};

    static GameState mGameState;
    static sf::RenderWindow mMainWindow;
    static GameObjectManager mGameObjectManager;
    static sf::Clock mGameClock;
    static float mElapsedTime;
    static float mLastUpdate;
};

#endif
