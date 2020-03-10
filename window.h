#ifndef WINDOW_H
#define WINDOW_H

#include <vector>
#include <ncurses.h>
#include "ball.h"

using namespace std;

class Window {
  WINDOW* window;
  int width;
  int height;

  void drawArea();
  void drawBall(int pos_x, int pos_y);
  
  public:
    Window();
    ~Window();
    void reload(vector<Ball*> balls);
    int getWidth();
    int getHeight();
};

#endif
