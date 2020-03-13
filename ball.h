#ifndef BALL_H
#define BALL_H

#include <stdlib.h>
#include "direction.cpp"

class Ball {
  int id;
  int pos_x;
  int pos_y;
  int prev_pos_x;
  int prev_pos_y;
  int speed;
  int winWidth;
  int winHeight;
  Direction direction;
  bool directionChanged;
  int color;

  public:
    Ball(int id, int pos_x, int pos_y, int winWidth, int winHeight); 
    ~Ball();

    void moveBall();   
    void bounce();
    void randomizeDirection();
    int getPosX();
    int getPosY();
    int getPrevPosX();
    int getPrevPosY();
    int getColor();
    int getSpeed();
};

#endif
