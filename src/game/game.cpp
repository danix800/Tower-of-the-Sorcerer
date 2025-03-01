#include "game.h"
#include "../resourceManager/resourceManager.h"
#include <cstdio>

Game::Game() {
  // register game
  ResourceManager::registerGame(this);
  // load all resource for the game
  ResourceManager::loadResources();

  // initialize members
  Anime_Timer = new Timer(ANIME_CLK, Game::handleAnime);
  Status_Timer = new Timer(STATUS_CLK, Game::handleStatus);
  dataManager = new DataManager(this);
  viewManager = new ViewManager(this);
  // set game state
  state = MAIN_MENU;
}

Game::~Game() {
  // stop timer
  Anime_Timer->stop();
  Status_Timer->stop();
  // free members
  delete viewManager;
  delete dataManager;
  delete Anime_Timer;
  delete Status_Timer;
  // free resources
  ResourceManager::freeResources();
}

Game::GameState Game::getState() {
  printf("DEBUG: Entering game.cpp::Game::getState\n");
  return state;

  printf("DEBUG: Exiting game.cpp::Game::getState\n");
}

int Game::start() {
  printf("DEBUG: Entering game.cpp::Game::start\n");
  // play the background music
  ResourceManager::playBGM(START_MUSIC);
  // show the main menu
  showMainMenu();
  // print the status
  printStatus("游戏开始");
  return Fl::run();

  printf("DEBUG: Exiting game.cpp::Game::start\n");
}

void Game::showMainMenu() {
  printf("DEBUG: Entering game.cpp::Game::showMainMenu\n");
  viewManager->showMainMenu();
  stopAnime();
  this->state = MAIN_MENU;
  // update bgm
  ResourceManager::playBGM();

  printf("DEBUG: Exiting game.cpp::Game::showMainMenu\n");
}

void Game::newGame() {
  printf("DEBUG: Entering game.cpp::Game::newGame\n");
  // initialize the game map
  // if it's a new game, then init the maps with new maps
  dataManager->setMaps(ResourceManager::New_Maps);
  // init data
  dataManager->initGameData();
  // init game
  initGame();
  // print the status
  printStatus("开始新游戏");

  printf("DEBUG: Exiting game.cpp::Game::newGame\n");
}

void Game::loadGame() {
  printf("DEBUG: Entering game.cpp::Game::loadGame\n");
  // initialize the game map
  // if it's a load game, then init the maps with saved maps
  dataManager->setMaps(ResourceManager::Saved_Maps);
  // load data
  dataManager->loadHeroInfo();
  // init game
  initGame();
  // print the status
  printStatus("加载游戏存档");

  printf("DEBUG: Exiting game.cpp::Game::loadGame\n");
}

void Game::initGame() {
  printf("DEBUG: Entering game.cpp::Game::initGame\n");
  // initialize the scene
  drawScene(dataManager->getMap());
  updateInfo();
  viewManager->drawHero(dataManager->getHero());
  // start the timer
  Anime_Timer->start();
  // start the game
  viewManager->startPlaying();
  // set the game state
  this->state = PLAYING;
  // update bgm
  ResourceManager::playBGM(dataManager->getTowerLevel());

  printf("DEBUG: Exiting game.cpp::Game::initGame\n");
}

void Game::moveHero(int keyCode) {
  printf("DEBUG: Entering game.cpp::keyCode)\n");
  // find the direction
  Hero::Direction direction;
  if (keyCode == KEY_W || keyCode == KEY_UP)
    direction = Hero::UP;
  else if (keyCode == KEY_S || keyCode == KEY_DOWN)
    direction = Hero::DOWN;
  else if (keyCode == KEY_A || keyCode == KEY_LEFT)
    direction = Hero::LEFT;
  else if (keyCode == KEY_D || keyCode == KEY_RIGHT)
    direction = Hero::RIGHT;
  // move the hero
  dataManager->moveHero(direction);
  // if the hero can move, redraw the hero
  Hero *hero = dataManager->getHero();
  if (hero->canMove())
    viewManager->drawHero(hero);

  printf("DEBUG: Exiting game.cpp::keyCode)\n");
}

