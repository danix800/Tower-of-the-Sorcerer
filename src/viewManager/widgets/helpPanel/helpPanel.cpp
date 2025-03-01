#include "helpPanel.h"
#include "../../../resourceManager/resourceManager.h"
#include <cstdio>

HelpPanel::HelpPanel() : TextDisplay(HELP_X, HELP_Y, HELP_WIDTH, HELP_HEIGHT) {
  printf("DEBUG: Entering helpPanel.cpp::HELP_HEIGHT)\n");
  this->color(ResourceManager::HelpPanelColor);
  this->setText(ResourceManager::helpText.data());

  printf("DEBUG: Exiting helpPanel.cpp::HELP_HEIGHT)\n");
}

HelpPanel::~HelpPanel() {}