#include "ball.h"

Ball::Ball(int id, int pos_x, int pos_y, int winWidth, int winHeight, Basket *basket)
{
  this->id = id;
  this->pos_x = pos_x;
  this->pos_y = pos_y;
  this->speed = this->randomizeSpeed();
  this->direction = Direction::TOP;
  this->winWidth = winWidth;
  this->winHeight = winHeight;
  this->prev_pos_x = pos_x;
  this->prev_pos_y = pos_y;
  this->directionChanged = false;
  this->color = rand() % 6 + 1;
  this->inBasket = false;
  this->basket = basket;
}

Ball::~Ball() {}

int Ball::getPosX()
{
  return this->pos_x;
}

int Ball::getPosY()
{
  return this->pos_y;
}

int Ball::getPrevPosX()
{
  return this->prev_pos_x;
}

int Ball::getPrevPosY()
{
  return this->prev_pos_y;
}

int Ball::getColor()
{
  return this->color;
}

int Ball::getSpeed()
{
  return this->speed;
}

bool Ball::getInBasket()
{
  return this->inBasket;
}

void Ball::moveBall()
{
  if (!this->inBasket)
  {
    this->prev_pos_x = pos_x;
    this->prev_pos_y = pos_y;

    if (!this->directionChanged && this->getPosY() == this->winHeight / 2)
    {
      this->randomizeDirection();
    }

    switch (this->direction)
    {
    case Direction::TOP:
      this->pos_y--;
      break;
    case Direction::TOP_RIGHT:
      this->pos_y--;
      this->pos_x++;
      break;
    case Direction::RIGHT:
      this->pos_x++;
      break;
    case Direction::BOTTOM_RIGHT:
      this->pos_x++;
      this->pos_y++;
      break;
    case Direction::BOTTOM:
      this->pos_y++;
      break;
    case Direction::BOTTOM_LEFT:
      this->pos_x--;
      this->pos_y++;
      break;
    case Direction::LEFT:
      this->pos_x--;
      break;
    case Direction::TOP_LEFT:
      this->pos_x--;
      this->pos_y--;
      break;
    }

    this->bounceWalls();
  }
}

void Ball::moveBottom()
{
  if (this->inBasket)
  {
    this->prev_pos_y = pos_y;
    this->pos_y++;
  }
}

void Ball::moveTop()
{
  if (this->inBasket)
  {
    this->prev_pos_y = pos_y;
    this->pos_y--;
  }
}

void Ball::moveRight()
{
  if (this->inBasket)
  {
    this->prev_pos_x = pos_x;
    this->pos_x++;
  }
}

void Ball::moveLeft()
{
  if (this->inBasket)
  {
    this->prev_pos_x = pos_x;
    this->pos_x--;
  }
}

