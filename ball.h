#ifndef BALL_H
#define BALL_H

#include <stdlib.h>
#include <vector>

#include "direction.cpp"
#include "point.h"
#include "basket.h"

using namespace std;

class Basket;

class Ball
{
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
  Basket *basket;
  bool inBasket;

  void bounce();
  void bounceBasketLeft();
  void bounceBasketBottom();
  void bounceBasketRight();
  void randomizeDirection();
  int randomizeSpeed();

public:
  Ball(int id, int pos_x, int pos_y, int winWidth, int winHeight, Basket *basket);
  ~Ball();

  void moveBall();
  void moveLeft();
  void moveTop();
  void moveRight();
  void moveBottom();
  void tryCatching();
  void catchToBasket();
  void releaseFromBasket();

  int getPosX();
  int getPosY();
  int getPrevPosX();
  int getPrevPosY();
  int getColor();
  int getSpeed();
  bool getInBasket();
};

#endif
