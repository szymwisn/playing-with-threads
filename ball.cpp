#include "ball.h"

Ball::Ball(int id, int pos_x, int pos_y, int winWidth, int winHeight) {
  this->id = id;
  this->pos_x = pos_x;
  this->pos_y = pos_y;
  // this->speed = rand() % 4 + 1;
  this->speed = 1;
  this->direction = Direction::TOP;
  this->winWidth = winWidth;
  this->winHeight = winHeight;
  this->prev_pos_x = pos_x;
  this->prev_pos_y = pos_y;
  this->directionChanged = false;
  this->color = rand() % 6 + 1;
}

Ball::~Ball() {}

int Ball::getPosX() {
  return this->pos_x;
}

int Ball::getPosY() {
  return this->pos_y;
}

int Ball::getPrevPosX() {
  return this->prev_pos_x;
}

int Ball::getPrevPosY() {
  return this->prev_pos_y;
}

int Ball::getColor() {
  return this->color;
}

void Ball::moveBall() {
  do { 
    if(!this->directionChanged && this->getPosY() == this->winHeight / 2) {
      this->randomizeDirection();
    }

    switch(this->direction) {
      case Direction::TOP:
        this->pos_y -= 1;
        break; 
      case Direction::TOP_RIGHT:
        this->pos_y -= 1;
        this->pos_x += 1;
        break;
      case Direction::RIGHT:
        this->pos_x += 1;
        break;
      case Direction::BOTTOM_RIGHT:
        this->pos_x += 1;
        this->pos_y += 1;
        break;
      case Direction::BOTTOM:
        this->pos_y += 1;
        break;
      case Direction::BOTTOM_LEFT:
        this->pos_x -= 1;
        this->pos_y += 1;
        break;
      case Direction::LEFT:
        this->pos_x -= 1;
        break;
      case Direction:: TOP_LEFT:
        this->pos_x -= 1;
        this->pos_y -= 1;
        break;
    } 

    this->prev_pos_x = pos_x;
    this->prev_pos_y = pos_y;

    this->bounce();
  } while(true);
}

void Ball::bounce() {
  // top wall
  if (this->pos_y == 1) {
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
  if (this->pos_x == this->winWidth - 2) {
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
  if (this->pos_y == this->winHeight - 2) {
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
  if (this->pos_x == 1) {
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

void Ball::randomizeDirection() {
  // probability of moving left - 45%
  // right - 40%
  // no change - 15%
  bool number = rand() % 100 + 1;

  if (number >= 1 && number <= 45) {
    this->direction = Direction::TOP_LEFT;
  } else if (number >= 60 && number <= 100) {
    this->direction = Direction::TOP_RIGHT;
  }

  directionChanged = true;
}
