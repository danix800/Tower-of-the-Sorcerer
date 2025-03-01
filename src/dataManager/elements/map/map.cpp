#include "map.h"
#include "../barrierFactory/barrierFactory.h"
#include "../enemyFactory/enemyFactory.h"
#include "../itemFactory/itemFactory.h"
#include "../npcFactory/npcFactory.h"
#include <cstdio>
#include <fstream>

Map::Map(string filename) {
  if (filename.length() > 0)
    loadMap(filename);
}

Map::~Map() {}

Cell *Map::getCellAt(int i, int j) { return matrix[i][j]; }

LinkedList<Cell *> Map::getAnimeCells() { return animeCells; }

LinkedList<Cell *> Map::getEnemies() { return enemies; }

Door *Map::getOpeningDoor() {
  Door *door = nullptr;
  for (Node<Cell *> *p = doors.begin(); p; p = p->getNext()) {
    door = (Door *)p->getValue();
    if (door->canPassIt())
      break;
  }
  return door;
}

int Map::getMatrixWidth() {
  printf("DEBUG: Entering map.cpp::Map::getMatrixWidth\n");
  return MATRIX_WIDTH;

  printf("DEBUG: Exiting map.cpp::Map::getMatrixWidth\n");
}

Cell *Map::getUpStair() {
  Cell *ret = nullptr;
  // find the upstair and return
  for (int i = 0; i < MATRIX_WIDTH; i++)
    for (int j = 0; j < MATRIX_WIDTH; j++)
      if (matrix[i][j]->getCellID() == Cell::ID::UPSTAIRS) {
        ret = matrix[i][j];
        break;
      }
  return ret;
}

Cell *Map::getDownStair() {
  Cell *ret = nullptr;
  // find the downstair and return
  for (int i = 0; i < MATRIX_WIDTH; i++)
    for (int j = 0; j < MATRIX_WIDTH; j++)
      if (matrix[i][j]->getCellID() == Cell::ID::DOWNSTAIRS) {
        ret = matrix[i][j];
        break;
      }
  return ret;
}

void Map::loadMap(string filename) {
  printf("DEBUG: Entering map.cpp::filename)\n");
  // open the file to read
  ifstream in(filename, ios::binary);
  // notice the matrix in file is the transpose matrix
  // of the matrix in the window
  for (int j = 0; j < MATRIX_WIDTH; j++)
    for (int i = 0; i < MATRIX_WIDTH; i++) {
      // buffer to read the id of current cell
      Cell::ID id;
      // read the id of current cell
      in.read((char *)&id, sizeof(id));
      // choose what cell to put into the matrix by its id
      matrix[i][j] = getNewCellByID(id, i, j);
    }
  in.close();

  printf("DEBUG: Exiting map.cpp::filename)\n");
}

void Map::saveMap(string filename) {
  printf("DEBUG: Entering map.cpp::filename)\n");
  // open the file to write
  ofstream out(filename, ios::binary);
  // notice the matrix in file is the transpose matrix
  // of the matrix in the window
  for (int j = 0; j < MATRIX_WIDTH; j++)
    for (int i = 0; i < MATRIX_WIDTH; i++) {
      // get the id of the cell
      Cell::ID id = getCellAt(i, j)->getCellID();
      // write the id into the file
      out.write((const char *)&id, sizeof(id));
    }
  out.close();

  printf("DEBUG: Exiting map.cpp::filename)\n");
}

void Map::removeEnemy(Enemy *enemy) {
  printf("DEBUG: Entering map.cpp::*enemy)\n");
  // get enemy position
  int x = enemy->getCurrentX();
  int y = enemy->getCurrentY();
  // remove the enemy in the linked list
  animeCells.remove(enemy);
  enemies.remove(enemy);
  // remove the enemy in the map
  matrix[x][y] = BarrierFactory::getground(x, y);
  // free the memory
  delete enemy;

  printf("DEBUG: Exiting map.cpp::*enemy)\n");
}

void Map::removeDoor(Door *door) {
  printf("DEBUG: Entering map.cpp::*door)\n");
  // get door position
  int x = door->getCurrentX();
  int y = door->getCurrentY();
  // remove the door in the linked list
  doors.remove(door);
  // remove the door in the map
  matrix[x][y] = BarrierFactory::getground(x, y);
  // free the memory
  delete door;

  printf("DEBUG: Exiting map.cpp::*door)\n");
}