void Game::stopHero() {
  printf("DEBUG: Entering game.cpp::Game::stopHero\n");
  // stop the move of hero
  dataManager->stopHero();
  // if the hero can move, redraw the hero
  Hero *hero = dataManager->getHero();
  if (hero->canMove())
    viewManager->drawHero(hero);

  printf("DEBUG: Exiting game.cpp::Game::stopHero\n");
}

void Game::drawCell(Cell *cell) {
  printf("DEBUG: Entering game.cpp::*cell)\n");
  viewManager->drawCell(cell);

  printf("DEBUG: Exiting game.cpp::*cell)\n");
}

void Game::drawScene(Map *map) {
  printf("DEBUG: Entering game.cpp::*map)\n");
  viewManager->drawScene(dataManager->getMap());
  viewManager->drawHero(dataManager->getHero());

  printf("DEBUG: Exiting game.cpp::*map)\n");
}

void Game::printStatus(string message) {
  printf("DEBUG: Entering game.cpp::message)\n");
  // print status
  viewManager->printStatus(message);
  // reset the timer to show the message
  Status_Timer->reset();

  printf("DEBUG: Exiting game.cpp::message)\n");
}

void Game::startAnime() {
  printf("DEBUG: Entering game.cpp::Game::startAnime\n");
  Anime_Timer->start();

  printf("DEBUG: Exiting game.cpp::Game::startAnime\n");
}

void Game::stopAnime() {
  printf("DEBUG: Entering game.cpp::Game::stopAnime\n");
  Anime_Timer->stop();

  printf("DEBUG: Exiting game.cpp::Game::stopAnime\n");
}

void Game::talkToNPC() {
  printf("DEBUG: Entering game.cpp::Game::talkToNPC\n");
  if (viewManager->isTalking())
    stopTalking();
  else {
    TalkingUI *ui = dataManager->talkToNPC();
    viewManager->showTalkingUI(ui);
  }

  printf("DEBUG: Exiting game.cpp::Game::talkToNPC\n");
}

void Game::stopTalking() {
  printf("DEBUG: Entering game.cpp::Game::stopTalking\n");
  if (viewManager->isTalking()) {
    viewManager->removeTalkingUI();
    dataManager->stopTalking();
  }

  printf("DEBUG: Exiting game.cpp::Game::stopTalking\n");
}

void Game::updateInfo() {
  printf("DEBUG: Entering game.cpp::Game::updateInfo\n");
  // update hero info
  viewManager->updateHeroInfo(dataManager->getHero());
  // update tower level
  viewManager->updateTowerLevel(dataManager->getTowerLevel());
  // update key number
  int red = dataManager->getRedKeys();
  int blue = dataManager->getBlueKeys();
  int yellow = dataManager->getYellowKeys();
  viewManager->updateKeys(red, blue, yellow);

  printf("DEBUG: Exiting game.cpp::Game::updateInfo\n");
}

void Game::handleAnime(void *data) {
  printf("DEBUG: Entering game.cpp::*data)\n");
  // get timer
  Timer *timer = (Timer *)data;
  // get game
  Game *game = ResourceManager::game;

  // get enemies
  LinkedList<Cell *> animeCells = game->dataManager->getAnimeCells();
  // draw every enemy
  Cell *cell;
  for (Node<Cell *> *p = animeCells.begin(); p; p = p->getNext()) {
    cell = p->getValue();
    game->drawCell(cell);
    cell->changePhoto();
  }

  // repeat Timer event
  Fl::repeat_timeout(ANIME_CLK, Game::handleAnime, timer);

  printf("DEBUG: Exiting game.cpp::*data)\n");
}