void Ball::bounceWalls()
{
  // top wall
  if (this->pos_y == 1)
  {
    switch (this->direction)
    {
    case Direction::TOP:
      this->direction = Direction::BOTTOM;
      break;
    case Direction::TOP_RIGHT:
      this->direction = Direction::BOTTOM_RIGHT;
      break;
    case Direction::TOP_LEFT:
      this->direction = Direction::BOTTOM_LEFT;
      break;
    }
  }

  // right wall
  if (this->pos_x == this->winWidth - 2)
  {
    switch (this->direction)
    {
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
  if (this->pos_y == this->winHeight - 2)
  {
    switch (this->direction)
    {
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
  if (this->pos_x == 1)
  {
    switch (this->direction)
    {
    case Direction::BOTTOM_LEFT:
      this->direction = Direction::BOTTOM_RIGHT;
      break;
    case Direction::LEFT:
      this->direction = Direction::RIGHT;
      break;
    case Direction::TOP_LEFT:
      this->direction = Direction::TOP_RIGHT;
      break;
    }
  }
}

void Ball::bounceBasketBottom()
{
  switch (this->direction)
  {
  case Direction::TOP:
    this->direction = Direction::BOTTOM;
    break;
  case Direction::TOP_RIGHT:
    this->direction = Direction::BOTTOM_RIGHT;
    break;
  case Direction::TOP_LEFT:
    this->direction = Direction::BOTTOM_LEFT;
    break;
  }
}

void Ball::bounceBasketTop()
{
  switch (this->direction)
  {
  case Direction::BOTTOM:
    this->direction = Direction::TOP;
    break;
  }
}

void Ball::bounceBasketLeft()
{
  switch (this->direction)
  {
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

void Ball::bounceBasketRight()
{
  switch (this->direction)
  {
  case Direction::BOTTOM_LEFT:
    this->direction = Direction::BOTTOM_RIGHT;
    break;
  case Direction::LEFT:
    this->direction = Direction::RIGHT;
    break;
  case Direction::TOP_LEFT:
    this->direction = Direction::TOP_RIGHT;
    break;
  }
}

void Ball::randomizeDirection()
{
  // probability of moving left - 45%
  // right - 40%
  // no change - 15%
  int number = rand() % 100 + 1;

  if (number > 0 && number <= 45)
  {
    this->direction = Direction::TOP_LEFT;
  }
  else if (number > 60 && number <= 100)
  {
    this->direction = Direction::TOP_RIGHT;
  }

  directionChanged = true;
}

int Ball::randomizeSpeed()
{
  switch (rand() % 3)
  {
  case 0:
    return 80000;
    break;
  case 1:
    return 120000;
    break;
  case 2:
    return 160000;
    break;
  default:
    return 80000;
  }
}

void Ball::catchToBasket()
{
  if (!this->inBasket)
  {
    this->inBasket = true;
  }
}

void Ball::releaseFromBasket()
{
  if (this->inBasket)
  {
    vector<Direction> directions;
    directions.push_back(Direction::TOP_RIGHT);
    directions.push_back(Direction::BOTTOM_RIGHT);
    directions.push_back(Direction::BOTTOM_LEFT);
    directions.push_back(Direction::TOP_LEFT);

    int index = rand() % directions.size();
    Direction newDirection = directions[index];

    this->direction = newDirection;
    this->inBasket = false;
  }
}

void Ball::tryCatching()
{
  if (!this->inBasket)
  {
    vector<Point *> basketLeft = this->basket->getLeftEdge();
    vector<Point *> basketRight = this->basket->getRightEdge();
    vector<Point *> basketBottom = this->basket->getBottomEdge();

    // catch bottom edge
    if (this->direction == Direction::BOTTOM_LEFT || this->direction == Direction::BOTTOM || this->direction == Direction::BOTTOM_RIGHT)
    {
      int edge_x_left = basketLeft[0]->x;
      int edge_y = basketBottom[0]->y;
      int edge_x_right = basketRight[0]->x;

      if (this->pos_y == edge_y && this->pos_x >= edge_x_left + 1 && this->pos_x <= edge_x_right - 1)
      {
        basket->catchBall(this);
      }
    }

    // bounceWalls from bottom edge
    if (this->direction == Direction::TOP_LEFT || this->direction == Direction::TOP || this->direction == Direction::TOP_RIGHT)
    {
      int edge_x_left = basketLeft[0]->x;
      int edge_y = basketBottom[0]->y;
      int edge_x_right = basketRight[0]->x;

      if (this->pos_y == edge_y + 1 && this->pos_x >= edge_x_left && this->pos_x <= edge_x_right)
      {
        this->bounceBasketBottom();
      }
    }

    // catch left edge
    if (this->direction == Direction::BOTTOM_LEFT)
    {
      int edge_y_top = basketLeft[0]->y;
      int edge_y_bottom = basketBottom[0]->y;
      int edge_x = basketLeft[0]->x;

      if (this->pos_x == edge_x && this->pos_y <= edge_y_bottom && this->pos_y >= edge_y_top)
      {
        this->basket->catchBall(this);
      }
    }

    // bounceWalls from left edge
    if (this->direction == Direction::TOP_RIGHT || this->direction == Direction::RIGHT || this->direction == Direction::BOTTOM_RIGHT)
    {
      int edge_y_top = basketLeft[0]->y;
      int edge_y_bottom = basketBottom[0]->y;
      int edge_x = basketLeft[0]->x;

      if (this->pos_x == edge_x - 1 && this->pos_y <= edge_y_bottom + 1 && this->pos_y >= edge_y_top - 1)
      {
        this->bounceBasketLeft();
      }
    }

    // catch right edge
    if (this->direction == Direction::BOTTOM_RIGHT)
    {
      int edge_y_top = basketRight[0]->y;
      int edge_y_bottom = basketBottom[0]->y;
      int edge_x = basketRight[0]->x;

      if (this->pos_x == edge_x && this->pos_y <= edge_y_bottom && this->pos_y >= edge_y_top)
      {
        this->basket->catchBall(this);
      }
    }
    
    // bounceWalls from right edge
    if (this->direction == Direction::TOP_LEFT || this->direction == Direction::LEFT || this->direction == Direction::BOTTOM_LEFT)
    {
      int edge_y_top = basketRight[0]->y;
      int edge_y_bottom = basketBottom[0]->y;
      int edge_x = basketRight[0]->x;

      if (this->pos_x == edge_x + 1 && this->pos_y <= edge_y_bottom + 1 && this->pos_y >= edge_y_top - 1)
      {
        this->bounceBasketRight();
      }
    }

    // bounceWalls from top 
    if (this->direction == Direction::BOTTOM)
    {
      int edge_y_top = basketLeft[0]->y;
      int edge_x_left = basketLeft[0]->x;
      int edge_x_right = basketRight[0]->x;

      if (this->pos_y == edge_y_top - 1 && (this->pos_x == edge_x_left || this->pos_x == edge_x_right))
      {
        this->bounceBasketTop();
      }
    }
  }
}
