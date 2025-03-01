
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "GUI.h"
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <cstdio>

namespace Graph_lib {

//------------------------------------------------------------------------------

void Button::attach(Window &win) {
  printf("DEBUG: Entering GUI.cpp::win)\n");
  pw = new Fl_Button(loc.x, loc.y, width, height, label.c_str());
  pw->callback(reinterpret_cast<Fl_Callback *>(do_it), &win); // pass the window
  own = &win;

  printf("DEBUG: Exiting GUI.cpp::win)\n");
}

//------------------------------------------------------------------------------

int In_box::get_int() {
  printf("DEBUG: Entering GUI.cpp::In_box::get_int\n");
  Fl_Input &pi = reference_to<Fl_Input>(pw);
  // return atoi(pi.value());
  const char *p = pi.value();
  if (!isdigit(p[0]))
    return -999999;
  return atoi(p);

  printf("DEBUG: Exiting GUI.cpp::In_box::get_int\n");
}

//------------------------------------------------------------------------------

void In_box::attach(Window &win) {
  printf("DEBUG: Entering GUI.cpp::win)\n");
  pw = new Fl_Input(loc.x, loc.y, width, height, label.c_str());
  own = &win;

  printf("DEBUG: Exiting GUI.cpp::win)\n");
}

//------------------------------------------------------------------------------

void Out_box::put(const string &s) {
  printf("DEBUG: Entering GUI.cpp::s)\n");
  reference_to<Fl_Output>(pw).value(s.c_str());

  printf("DEBUG: Exiting GUI.cpp::s)\n");
}

//------------------------------------------------------------------------------

void Out_box::attach(Window &win) {
  printf("DEBUG: Entering GUI.cpp::win)\n");
  pw = new Fl_Output(loc.x, loc.y, width, height, label.c_str());
  own = &win;

  printf("DEBUG: Exiting GUI.cpp::win)\n");
}

//------------------------------------------------------------------------------

int Menu::attach(Button &b) {
  printf("DEBUG: Entering GUI.cpp::b)\n");
  b.width = width;
  b.height = height;

  switch (k) {
  case horizontal:
    b.loc = Point(loc.x + offset, loc.y);
    offset += b.width;
    break;
  case vertical:
    b.loc = Point(loc.x, loc.y + offset);
    offset += b.height;
    break;
  }
  selection.push_back(b); // b is NOT OWNED: pass by reference
  return int(selection.size() - 1);

  printf("DEBUG: Exiting GUI.cpp::b)\n");
}

//------------------------------------------------------------------------------

int Menu::attach(Button *p) {
  printf("DEBUG: Entering GUI.cpp::p)\n");
  Button &b = *p;
  b.width = width;
  b.height = height;

  switch (k) {
  case horizontal:
    b.loc = Point(loc.x + offset, loc.y);
    offset += b.width;
    break;
  case vertical:
    b.loc = Point(loc.x, loc.y + offset);
    offset += b.height;
    break;
  }
  selection.push_back(&b); // b is OWNED: pass by pointer
  return int(selection.size() - 1);

  printf("DEBUG: Exiting GUI.cpp::p)\n");
}

//------------------------------------------------------------------------------

}; // namespace Graph_lib