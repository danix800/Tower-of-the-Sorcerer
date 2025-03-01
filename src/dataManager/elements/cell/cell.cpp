#include "cell.h"
#include <cstdio>

Cell::Cell(ID id, Type type) {
  this->id = id;
  this->type = type;
  this->index = 0;
  this->photos = photos;
  this->viewedAllPhotos = false;
}

Cell::~Cell() {}

void Cell::setPhoto(Fl_Image *photo) {
  printf("DEBUG: Entering cell.cpp::*photo)\n");
  this->photos = LinkedList<Fl_Image *>({photo});

  printf("DEBUG: Exiting cell.cpp::*photo)\n");
}

void Cell::setPhotos(LinkedList<Fl_Image *> photos) {
  printf("DEBUG: Entering cell.cpp::photos)\n");
  this->photos = photos;

  printf("DEBUG: Exiting cell.cpp::photos)\n");
}

Fl_Image *Cell::getPhoto() { return photos[index]; }

bool Cell::shownAllPhotos() {
  printf("DEBUG: Entering cell.cpp::Cell::shownAllPhotos\n");
  return viewedAllPhotos;

  printf("DEBUG: Exiting cell.cpp::Cell::shownAllPhotos\n");
}

Cell::ID Cell::getCellID() {
  printf("DEBUG: Entering cell.cpp::Cell::getCellID\n");
  return id;

  printf("DEBUG: Exiting cell.cpp::Cell::getCellID\n");
}

Cell::Type Cell::getCellType() {
  printf("DEBUG: Entering cell.cpp::Cell::getCellType\n");
  return type;

  printf("DEBUG: Exiting cell.cpp::Cell::getCellType\n");
}

void Cell::changePhoto() {
  printf("DEBUG: Entering cell.cpp::Cell::changePhoto\n");
  // show next photo
  index++;
  // if shown all photos, show the first photo
  if (index == photos.size()) {
    viewedAllPhotos = true;
    index = 0;
  }

  printf("DEBUG: Exiting cell.cpp::Cell::changePhoto\n");
}

void Cell::setIndex(int index) {
  printf("DEBUG: Entering cell.cpp::index)\n");
  this->index = index;

  printf("DEBUG: Exiting cell.cpp::index)\n");
}

int Cell::getIndex() {
  printf("DEBUG: Entering cell.cpp::Cell::getIndex\n");
  return index;

  printf("DEBUG: Exiting cell.cpp::Cell::getIndex\n");
}

bool Cell::isFinalPhoto() {
  printf("DEBUG: Entering cell.cpp::Cell::isFinalPhoto\n");
  return index == photos.size() - 1;

  printf("DEBUG: Exiting cell.cpp::Cell::isFinalPhoto\n");
}

int Cell::getCurrentX() {
  printf("DEBUG: Entering cell.cpp::Cell::getCurrentX\n");
  return currentX;

  printf("DEBUG: Exiting cell.cpp::Cell::getCurrentX\n");
}

int Cell::getCurrentY() {
  printf("DEBUG: Entering cell.cpp::Cell::getCurrentY\n");
  return currentY;

  printf("DEBUG: Exiting cell.cpp::Cell::getCurrentY\n");
}

void Cell::setPosition(int x, int y) {
  printf("DEBUG: Entering cell.cpp::y)\n");
  currentX = x;
  currentY = y;

  printf("DEBUG: Exiting cell.cpp::y)\n");
}

void Cell::setPosition(Cell *cell) {
  printf("DEBUG: Entering cell.cpp::*cell)\n");
  currentX = cell->getCurrentX();
  currentY = cell->getCurrentY();

  printf("DEBUG: Exiting cell.cpp::*cell)\n");
}
