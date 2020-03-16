#include "window.h"

Window::Window() {
  initscr();
  // cbreak();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(FALSE);
  getmaxyx(stdscr, this->height, this->width);
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_BLUE, COLOR_BLACK);
  init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(5, COLOR_YELLOW, COLOR_BLACK);
  init_pair(6, COLOR_WHITE, COLOR_BLACK);
  this->drawArea();
}

Window::~Window() {
  wrefresh(this->window);
  delwin(this->window);
  endwin();
}

void Window::reload(vector<Ball*> balls, Basket* basket) {
  drawBasket(basket);

  for(int i = 0; i < balls.size(); i++){
    drawBall(balls[i]);
  }
}

int Window::getWidth() {
  return this->width;
}

int Window::getHeight() {
  return this->height;
}

WINDOW* Window::getWindow() {
  return this->window;
}

void Window::drawArea() {
  this->window = newwin(this->height, this->width, 0, 0);
  refresh();

  box(this->window, 0, 0);
  mvwaddch(this->window, this->height / 2, this->width / 2, 'V');
  wrefresh(this->window);
}

void Window::drawBall(Ball* ball) {
  mvwaddch(this->window, ball->getPrevPosY(), ball->getPrevPosX(), ' ');

  if(ball->getPrevPosY() == this->height / 2 && ball->getPrevPosX() == this->width / 2) {
    mvwaddch(this->window, this->height / 2, this->width / 2, 'V');
  }
  
  wattron(this->window, COLOR_PAIR(ball->getColor()));
  mvwaddch(this->window, ball->getPosY(), ball->getPosX(), 'o');
  wattroff(this->window, COLOR_PAIR(ball->getColor()));

  wrefresh(this->window);
}

void Window::drawBasket(Basket* basket) {
  for(Point* point : basket->getPrevLeftEdge()) {
    mvwaddch(this->window, point->y, point->x, ' ');
  }

  for(Point* point : basket->getPrevRightEdge()) {
    mvwaddch(this->window, point->y, point->x, ' ');
  }

  for(Point* point : basket->getPrevBottomEdge()) {
    mvwaddch(this->window, point->y, point->x, ' ');
  }
  
  for(Point* point : basket->getLeftEdge()) {
    mvwaddch(this->window, point->y, point->x, '|');
  }

  for(Point* point : basket->getRightEdge()) {
    mvwaddch(this->window, point->y, point->x, '|');
  }

  for(Point* point : basket->getBottomEdge()) {
    mvwaddch(this->window, point->y, point->x, '_');
  }

  wrefresh(this->window);
}
