#ifndef WINDOW_H
#define WINDOW_H

#include <vector>
#include <ncurses.h>

#include "ball.h"
#include "basket.h"

using namespace std;

class Window {
  WINDOW* window;
  int width;
  int height;

  void drawArea();
  void drawBall(Ball* ball);
  void drawBasket(Basket* basket);
  
  public:
    Window();
    ~Window();
    void reload(vector<Ball*> balls, Basket* basket);
    int getWidth();
    int getHeight();
    WINDOW* getWindow();
};

#endif
