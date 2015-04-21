#ifndef GAME_H
#define GAME_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class Game
{
  public:
    static void start();

  private: 
    static bool isExiting();
    static void gameLoop();

    static void showSplash();
    static void showMenu();

    enum GameState {UNINIT, SPLASH, PAUSED, MENU, PLAYING, EXITING};

    static GameState mGameState;
    static sf::RenderWindow mMainWindow;
};

#endif
