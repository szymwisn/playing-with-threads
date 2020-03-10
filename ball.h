#ifndef BALL_H
#define BALL_H

#include <stdlib.h>
#include "direction.cpp"

class Ball {
  int id;
  int pos_x;
  int pos_y;
  int speed;
  int winWidth;
  int winHeight;
  Direction direction;

  public:
    Ball(int id, int pos_x, int pos_y, int winWidth, int winHeight); 
    ~Ball();

    void moveBall();   
    void changeDirection();
    int getPosX();
    int getPosY();
};

#endif
