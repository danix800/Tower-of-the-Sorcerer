
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "Window.h"
#include "GUI.h"
#include "Graph.h"
#include <cstdio>

//------------------------------------------------------------------------------
namespace Graph_lib {

Window::Window(int ww, int hh, const string &title)
    : Fl_Window(ww, hh, title.c_str()), w(ww), h(hh) {
  init();
}

//------------------------------------------------------------------------------

Window::Window(Point xy, int ww, int hh, const string &title)
    : Fl_Window(xy.x, xy.y, ww, hh, title.c_str()), w(ww), h(hh) {
  init();
}

//------------------------------------------------------------------------------

void Window::init() {
  printf("DEBUG: Entering Window.cpp::Window::init\n");
  resizable(this);
  show();

  printf("DEBUG: Exiting Window.cpp::Window::init\n");
}

//------------------------------------------------------------------------------

void Window::draw() {
  printf("DEBUG: Entering Window.cpp::Window::draw\n");
  Fl_Window::draw();
  for (unsigned int i = 0; i < shapes.size(); ++i)
    shapes[i]->draw();

  printf("DEBUG: Exiting Window.cpp::Window::draw\n");
}

//------------------------------------------------------------------------------

void Window::attach(Widget &w) {
  printf("DEBUG: Entering Window.cpp::w)\n");
  begin();         // FTLK: begin attaching new Fl_Wigets to this window
  w.attach(*this); // let the Widget create its Fl_Wigits
  end();           // FTLK: stop attaching new Fl_Wigets to this window

  printf("DEBUG: Exiting Window.cpp::w)\n");
}

//------------------------------------------------------------------------------

void Window::detach(Widget &b) {
  printf("DEBUG: Entering Window.cpp::b)\n");
  b.hide();

  printf("DEBUG: Exiting Window.cpp::b)\n");
}

//------------------------------------------------------------------------------

void Window::detach(Shape &s)
// guess that the last attached will be first released
{
  for (unsigned int i = shapes.size(); 0 < i; --i)
    if (shapes[i - 1] == &s)
      shapes.erase(shapes.begin() + (i - 1));
}

//------------------------------------------------------------------------------

void Window::put_on_top(Shape &p) {
  printf("DEBUG: Entering Window.cpp::p)\n");
  for (unsigned int i = 0; i < shapes.size(); ++i) {
    if (&p == shapes[i]) {
      for (++i; i < shapes.size(); ++i)
        shapes[i - 1] = shapes[i];
      shapes[shapes.size() - 1] = &p;
      return;
    }
  }

  printf("DEBUG: Exiting Window.cpp::p)\n");
}

//------------------------------------------------------------------------------

int gui_main() {
  printf("DEBUG: Entering Window.cpp::gui_main\n");
  return Fl::run();

  printf("DEBUG: Exiting Window.cpp::gui_main\n");
}

//------------------------------------------------------------------------------

}; // namespace Graph_lib
