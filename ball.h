#ifndef BALL_H
#define BALL_H

#include <stdlib.h>
#include "direction.cpp"

class Ball {
  int id;
  int pos_x;
  int pos_y;
  int speed;
  Direction direction;
  int winHeight;
  int winWidth;

  public:
    Ball(int id, int pos_x, int pos_y, int winWidth, int winHeight); 
    ~Ball();

    void moveBall();   
    void changeDirection();
};

#endif

