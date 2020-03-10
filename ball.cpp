#include "ball.h"

Ball::Ball(int id, int pos_x, int pos_y, int winWidth, int winHeight) {
  this->id = id;
  this->pos_x = pos_x;
  this->pos_y = pos_y;
  this->speed = rand() % 4 + 1;
  this->direction = Direction::TOP;
  this->winWidth = winWidth;
  this->winHeight = winHeight;
}

Ball::~Ball() {}

int Ball::getPosX() {
  return this->pos_x;
}

int Ball::getPosY() {
  return this->pos_y;
}

void Ball::moveBall() {
  do { 
    this->changeDirection();

    switch(this->direction) {
      case Direction::TOP:
        this->pos_y -= 1;
        break; 
      case Direction::TOP_RIGHT:
        this->pos_y -= 1 * this->speed;
        this->pos_x += 1 * this->speed;
        break;
      case Direction::RIGHT:
        this->pos_x += 1 * this->speed;
        break;
      case Direction::BOTTOM_RIGHT:
        this->pos_x += 1 * this->speed;
        this->pos_y += 1 * this->speed;
        break;
      case Direction::BOTTOM:
        this->pos_y += 1 * this->speed;
        break;
      case Direction::BOTTOM_LEFT:
        this->pos_x -= 1 * this->speed;
        this->pos_y += 1 * this->speed;
        break;
      case Direction::LEFT:
        this->pos_x -= 1 * this->speed;
        break;
      case Direction:: TOP_LEFT:
        this->pos_x -= 1 * this->speed;
        this->pos_y -= 1 * this->speed;
        break;
    } 
  } while(true);
}

void Ball::changeDirection() {
  // top wall
  if (this->pos_y == 0) {
    switch(this->direction) {
      case Direction::TOP:
        this->direction = Direction::BOTTOM;
        break; 
      case Direction::TOP_RIGHT:
        this->direction = Direction::BOTTOM_RIGHT;
        break;
      case Direction:: TOP_LEFT:
        this->direction = Direction::BOTTOM_LEFT;
        break;   
    }
  }

  // right wall
  if (this->pos_x == this->winWidth) {
    switch(this->direction) {
      case Direction::TOP_RIGHT:
        this->direction = Direction::TOP_LEFT;
        break;
      case Direction::RIGHT:
        this->direction = Direction::LEFT;
        break;
      case Direction::BOTTOM_RIGHT:
        this->direction = Direction::BOTTOM_LEFT;
        break;
    }
  } 

  // bottom wall
  if (this->pos_y == this->winHeight) {
    switch(this->direction) {
      case Direction::BOTTOM_RIGHT:
        this->direction = Direction::TOP_RIGHT;
        break;
      case Direction::BOTTOM:
        this->direction = Direction::TOP;
        break;
      case Direction::BOTTOM_LEFT:
        this->direction = Direction::TOP_LEFT;
        break;
    }
  }   

  // left wall
  if (this->pos_x == 0) {
    switch(this->direction) {
      case Direction::BOTTOM_LEFT:
        this->direction = Direction::BOTTOM_RIGHT;
        break;
      case Direction::LEFT:
        this->direction = Direction::RIGHT;
        break;
      case Direction:: TOP_LEFT:
        this->direction = Direction::TOP_RIGHT;
        break;   
    }
  }
}