void Map::removeItem(Item *item) {
  printf("DEBUG: Entering map.cpp::*item)\n");
  // get item position
  int x = item->getCurrentX();
  int y = item->getCurrentY();
  matrix[x][y] = BarrierFactory::getground(x, y);
  // free the memory
  delete item;

  printf("DEBUG: Exiting map.cpp::*item)\n");
}

Map *Map::copyMap(Map *map) {
  Map *ret = new Map();
  for (int i = 0; i < MATRIX_WIDTH; i++)
    for (int j = 0; j < MATRIX_WIDTH; j++) {
      // get the id of cell
      Cell::ID id = map->getCellAt(i, j)->getCellID();
      // get a new cell by id
      ret->matrix[i][j] = ret->getNewCellByID(id, i, j);
    }
  return ret;
}

Cell *Map::getNewCellByID(Cell::ID id, int x, int y) {
  Cell *ret = nullptr;
  // barrier
  if (id == Cell::ID::GROUND) {
    printf("DEBUG: Entering map.cpp::Cell::ID::GROUND)\n");
    ret = BarrierFactory::getground(x, y);

    printf("DEBUG: Exiting map.cpp::Cell::ID::GROUND)\n");
  } else if (id == Cell::ID::BRICK_WALL) {
    printf("DEBUG: Entering map.cpp::Cell::ID::BRICK_WALL)\n");
    ret = BarrierFactory::getbrick_wall(x, y);

    printf("DEBUG: Exiting map.cpp::Cell::ID::BRICK_WALL)\n");
  } else if (id == Cell::ID::STAR) {
    printf("DEBUG: Entering map.cpp::Cell::ID::STAR)\n");
    ret = BarrierFactory::getstar(x, y);
    animeCells.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::STAR)\n");
  } else if (id == Cell::ID::LAVA) {
    printf("DEBUG: Entering map.cpp::Cell::ID::LAVA)\n");
    ret = BarrierFactory::getlava(x, y);
    animeCells.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::LAVA)\n");
  }

  else if (id == Cell::ID::STONE_LEFT) {
    printf("DEBUG: Entering map.cpp::Cell::ID::STONE_LEFT)\n");
    ret = BarrierFactory::getstone_left(x, y);
    animeCells.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::STONE_LEFT)\n");
  } else if (id == Cell::ID::STONE_RIGHT) {
    printf("DEBUG: Entering map.cpp::Cell::ID::STONE_RIGHT)\n");
    ret = BarrierFactory::getstone_right(x, y);
    animeCells.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::STONE_RIGHT)\n");
  }

  else if (id == Cell::ID::DRAGON_NW) {
    printf("DEBUG: Entering map.cpp::Cell::ID::DRAGON_NW)\n");
    ret = BarrierFactory::getdragon_nw(x, y);
    animeCells.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::DRAGON_NW)\n");
  } else if (id == Cell::ID::DRAGON_N) {
    printf("DEBUG: Entering map.cpp::Cell::ID::DRAGON_N)\n");
    ret = BarrierFactory::getdragon_n(x, y);
    animeCells.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::DRAGON_N)\n");
  } else if (id == Cell::ID::DRAGON_NE) {
    printf("DEBUG: Entering map.cpp::Cell::ID::DRAGON_NE)\n");
    ret = BarrierFactory::getdragon_ne(x, y);
    animeCells.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::DRAGON_NE)\n");
  } else if (id == Cell::ID::DRAGON_W) {
    printf("DEBUG: Entering map.cpp::Cell::ID::DRAGON_W)\n");
    ret = BarrierFactory::getdragon_w(x, y);
    animeCells.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::DRAGON_W)\n");
  } else if (id == Cell::ID::DRAGON_M) {
    printf("DEBUG: Entering map.cpp::Cell::ID::DRAGON_M)\n");
    ret = BarrierFactory::getdragon_m(x, y);
    animeCells.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::DRAGON_M)\n");
  } else if (id == Cell::ID::DRAGON_E) {
    printf("DEBUG: Entering map.cpp::Cell::ID::DRAGON_E)\n");
    ret = BarrierFactory::getdragon_e(x, y);
    animeCells.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::DRAGON_E)\n");
  } else if (id == Cell::ID::DRAGON_SW) {
    printf("DEBUG: Entering map.cpp::Cell::ID::DRAGON_SW)\n");
    ret = BarrierFactory::getdragon_sw(x, y);
    animeCells.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::DRAGON_SW)\n");
  } else if (id == Cell::ID::DRAGON_SE) {
    printf("DEBUG: Entering map.cpp::Cell::ID::DRAGON_SE)\n");
    ret = BarrierFactory::getdragon_se(x, y);
    animeCells.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::DRAGON_SE)\n");
  }
  // doors
  else if (id == Cell::ID::AUTO_DOOR) {
    printf("DEBUG: Entering map.cpp::Cell::ID::AUTO_DOOR)\n");
    ret = BarrierFactory::getauto_door(x, y);
    doors.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::AUTO_DOOR)\n");
  } else if (id == Cell::ID::RED_DOOR) {
    printf("DEBUG: Entering map.cpp::Cell::ID::RED_DOOR)\n");
    ret = BarrierFactory::getred_door(x, y);
    doors.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::RED_DOOR)\n");
  } else if (id == Cell::ID::BLUE_DOOR) {
    printf("DEBUG: Entering map.cpp::Cell::ID::BLUE_DOOR)\n");
    ret = BarrierFactory::getblue_door(x, y);
    doors.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::BLUE_DOOR)\n");
  } else if (id == Cell::ID::YELLOW_DOOR) {
    printf("DEBUG: Entering map.cpp::Cell::ID::YELLOW_DOOR)\n");
    ret = BarrierFactory::getyellow_door(x, y);
    doors.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::YELLOW_DOOR)\n");
  }
  // items
  else if (id == Cell::ID::RED_KEY) {
    printf("DEBUG: Entering map.cpp::Cell::ID::RED_KEY)\n");
    ret = ItemFactory::getred_key(x, y);

    printf("DEBUG: Exiting map.cpp::Cell::ID::RED_KEY)\n");
  } else if (id == Cell::ID::BLUE_KEY) {
    printf("DEBUG: Entering map.cpp::Cell::ID::BLUE_KEY)\n");
    ret = ItemFactory::getblue_key(x, y);

    printf("DEBUG: Exiting map.cpp::Cell::ID::BLUE_KEY)\n");
  } else if (id == Cell::ID::YELLOW_KEY) {
    printf("DEBUG: Entering map.cpp::Cell::ID::YELLOW_KEY)\n");
    ret = ItemFactory::getyellow_key(x, y);

    printf("DEBUG: Exiting map.cpp::Cell::ID::YELLOW_KEY)\n");
  } else if (id == Cell::ID::SUPER_KEY) {
    printf("DEBUG: Entering map.cpp::Cell::ID::SUPER_KEY)\n");
    ret = ItemFactory::getsuper_key(x, y);

    printf("DEBUG: Exiting map.cpp::Cell::ID::SUPER_KEY)\n");
  }

  else if (id == Cell::ID::RED_POTION) {
    printf("DEBUG: Entering map.cpp::Cell::ID::RED_POTION)\n");
    ret = ItemFactory::getred_potion(x, y);

    printf("DEBUG: Exiting map.cpp::Cell::ID::RED_POTION)\n");
  } else if (id == Cell::ID::BLUE_POTION) {
    printf("DEBUG: Entering map.cpp::Cell::ID::BLUE_POTION)\n");
    ret = ItemFactory::getblue_potion(x, y);

    printf("DEBUG: Exiting map.cpp::Cell::ID::BLUE_POTION)\n");
  } else if (id == Cell::ID::SUPER_POTION) {
    printf("DEBUG: Entering map.cpp::Cell::ID::SUPER_POTION)\n");
    ret = ItemFactory::getsuper_potion(x, y);

    printf("DEBUG: Exiting map.cpp::Cell::ID::SUPER_POTION)\n");
  }

  else if (id == Cell::ID::RED_CRYSTAL) {
    printf("DEBUG: Entering map.cpp::Cell::ID::RED_CRYSTAL)\n");
    ret = ItemFactory::getred_crystal(x, y);

    printf("DEBUG: Exiting map.cpp::Cell::ID::RED_CRYSTAL)\n");
  } else if (id == Cell::ID::BLUE_CRYSTAL) {
    printf("DEBUG: Entering map.cpp::Cell::ID::BLUE_CRYSTAL)\n");
    ret = ItemFactory::getblue_crystal(x, y);

    printf("DEBUG: Exiting map.cpp::Cell::ID::BLUE_CRYSTAL)\n");
  }

  else if (id == Cell::ID::SWORD_PRIMARY) {
    printf("DEBUG: Entering map.cpp::Cell::ID::SWORD_PRIMARY)\n");
    ret = ItemFactory::getsword_primary(x, y);

    printf("DEBUG: Exiting map.cpp::Cell::ID::SWORD_PRIMARY)\n");
  } else if (id == Cell::ID::SWORD_MEDIUM) {
    printf("DEBUG: Entering map.cpp::Cell::ID::SWORD_MEDIUM)\n");
    ret = ItemFactory::getsword_medium(x, y);

    printf("DEBUG: Exiting map.cpp::Cell::ID::SWORD_MEDIUM)\n");
  } else if (id == Cell::ID::SWORD_SUPER) {
    printf("DEBUG: Entering map.cpp::Cell::ID::SWORD_SUPER)\n");
    ret = ItemFactory::getsword_super(x, y);

    printf("DEBUG: Exiting map.cpp::Cell::ID::SWORD_SUPER)\n");
  }

  else if (id == Cell::ID::SHIELD_PRIMARY) {
    printf("DEBUG: Entering map.cpp::Cell::ID::SHIELD_PRIMARY)\n");
    ret = ItemFactory::getshield_primary(x, y);

    printf("DEBUG: Exiting map.cpp::Cell::ID::SHIELD_PRIMARY)\n");
  } else if (id == Cell::ID::SHIELD_MEDIUM) {
    printf("DEBUG: Entering map.cpp::Cell::ID::SHIELD_MEDIUM)\n");
    ret = ItemFactory::getshield_medium(x, y);

    printf("DEBUG: Exiting map.cpp::Cell::ID::SHIELD_MEDIUM)\n");
  } else if (id == Cell::ID::SHIELD_SUPER) {
    printf("DEBUG: Entering map.cpp::Cell::ID::SHIELD_SUPER)\n");
    ret = ItemFactory::getshield_super(x, y);

    printf("DEBUG: Exiting map.cpp::Cell::ID::SHIELD_SUPER)\n");
  }

  else if (id == Cell::ID::COIN) {
    printf("DEBUG: Entering map.cpp::Cell::ID::COIN)\n");
    ret = ItemFactory::getcoin(x, y);

    printf("DEBUG: Exiting map.cpp::Cell::ID::COIN)\n");
  } else if (id == Cell::ID::LEVEL_UP) {
    printf("DEBUG: Entering map.cpp::Cell::ID::LEVEL_UP)\n");
    ret = ItemFactory::getlevel_up(x, y);

    printf("DEBUG: Exiting map.cpp::Cell::ID::LEVEL_UP)\n");
  }
  // stairs
  else if (id == Cell::ID::UPSTAIRS) {
    printf("DEBUG: Entering map.cpp::Cell::ID::UPSTAIRS)\n");
    ret = ItemFactory::getupstairs(x, y);

    printf("DEBUG: Exiting map.cpp::Cell::ID::UPSTAIRS)\n");
  } else if (id == Cell::ID::DOWNSTAIRS) {
    printf("DEBUG: Entering map.cpp::Cell::ID::DOWNSTAIRS)\n");
    ret = ItemFactory::getdownstairs(x, y);

    printf("DEBUG: Exiting map.cpp::Cell::ID::DOWNSTAIRS)\n");
  }
  // special
  else if (id == Cell::ID::CROSS) {
    printf("DEBUG: Entering map.cpp::Cell::ID::CROSS)\n");
    ret = ItemFactory::getcross(x, y);

    printf("DEBUG: Exiting map.cpp::Cell::ID::CROSS)\n");
  } else if (id == Cell::ID::FIRE_WAND) {
    printf("DEBUG: Entering map.cpp::Cell::ID::FIRE_WAND)\n");
    ret = ItemFactory::getfire_wand(x, y);

    printf("DEBUG: Exiting map.cpp::Cell::ID::FIRE_WAND)\n");
  } else if (id == Cell::ID::ICE_WAND) {
    printf("DEBUG: Entering map.cpp::Cell::ID::ICE_WAND)\n");
    ret = ItemFactory::getice_wand(x, y);

    printf("DEBUG: Exiting map.cpp::Cell::ID::ICE_WAND)\n");
  } else if (id == Cell::ID::EARTH_WAND) {
    printf("DEBUG: Entering map.cpp::Cell::ID::EARTH_WAND)\n");
    ret = ItemFactory::getearth_wand(x, y);

    printf("DEBUG: Exiting map.cpp::Cell::ID::EARTH_WAND)\n");
  }
  // enemy
  else if (id == Cell::ID::GREEN_SLIME) {
    printf("DEBUG: Entering map.cpp::Cell::ID::GREEN_SLIME)\n");
    ret = EnemyFactory::getgreen_slime(x, y);
    animeCells.push_back(ret);
    enemies.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::GREEN_SLIME)\n");
  } else if (id == Cell::ID::RED_SLIME) {
    printf("DEBUG: Entering map.cpp::Cell::ID::RED_SLIME)\n");
    ret = EnemyFactory::getred_slime(x, y);
    animeCells.push_back(ret);
    enemies.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::RED_SLIME)\n");
  } else if (id == Cell::ID::GHOST_SLIME) {
    printf("DEBUG: Entering map.cpp::Cell::ID::GHOST_SLIME)\n");
    ret = EnemyFactory::getghost_slime(x, y);
    animeCells.push_back(ret);
    enemies.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::GHOST_SLIME)\n");
  } else if (id == Cell::ID::BIG_SLIME) {
    printf("DEBUG: Entering map.cpp::Cell::ID::BIG_SLIME)\n");
    ret = EnemyFactory::getbig_slime(x, y);
    animeCells.push_back(ret);
    enemies.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::BIG_SLIME)\n");
  }

  else if (id == Cell::ID::SMALL_BAT) {
    printf("DEBUG: Entering map.cpp::Cell::ID::SMALL_BAT)\n");
    ret = EnemyFactory::getsmall_bat(x, y);
    animeCells.push_back(ret);
    enemies.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::SMALL_BAT)\n");
  } else if (id == Cell::ID::BIG_BAT) {
    printf("DEBUG: Entering map.cpp::Cell::ID::BIG_BAT)\n");
    ret = EnemyFactory::getbig_bat(x, y);
    animeCells.push_back(ret);
    enemies.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::BIG_BAT)\n");
  } else if (id == Cell::ID::RED_BAT) {
    printf("DEBUG: Entering map.cpp::Cell::ID::RED_BAT)\n");
    ret = EnemyFactory::getred_bat(x, y);
    animeCells.push_back(ret);
    enemies.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::RED_BAT)\n");
  }

  else if (id == Cell::ID::SKELETON) {
    printf("DEBUG: Entering map.cpp::Cell::ID::SKELETON)\n");
    ret = EnemyFactory::getskeleton(x, y);
    animeCells.push_back(ret);
    enemies.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::SKELETON)\n");
  } else if (id == Cell::ID::SKELETON_WARRIOR) {
    printf("DEBUG: Entering map.cpp::Cell::ID::SKELETON_WARRIOR)\n");
    ret = EnemyFactory::getskeleton_warrior(x, y);
    animeCells.push_back(ret);
    enemies.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::SKELETON_WARRIOR)\n");
  } else if (id == Cell::ID::SKELETON_CAPTAIN) {
    printf("DEBUG: Entering map.cpp::Cell::ID::SKELETON_CAPTAIN)\n");
    ret = EnemyFactory::getskeleton_captain(x, y);
    animeCells.push_back(ret);
    enemies.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::SKELETON_CAPTAIN)\n");
  } else if (id == Cell::ID::SKELETON_ARMORED) {
    printf("DEBUG: Entering map.cpp::Cell::ID::SKELETON_ARMORED)\n");
    ret = EnemyFactory::getskeleton_armored(x, y);
    animeCells.push_back(ret);
    enemies.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::SKELETON_ARMORED)\n");
  }

  else if (id == Cell::ID::ORC) {
    printf("DEBUG: Entering map.cpp::Cell::ID::ORC)\n");
    ret = EnemyFactory::getorc(x, y);
    animeCells.push_back(ret);
    enemies.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::ORC)\n");
  } else if (id == Cell::ID::ORC_WARRIOR) {
    printf("DEBUG: Entering map.cpp::Cell::ID::ORC_WARRIOR)\n");
    ret = EnemyFactory::getorc_warrior(x, y);
    animeCells.push_back(ret);
    enemies.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::ORC_WARRIOR)\n");
  }

  else if (id == Cell::ID::WIZARD) {
    printf("DEBUG: Entering map.cpp::Cell::ID::WIZARD)\n");
    ret = EnemyFactory::getwizard(x, y);
    animeCells.push_back(ret);
    enemies.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::WIZARD)\n");
  } else if (id == Cell::ID::RED_WIZARD) {
    printf("DEBUG: Entering map.cpp::Cell::ID::RED_WIZARD)\n");
    ret = EnemyFactory::getred_wizard(x, y);
    animeCells.push_back(ret);
    enemies.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::RED_WIZARD)\n");
  }

  else if (id == Cell::ID::MAGE) {
    printf("DEBUG: Entering map.cpp::Cell::ID::MAGE)\n");
    ret = EnemyFactory::getmage(x, y);
    animeCells.push_back(ret);
    enemies.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::MAGE)\n");
  } else if (id == Cell::ID::RED_MAGE) {
    printf("DEBUG: Entering map.cpp::Cell::ID::RED_MAGE)\n");
    ret = EnemyFactory::getred_mage(x, y);
    animeCells.push_back(ret);
    enemies.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::RED_MAGE)\n");
  }

  else if (id == Cell::ID::HEAD_MONSTER) {
    printf("DEBUG: Entering map.cpp::Cell::ID::HEAD_MONSTER)\n");
    ret = EnemyFactory::gethead_monster(x, y);
    animeCells.push_back(ret);
    enemies.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::HEAD_MONSTER)\n");
  }

  else if (id == Cell::ID::DUAL_BLADE) {
    printf("DEBUG: Entering map.cpp::Cell::ID::DUAL_BLADE)\n");
    ret = EnemyFactory::getdual_blade(x, y);
    animeCells.push_back(ret);
    enemies.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::DUAL_BLADE)\n");
  }

  else if (id == Cell::ID::GOLDEN_GUARD) {
    printf("DEBUG: Entering map.cpp::Cell::ID::GOLDEN_GUARD)\n");
    ret = EnemyFactory::getgolden_guard(x, y);
    animeCells.push_back(ret);
    enemies.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::GOLDEN_GUARD)\n");
  } else if (id == Cell::ID::BLUE_GUARD) {
    printf("DEBUG: Entering map.cpp::Cell::ID::BLUE_GUARD)\n");
    ret = EnemyFactory::getblue_guard(x, y);
    animeCells.push_back(ret);
    enemies.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::BLUE_GUARD)\n");
  } else if (id == Cell::ID::RED_GUARD) {
    printf("DEBUG: Entering map.cpp::Cell::ID::RED_GUARD)\n");
    ret = EnemyFactory::getred_guard(x, y);
    animeCells.push_back(ret);
    enemies.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::RED_GUARD)\n");
  }

  else if (id == Cell::ID::RED_KNIGHT) {
    printf("DEBUG: Entering map.cpp::Cell::ID::RED_KNIGHT)\n");
    ret = EnemyFactory::getred_knight(x, y);
    animeCells.push_back(ret);
    enemies.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::RED_KNIGHT)\n");
  } else if (id == Cell::ID::YELLOW_KNIGHT) {
    printf("DEBUG: Entering map.cpp::Cell::ID::YELLOW_KNIGHT)\n");
    ret = EnemyFactory::getyellow_knight(x, y);
    animeCells.push_back(ret);
    enemies.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::YELLOW_KNIGHT)\n");
  } else if (id == Cell::ID::BLUE_KNIGHT) {
    printf("DEBUG: Entering map.cpp::Cell::ID::BLUE_KNIGHT)\n");
    ret = EnemyFactory::getblue_knight(x, y);
    animeCells.push_back(ret);
    enemies.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::BLUE_KNIGHT)\n");
  } else if (id == Cell::ID::ARMORED_KNIGHT) {
    printf("DEBUG: Entering map.cpp::Cell::ID::ARMORED_KNIGHT)\n");
    ret = EnemyFactory::getarmored_knight(x, y);
    animeCells.push_back(ret);
    enemies.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::ARMORED_KNIGHT)\n");
  } else if (id == Cell::ID::GHOST_KNIGHT) {
    printf("DEBUG: Entering map.cpp::Cell::ID::GHOST_KNIGHT)\n");
    ret = EnemyFactory::getghost_knight(x, y);
    animeCells.push_back(ret);
    enemies.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::GHOST_KNIGHT)\n");
  } else if (id == Cell::ID::GHOST_KNIGHT_CAPTAIN) {
    printf("DEBUG: Entering map.cpp::Cell::ID::GHOST_KNIGHT_CAPTAIN)\n");
    ret = EnemyFactory::getghost_knight_captain(x, y);
    animeCells.push_back(ret);
    enemies.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::GHOST_KNIGHT_CAPTAIN)\n");
  }

  else if (id == Cell::ID::GREEN_GHOST) {
    printf("DEBUG: Entering map.cpp::Cell::ID::GREEN_GHOST)\n");
    ret = EnemyFactory::getgreen_ghost(x, y);
    animeCells.push_back(ret);
    enemies.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::GREEN_GHOST)\n");
  }

  else if (id == Cell::ID::RED_LORD) {
    printf("DEBUG: Entering map.cpp::Cell::ID::RED_LORD)\n");
    ret = EnemyFactory::getred_lord(x, y);
    animeCells.push_back(ret);
    enemies.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::RED_LORD)\n");
  } else if (id == Cell::ID::GHOST_LORD) {
    printf("DEBUG: Entering map.cpp::Cell::ID::GHOST_LORD)\n");
    ret = EnemyFactory::getghost_lord(x, y);
    animeCells.push_back(ret);
    enemies.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::GHOST_LORD)\n");
  } else if (id == Cell::ID::DRAGON) {
    printf("DEBUG: Entering map.cpp::Cell::ID::DRAGON)\n");
    ret = EnemyFactory::getdragon(x, y);
    animeCells.push_back(ret);
    enemies.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::DRAGON)\n");
  }
  // NPC
  else if (id == Cell::ID::FAIRY) {
    printf("DEBUG: Entering map.cpp::Cell::ID::FAIRY)\n");
    ret = NPCFactory::getfairy(x, y);
    animeCells.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::FAIRY)\n");
  } else if (id == Cell::ID::PRINCESS) {
    printf("DEBUG: Entering map.cpp::Cell::ID::PRINCESS)\n");
    ret = NPCFactory::getprincess(x, y);
    animeCells.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::PRINCESS)\n");
  } else if (id == Cell::ID::OLD_MAN_LEVEL5) {
    printf("DEBUG: Entering map.cpp::Cell::ID::OLD_MAN_LEVEL5)\n");
    ret = NPCFactory::getold_man_level5(x, y);
    animeCells.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::OLD_MAN_LEVEL5)\n");
  } else if (id == Cell::ID::OLD_MAN_LEVEL13) {
    printf("DEBUG: Entering map.cpp::Cell::ID::OLD_MAN_LEVEL13)\n");
    ret = NPCFactory::getold_man_level13(x, y);
    animeCells.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::OLD_MAN_LEVEL13)\n");
  } else if (id == Cell::ID::STONE_LEVEL3) {
    printf("DEBUG: Entering map.cpp::Cell::ID::STONE_LEVEL3)\n");
    ret = NPCFactory::getstone_level3(x, y);
    animeCells.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::STONE_LEVEL3)\n");
  } else if (id == Cell::ID::STONE_LEVEL11) {
    printf("DEBUG: Entering map.cpp::Cell::ID::STONE_LEVEL11)\n");
    ret = NPCFactory::getstone_level11(x, y);
    animeCells.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::STONE_LEVEL11)\n");
  } else if (id == Cell::ID::KEY_SELLER) {
    printf("DEBUG: Entering map.cpp::Cell::ID::KEY_SELLER)\n");
    ret = NPCFactory::getkey_seller(x, y);
    animeCells.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::KEY_SELLER)\n");
  } else if (id == Cell::ID::KEY_BUYER) {
    printf("DEBUG: Entering map.cpp::Cell::ID::KEY_BUYER)\n");
    ret = NPCFactory::getkey_buyer(x, y);
    animeCells.push_back(ret);

    printf("DEBUG: Exiting map.cpp::Cell::ID::KEY_BUYER)\n");
  }

  return ret;
}