void Game::handleFight(void *data) {
  printf("DEBUG: Entering game.cpp::*data)\n");
  // get timer
  Timer *timer = (Timer *)data;
  // get game
  Game *game = ResourceManager::game;

  // get hero info
  Hero *hero = game->dataManager->getHero();
  Hero::FightState state = hero->getFightState();

  // check whether the timer will continue
  bool wantRepeat = true;
  // modify the fight state of hero
  if (state == Hero::WILL_FIGHT) {
    printf("DEBUG: Entering game.cpp::Hero::WILL_FIGHT)\n");
    game->dataManager->HeroBeginFight();

    printf("DEBUG: Exiting game.cpp::Hero::WILL_FIGHT)\n");
  } else if (state == Hero::FIGHTING) {
    printf("DEBUG: Entering game.cpp::Hero::FIGHTING)\n");
    game->dataManager->HeroStopFight();
    // if hero has stopped fight, then stop the timer
    if (hero->getFightState() == Hero::NO_FIGHT) {
      timer->stop();
      delete timer;
      // don't want repeat Timer event
      wantRepeat = false;
    }

    printf("DEBUG: Exiting game.cpp::Hero::FIGHTING)\n");
  }
  // get the cell that hero is in
  int x = hero->getCurrentX();
  int y = hero->getCurrentY();
  Cell *cell = game->dataManager->getCellAt(x, y);
  // redraw the cell that hero is in
  game->drawCell(cell);
  // update the info panel
  game->updateInfo();
  // redraw the hero
  game->viewManager->drawHero(hero);

  // repeat Timer event
  if (wantRepeat)
    Fl::repeat_timeout(FIGHT_CLK, Game::handleFight, timer);

  printf("DEBUG: Exiting game.cpp::*data)\n");
}

void Game::handleDoorOpen(void *data) {
  printf("DEBUG: Entering game.cpp::*data)\n");
  // get timer
  Timer *timer = (Timer *)data;
  // get game
  Game *game = ResourceManager::game;

  // get the door
  Door *door = game->dataManager->getOpeningDoor();
  // redraw the door
  game->drawCell(door);
  // redraw the hero
  game->viewManager->drawHero(game->dataManager->getHero());
  // change the photo of the door
  if (!door->shownAllPhotos()) {
    door->changePhoto();
    // repeat Timer event
    Fl::repeat_timeout(DOOR_CLK, Game::handleDoorOpen, timer);
  } else {
    // if all the photos have shown, stop the timer
    timer->stop();
    delete timer;
    // get the position of the door
    int x = door->getCurrentX();
    int y = door->getCurrentY();
    // remove the door in the map
    game->dataManager->removeDoor(door);
    // redraw the removed cell
    game->drawCell(game->dataManager->getCellAt(x, y));
  }

  printf("DEBUG: Exiting game.cpp::*data)\n");
}
void Game::handleStatus(void *data) {
  printf("DEBUG: Entering game.cpp::*data)\n");
  // get timer
  Timer *timer = (Timer *)data;
  // get game
  Game *game = ResourceManager::game;

  // clear the status bar message
  game->viewManager->printStatus("");
  // stop the timer
  game->Status_Timer->stop();

  printf("DEBUG: Exiting game.cpp::*data)\n");
}

void Game::transportTo(int dst) {
  printf("DEBUG: Entering game.cpp::dst)\n");
  dataManager->transportTo(dst);

  printf("DEBUG: Exiting game.cpp::dst)\n");
}

int Game::getHighestLevel() {
  printf("DEBUG: Entering game.cpp::Game::getHighestLevel\n");
  return dataManager->getHighestLevel();

  printf("DEBUG: Exiting game.cpp::Game::getHighestLevel\n");
}

Hero *Game::getHero() { return dataManager->getHero(); }

LinkedList<Cell *> Game::getEnemies() { return dataManager->getEnemies(); }

ViewManager *Game::getMainWindow() { return viewManager; }

void Game::transaction(Fl_Widget *widget, void *data) {
  printf("DEBUG: Entering game.cpp::*data)\n");
  // get the button and game
  TradeButton *button = (TradeButton *)widget;
  Game *game = ResourceManager::game;
  // get the transaction info
  TradeButton::Currency currency = button->getCurrency();
  TradeButton::Goods goods = button->getGoods();
  int cost = button->getCostAmount();
  int gain = button->getGainAmount();
  // modify the data
  game->dataManager->transaction(currency, goods, cost, gain);
  // update the infoPanel
  game->updateInfo();
  // print the status
  game->printStatus(button->getText());

  printf("DEBUG: Exiting game.cpp::*data)\n");
}

