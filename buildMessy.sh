#!/bin/bash

#Just builds Messy so i don't have to write it every time

g++ -std=c++11 Messy.cpp Game.cpp IVisibleGameObject.cpp PauseMenu.cpp GameObjectManager.cpp Maid.cpp MainMenu.cpp SplashScreen.cpp stdafx.cpp -o Messy -lsfml-graphics -lsfml-window -lsfml-system
