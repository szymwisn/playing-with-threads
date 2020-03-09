#ifndef WINDOW_H
#define WINDOW_H

#include <ncurses.h>

class Window {
  WINDOW* window;
  int width;
  int height;

  public:
    Window();
    ~Window();
    void drawArea();
    void drawBall(int pos_x, int pos_y);
    void reload();
};

#endif