void Game::startNewGame(Fl_Widget *widget, void *data) {
  printf("DEBUG: Entering game.cpp::*data)\n");
  // get the game
  Game *game = ResourceManager::game;
  // start a new game
  if (game->state == MAIN_MENU && !game->viewManager->isUIShowing())
    game->newGame();

  printf("DEBUG: Exiting game.cpp::*data)\n");
}

void Game::startLoadGame(Fl_Widget *widget, void *data) {
  printf("DEBUG: Entering game.cpp::*data)\n");
  // get the game
  Game *game = ResourceManager::game;
  // start a load game
  if (game->state == MAIN_MENU && !game->viewManager->isUIShowing())
    game->loadGame();

  printf("DEBUG: Exiting game.cpp::*data)\n");
}

void Game::musicControl(Fl_Widget *widget, void *data) {
  printf("DEBUG: Entering game.cpp::*data)\n");
  // control signal
  static bool isPlaying = true;
  // store the control button
  static ControlButton *button = nullptr;

  // get the game
  Game *game = ResourceManager::game;
  // record the button for the first call
  if (!button) {
    printf("DEBUG: Entering game.cpp::\n");
    button = (ControlButton *)widget;
    return;

    printf("DEBUG: Exiting game.cpp::\n");
  }

  if (isPlaying) {
    // stop the bgm
    isPlaying = false;
    ResourceManager::playBGM(STOP_MUSIC);
    // change the icon
    button->image(ResourceManager::MusicOff);
    button->redraw();
    // print the status
    game->printStatus("关闭音乐");
  } else {
    // start the bgm
    isPlaying = true;
    ResourceManager::playBGM(START_MUSIC);
    ResourceManager::playBGM(game->dataManager->getTowerLevel());
    // change the icon
    button->image(ResourceManager::MusicOn);
    button->redraw();
    // print the status
    game->printStatus("播放音乐");
  }

  printf("DEBUG: Exiting game.cpp::*data)\n");
}

void Game::saveGame(Fl_Widget *widget, void *data) {
  printf("DEBUG: Entering game.cpp::*data)\n");
  // get the game
  Game *game = ResourceManager::game;
  // save game data
  if (game->state == PLAYING && game->dataManager->getHero()->canMove())
    game->dataManager->saveGameData();

  printf("DEBUG: Exiting game.cpp::*data)\n");
}

void Game::goMainMenu(Fl_Widget *widget, void *data) {
  printf("DEBUG: Entering game.cpp::*data)\n");
  // get the game
  Game *game = ResourceManager::game;
  // go to the main menu
  if (game->state == PLAYING && !game->viewManager->isUIShowing() &&
      game->dataManager->getHero()->canMove()) {
    game->showMainMenu();
    // print the status
    game->printStatus("回到主菜单");
  }

  printf("DEBUG: Exiting game.cpp::*data)\n");
}

void Game::openHelpDoc(Fl_Widget *widget, void *data) {
  printf("DEBUG: Entering game.cpp::*data)\n");
  // store the UI
  static HelpPanel *help = nullptr;

  // get the game
  Game *game = ResourceManager::game;
  // check whether the ESC key is pressed
  bool ESC_Pressed = (Fl::event_key() == KEY_ESC);

  // if the ui is showing, close the help UI
  if (help != nullptr) {
    printf("DEBUG: Entering game.cpp::nullptr)\n");
    game->hideGivenUI(help);
    help = nullptr;
    game->printStatus("关闭帮助面板");

    printf("DEBUG: Exiting game.cpp::nullptr)\n");
  }
  // if the ESC is not pressed
  // and no UI is showing
  // open the UI
  else if (!ESC_Pressed && !game->viewManager->isUIShowing() &&
           game->dataManager->getHero()->canMove()) {
    help = new HelpPanel();
    game->showGivenUI(help);
    game->printStatus("打开帮助面板");
  }

  printf("DEBUG: Exiting game.cpp::*data)\n");
}

