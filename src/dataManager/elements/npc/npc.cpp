#include "npc.h"
#include <cstdio>

NPC::NPC(ID id, TalkingUI *ui, string name, string words)
    : Cell(id, Type::NPC), talkingUI(ui), name(name), words(words) {}

NPC::~NPC() {}

TalkingUI *NPC::getTalkingUI() { return talkingUI; }

string NPC::getName() {
  printf("DEBUG: Entering npc.cpp::NPC::getName\n");
  return " " + name;

  printf("DEBUG: Exiting npc.cpp::NPC::getName\n");
}

string NPC::getWords() {
  printf("DEBUG: Entering npc.cpp::NPC::getWords\n");
  return "　　" + words;

  printf("DEBUG: Exiting npc.cpp::NPC::getWords\n");
}