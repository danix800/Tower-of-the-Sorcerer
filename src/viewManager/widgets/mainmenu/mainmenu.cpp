#include "mainmenu.h"
#include "../../../resourceManager/resourceManager.h"
#include <cstdio>

MainMenu::MainMenu()
    : Fl_Box(MAINMENU_X, MAINMENU_Y, MAINMENU_WIDTH, MAINMENU_HEIGHT) {
  printf("DEBUG: Entering mainmenu.cpp::MAINMENU_HEIGHT)\n");
  // style
  this->box(FL_NO_BOX);
  this->image(ResourceManager::MainMenu);
  // when first create, it should not be shown
  this->hide();

  printf("DEBUG: Exiting mainmenu.cpp::MAINMENU_HEIGHT)\n");
}

MainMenu::~MainMenu() {}
