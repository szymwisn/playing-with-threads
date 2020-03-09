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

Ball::~Ball() {

}

void Ball::moveBall() {
  do { 
    this->changeDirection();

    switch(this->direction) {
      case Direction::TOP:
        pos_y += 1 * this->speed;
        break; 
      case Direction::TOP_RIGHT:
        pos_y += 1 * this->speed;
        pos_x += 1 * this->speed;
        break;
      case Direction::RIGHT:
        pos_x += 1 * this->speed;
        break;
      case Direction::BOTTOM_RIGHT:
        pos_x += 1 * this->speed;
        pos_y -= 1 * this->speed;
        break;
      case Direction::BOTTOM:
        pos_y -= 1 * this->speed;
        break;
      case Direction::BOTTOM_LEFT:
        pos_x -= 1 * this->speed;
        pos_y -= 1 * this->speed;
        break;
      case Direction::LEFT:
        pos_x -= 1 * this->speed;
        break;
      case Direction:: TOP_LEFT:
        pos_x -= 1 * this->speed;
        pos_y += 1 * this->speed;
        break;
    } 
  } while(true);
}

void Ball::changeDirection() {
  // top wall
  if (pos_y == 0) {
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
  if (pos_x == winWidth) {
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
  if (pos_y == winHeight) {
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
  if (pos_x == 0) {
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

