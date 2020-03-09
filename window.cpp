#include "window.h"

Window::Window() {
  initscr();
  curs_set(FALSE);
  getmaxyx(stdscr, this->height, this->width);
  this->drawArea();
}

Window::~Window() {
  wrefresh(this->window);
  delwin(this->window);
  endwin();
  refresh();
}

void Window::drawArea() {
  this->window = newwin(this->height, this->width, 0, 0);
  refresh();

  box(this->window, 0, 0);
  wrefresh(this->window);
}

void Window::drawBall(int pos_x, int pos_y) {
  mvwprintw(this->window, pos_y, pos_x, "o");
  wrefresh(this->window);
}

void Window::reload() {

}
