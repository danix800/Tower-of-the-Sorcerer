#include "hero.h"
#include "../../../resourceManager/resourceManager.h"
#include <cstdio>

Hero::Hero()
    : Character(ID::HERO, Type::HERO, INIT_HEALTH, INIT_ATTACK, INIT_DEFENCE,
                INIT_MONEY, INIT_EXP) {
  printf("DEBUG: Entering hero.cpp::)\n");
  // init the info
  this->fightState = FightState::NO_FIGHT;
  this->waiting = false;
  // init the photos
  this->setPhotos(ResourceManager::HeroPhotos);
  // set the init direction
  this->setDirection(DOWN);

  printf("DEBUG: Exiting hero.cpp::)\n");
}

Hero::~Hero() {}

int Hero::getPreviousX() {
  printf("DEBUG: Entering hero.cpp::Hero::getPreviousX\n");
  return previousX;

  printf("DEBUG: Exiting hero.cpp::Hero::getPreviousX\n");
}

int Hero::getPreviousY() {
  printf("DEBUG: Entering hero.cpp::Hero::getPreviousY\n");
  return previousY;

  printf("DEBUG: Exiting hero.cpp::Hero::getPreviousY\n");
}

Hero::FightState Hero::getFightState() {
  printf("DEBUG: Entering hero.cpp::Hero::getFightState\n");
  return fightState;

  printf("DEBUG: Exiting hero.cpp::Hero::getFightState\n");
}

void Hero::setFightState(FightState fightState) {
  printf("DEBUG: Entering hero.cpp::fightState)\n");
  this->fightState = fightState;

  printf("DEBUG: Exiting hero.cpp::fightState)\n");
}

void Hero::setWaiting(bool waiting) {
  printf("DEBUG: Entering hero.cpp::waiting)\n");
  this->waiting = waiting;

  printf("DEBUG: Exiting hero.cpp::waiting)\n");
}

void Hero::setDirection(Direction direction) {
  printf("DEBUG: Entering hero.cpp::direction)\n");
  this->setIndex(direction);

  printf("DEBUG: Exiting hero.cpp::direction)\n");
}

Hero::Direction Hero::getDirection() {
  printf("DEBUG: Entering hero.cpp::Hero::getDirection\n");
  int index = getIndex();
  index = index > 4 ? index - 4 : index;
  return (Direction)index;

  printf("DEBUG: Exiting hero.cpp::Hero::getDirection\n");
}

bool Hero::canMove() {
  printf("DEBUG: Entering hero.cpp::Hero::canMove\n");
  return fightState == NO_FIGHT && !waiting;

  printf("DEBUG: Exiting hero.cpp::Hero::canMove\n");
}

void Hero::setPosition(int x, int y) {
  printf("DEBUG: Entering hero.cpp::y)\n");
  // update previous position
  previousX = getCurrentX();
  previousY = getCurrentY();
  // update current position
  Character::setPosition(x, y);

  printf("DEBUG: Exiting hero.cpp::y)\n");
}

void Hero::setPosition(Cell *cell) {
  printf("DEBUG: Entering hero.cpp::*cell)\n");
  // update previous position
  previousX = getCurrentX();
  previousY = getCurrentY();
  // update current position
  Character::setPosition(cell);

  printf("DEBUG: Exiting hero.cpp::*cell)\n");
}