void Game::openTransportUI(Fl_Widget *widget, void *data) {
  printf("DEBUG: Entering game.cpp::*data)\n");
  // store the UI
  static TransportPanel *ui = nullptr;

  // get the game
  Game *game = ResourceManager::game;
  // check whether the ESC key is pressed
  bool ESC_Pressed = Fl::event_key() == KEY_ESC;

  if (game->state == PLAYING) {
    // if the ui is showing, close the UI
    if (ui != nullptr) {
      printf("DEBUG: Entering game.cpp::nullptr)\n");
      game->hideGivenUI(ui);
      ui = nullptr;
      game->printStatus("关闭传送面板");

      printf("DEBUG: Exiting game.cpp::nullptr)\n");
    }
    // if the ESC is not pressed
    // and no UI is showing
    // open the UI
    else if (!ESC_Pressed && !game->viewManager->isUIShowing() &&
             game->dataManager->getHero()->canMove()) {
      ui = new TransportPanel();
      game->showGivenUI(ui);
      game->printStatus("打开传送面板");
    }
  }

  printf("DEBUG: Exiting game.cpp::*data)\n");
}

void Game::openWinUI(Fl_Widget *widget, void *data) {
  printf("DEBUG: Entering game.cpp::*data)\n");
  // store the UI
  static WinUI *ui = nullptr;

  // get the game
  Game *game = ResourceManager::game;

  // if the ui is showing, close the UI
  if (ui != nullptr) {
    printf("DEBUG: Entering game.cpp::nullptr)\n");
    game->hideGivenUI(ui);
    ui = nullptr;
    Game::goMainMenu(nullptr, nullptr);

    printf("DEBUG: Exiting game.cpp::nullptr)\n");
  }
  // else, open the UI
  else {
    ui = new WinUI();
    game->showGivenUI(ui);
    game->printStatus("游戏胜利");
  }

  printf("DEBUG: Exiting game.cpp::*data)\n");
}

void Game::openMonsterBook(Fl_Widget *widget, void *data) {
  printf("DEBUG: Entering game.cpp::*data)\n");
  // store the UI
  static BookPanel *book = nullptr;

  // get the game
  Game *game = ResourceManager::game;
  // check whether the ESC key is pressed
  bool ESC_Pressed = Fl::event_key() == KEY_ESC;

  if (game->state == PLAYING) {
    // if the ui is showing, close the UI
    if (book != nullptr) {
      printf("DEBUG: Entering game.cpp::nullptr)\n");
      game->hideGivenUI(book);
      book = nullptr;
      game->printStatus("关闭怪物图鉴");

      printf("DEBUG: Exiting game.cpp::nullptr)\n");
    }
    // if the ESC is not pressed
    // and no UI is showing
    // open the UI
    else if (!ESC_Pressed && !game->viewManager->isUIShowing() &&
             game->dataManager->getHero()->canMove()) {
      book = new BookPanel(game->dataManager->getEnemies());
      game->showGivenUI(book);
      game->printStatus("打开怪物图鉴");
    }
  }

  printf("DEBUG: Exiting game.cpp::*data)\n");
}

void Game::showGivenUI(Fl_Widget *ui) {
  printf("DEBUG: Entering game.cpp::*ui)\n");
  // add the ui into the window
  viewManager->add(ui);
  viewManager->setUIShowing(true);
  // stop the anime and hero
  if (state == PLAYING) {
    printf("DEBUG: Entering game.cpp::PLAYING)\n");
    stopAnime();
    dataManager->getHero()->setWaiting(true);

    printf("DEBUG: Exiting game.cpp::PLAYING)\n");
  }
  // redraw the UI
  ui->redraw();

  printf("DEBUG: Exiting game.cpp::*ui)\n");
}

void Game::hideGivenUI(Fl_Widget *ui) {
  printf("DEBUG: Entering game.cpp::*ui)\n");
  // remove and free the ui
  viewManager->remove(ui);
  viewManager->setUIShowing(false);
  delete ui;
  // restart the anime and let the hero move
  if (state == PLAYING) {
    printf("DEBUG: Entering game.cpp::PLAYING)\n");
    startAnime();
    dataManager->getHero()->setWaiting(false);

    printf("DEBUG: Exiting game.cpp::PLAYING)\n");
  }
  // redraw the window
  viewManager->redraw();

  printf("DEBUG: Exiting game.cpp::*ui)\n");
}
