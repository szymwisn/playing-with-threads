#ifndef BALL_H
#define BALL_H

#include <stdlib.h>
#include <vector>

#include "direction.cpp"

using namespace std;

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
  bool inBasket;

  void bounce();
  void randomizeDirection();

  public:
    Ball(int id, int pos_x, int pos_y, int winWidth, int winHeight); 
    ~Ball();

    void moveBall();   
    void catchInBasket();
    void removeFromBasket();
    void moveInBasket(int horizontal_change, int vertical_change);
    
    int getPosX();
    int getPosY();
    int getPrevPosX();
    int getPrevPosY();
    int getColor();
    int getSpeed();
    bool getInBasket();
};

#endif
