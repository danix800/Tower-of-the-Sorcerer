#include "game/game.h"
#include <cstdio>

int main() {
  printf("DEBUG: Entering main.cpp::main\n");
  // begin a new game
  Game *game = new Game();
  // enter the main loop to start the game
  int value = game->start();
  // free the memory
  delete game;

  return value;

  printf("DEBUG: Exiting main.cpp::main\n");
}