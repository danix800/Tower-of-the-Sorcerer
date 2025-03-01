#include "timer.h"
#include "../resourceManager/resourceManager.h"
#include <cstdio>

Timer::Timer(double interval, Fl_Timeout_Handler callback)
    : intervalTime(interval), running(false), callback(callback) {}

Timer::~Timer() {}

void Timer::start() {
  printf("DEBUG: Entering timer.cpp::Timer::start\n");
  if (!running) {
    running = true;
    Fl::add_timeout(intervalTime, callback, this);
  }

  printf("DEBUG: Exiting timer.cpp::Timer::start\n");
}

void Timer::stop() {
  printf("DEBUG: Entering timer.cpp::Timer::stop\n");
  if (running) {
    running = false;
    Fl::remove_timeout(callback, this);
  }

  printf("DEBUG: Exiting timer.cpp::Timer::stop\n");
}

void Timer::reset() {
  printf("DEBUG: Entering timer.cpp::Timer::reset\n");
  this->stop();
  this->start();

  printf("DEBUG: Exiting timer.cpp::Timer::reset\n");
}
