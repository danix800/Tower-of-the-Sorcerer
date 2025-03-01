#include "statusbar.h"
#include "../../../resourceManager/resourceManager.h"
#include <cstdio>

StatusBar::StatusBar()
    : Fl_Box(0, STATUSBAR_Y, STATUSBAR_WIDTH, STATUSBAR_HEIGHT) {
  printf("DEBUG: Entering statusbar.cpp::STATUSBAR_HEIGHT)\n");
  // set style
  this->box(FL_FLAT_BOX);
  // set color
  this->color(FL_WHITE);
  // set font
  this->labelfont(ResourceManager::HeiTi);
  this->labelsize(STATUSBAR_TEXTSIZE);
  this->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
  // when first create, it should not be shown
  this->hide();

  printf("DEBUG: Exiting statusbar.cpp::STATUSBAR_HEIGHT)\n");
}

StatusBar::~StatusBar() {}

void StatusBar::printStatus(string message) {
  printf("DEBUG: Entering statusbar.cpp::message)\n");
  message = ' ' + message;
  this->copy_label(message.data());
  this->redraw_label();

  printf("DEBUG: Exiting statusbar.cpp::message)\n");
}