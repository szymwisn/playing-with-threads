#include "window.h"

Window::Window() {
  initscr();
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
  refresh();
}

void Window::reload(vector<Ball*> balls) {
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

void Window::drawArea() {
  this->window = newwin(this->height, this->width, 0, 0);
  refresh();

  box(this->window, 0, 0);
  wrefresh(this->window);
}

void Window::drawBall(Ball* ball) {
  mvwprintw(this->window, ball->getPrevPosY(), ball->getPrevPosX(), " ");
  
  wattron(this->window, COLOR_PAIR(ball->getColor()));
  mvwprintw(this->window, ball->getPosY(), ball->getPosX(), "o");
  wattroff(this->window, COLOR_PAIR(ball->getColor()));

  wrefresh(this->window);
}
