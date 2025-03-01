#include "character.h"
#include <cstdio>

Character::Character(ID id, Type type, int health, int attack, int defence,
                     int money, int exp, string name, string expression,
                     int level)
    : Cell(id, type), health(health), attack(attack), defence(defence),
      money(money), exp(exp), name(name), expression(expression), level(level) {

}

Character::~Character() {}

bool Character::canDefeat(Character *enemy) const {
  printf("DEBUG: Entering character.cpp::const\n");
  bool ret;
  // compute the damage to the enemy in each fight
  int damageToEnemy = this->attack - enemy->defence;
  // if cannot damage the enemy, then cannot defeat it
  if (damageToEnemy <= 0)
    ret = false;
  else {
    // compute how many times you need to kill the enemy
    int fightTimes = enemy->health / damageToEnemy;
    // round up the fightTimes
    if (enemy->health % damageToEnemy != 0)
      fightTimes++;
    // compute the damage to this character in each fight
    int damageToMe = enemy->attack - this->defence;
    if (damageToMe < 0)
      damageToMe = 0;
    // compute the total damage this character take
    int loseHealth = fightTimes * damageToMe;
    // judge whether the character will die
    if (loseHealth < this->health)
      ret = true;
    else
      ret = false;
  }
  return ret;

  printf("DEBUG: Exiting character.cpp::const\n");
}

void Character::attackEnemy(Character *enemy) {
  printf("DEBUG: Entering character.cpp::enemy)\n");
  // before this function, it's ensured that
  // this character can defeat the enemy
  int damageToEnemy = this->attack - enemy->defence;
  int damageToMe = enemy->attack - this->defence;
  if (damageToMe < 0)
    damageToMe = 0;
  // begin to fight
  enemy->health -= damageToEnemy;
  if (enemy->health < 0)
    enemy->health = 0;
  // can defeat enemy, so the remain health > 0
  this->health -= damageToMe;

  printf("DEBUG: Exiting character.cpp::enemy)\n");
}

void Character::getRewardFrom(Character *enemy) {
  printf("DEBUG: Entering character.cpp::*enemy)\n");
  this->money += enemy->money;
  this->exp += enemy->money;

  printf("DEBUG: Exiting character.cpp::*enemy)\n");
}

void Character::getExtraDamageFrom(Character *enemy) {
  printf("DEBUG: Entering character.cpp::*enemy)\n");
  // get extra damage from special enemy
  if (enemy->getCellID() == Cell::ID::MAGE)
    this->health -= 100;
  else if (enemy->getCellID() == Cell::ID::RED_MAGE)
    this->health -= 300;
  else if (enemy->getCellID() == Cell::ID::BLUE_KNIGHT)
    this->health -= this->health / 4;
  else if (enemy->getCellID() == Cell::ID::GHOST_KNIGHT_CAPTAIN)
    this->health -= this->health / 3;

  // ensure this character will not die
  if (this->health <= 0)
    this->health = 1;

  printf("DEBUG: Exiting character.cpp::*enemy)\n");
}

bool Character::dead() {
  printf("DEBUG: Entering character.cpp::Character::dead\n");
  return health == 0;

  printf("DEBUG: Exiting character.cpp::Character::dead\n");
}

bool Character::canDamage(Character *enemy) {
  printf("DEBUG: Entering character.cpp::*enemy)\n");
  return this->attack > enemy->defence;

  printf("DEBUG: Exiting character.cpp::*enemy)\n");
}

int Character::getDamageTo(Character *enemy) {
  printf("DEBUG: Entering character.cpp::*enemy)\n");
  int totalDamage = 0;
  if (enemy->canDamage(this)) {
    int damageToEnemy = this->attack - enemy->defence;
    if (damageToEnemy < 0)
      damageToEnemy = 0;
    int damageToMe = enemy->attack - this->defence;

    // compute after how many times you will die
    int fightTimes = this->health / damageToMe;
    // round up the fightTimes
    if (this->health % damageToMe != 0)
      fightTimes++;
    // compute the damage
    totalDamage = fightTimes * damageToEnemy;
  }

  return totalDamage;

  printf("DEBUG: Exiting character.cpp::*enemy)\n");
}

void Character::levelUP(int levels) {
  printf("DEBUG: Entering character.cpp::levels)\n");
  level += levels;
  health += 1000 * levels;
  attack += 10 * levels;
  defence += 10 * levels;

  printf("DEBUG: Exiting character.cpp::levels)\n");
}

int Character::getLevel() {
  printf("DEBUG: Entering character.cpp::Character::getLevel\n");
  return level;

  printf("DEBUG: Exiting character.cpp::Character::getLevel\n");
}

int Character::getHealth() {
  printf("DEBUG: Entering character.cpp::Character::getHealth\n");
  return health;

  printf("DEBUG: Exiting character.cpp::Character::getHealth\n");
}

int Character::getAttack() {
  printf("DEBUG: Entering character.cpp::Character::getAttack\n");
  return attack;

  printf("DEBUG: Exiting character.cpp::Character::getAttack\n");
}

int Character::getDefence() {
  printf("DEBUG: Entering character.cpp::Character::getDefence\n");
  return defence;

  printf("DEBUG: Exiting character.cpp::Character::getDefence\n");
}

int Character::getMoney() {
  printf("DEBUG: Entering character.cpp::Character::getMoney\n");
  return money;

  printf("DEBUG: Exiting character.cpp::Character::getMoney\n");
}

int Character::getExp() {
  printf("DEBUG: Entering character.cpp::Character::getExp\n");
  return exp;

  printf("DEBUG: Exiting character.cpp::Character::getExp\n");
}

string Character::getName() {
  printf("DEBUG: Entering character.cpp::Character::getName\n");
  return name;

  printf("DEBUG: Exiting character.cpp::Character::getName\n");
}

string Character::getExpression() {
  printf("DEBUG: Entering character.cpp::Character::getExpression\n");
  return expression;

  printf("DEBUG: Exiting character.cpp::Character::getExpression\n");
}

void Character::setLevel(int level) {
  printf("DEBUG: Entering character.cpp::level)\n");
  this->level = level;

  printf("DEBUG: Exiting character.cpp::level)\n");
}

void Character::setHealth(int health) {
  printf("DEBUG: Entering character.cpp::health)\n");
  this->health = health;

  printf("DEBUG: Exiting character.cpp::health)\n");
}

void Character::setAttack(int attack) {
  printf("DEBUG: Entering character.cpp::attack)\n");
  this->attack = attack;

  printf("DEBUG: Exiting character.cpp::attack)\n");
}

void Character::setDefence(int defence) {
  printf("DEBUG: Entering character.cpp::defence)\n");
  this->defence = defence;

  printf("DEBUG: Exiting character.cpp::defence)\n");
}

void Character::setMoney(int money) {
  printf("DEBUG: Entering character.cpp::money)\n");
  this->money = money;

  printf("DEBUG: Exiting character.cpp::money)\n");
}

void Character::setExp(int exp) {
  printf("DEBUG: Entering character.cpp::exp)\n");
  this->exp = exp;

  printf("DEBUG: Exiting character.cpp::exp)\n");
}
