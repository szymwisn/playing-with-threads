#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <vector>
#include <unistd.h>
#include <time.h>
#include <ncurses.h>

#include "window.h"
#include "ball.h"
#include "basket.h"

using namespace std;

const int BALLS_NUMBER = 50;

Window *window;
Basket *basket;

vector<Ball *> allBalls;
bool running = true;
int pressedKey;

void *windowUpdateCallback(void *arg)
{
  while (running)
  {
    // 25 Hz
    usleep(40000);
    window->reload(allBalls, basket);
  }

  pthread_exit(NULL);
}

void *ballCallback(void *id)
{
  while (running)
  {
    usleep(allBalls[(long)id]->getSpeed());
    allBalls[(long)id]->tryCatching();
    allBalls[(long)id]->moveBall();
  }

  pthread_exit(NULL);
}

void *keyboardCallback(void *arg)
{
  while (running)
  {
    int key = getch();

    usleep(45000);  
    
    switch (key)
    {
    case 'q':
      running = false;
      break;
    case KEY_UP:
      basket->moveTop();
      break;
    case KEY_RIGHT:
      basket->moveRight();
      break;
    case KEY_DOWN:
      basket->moveBottom();
      break;
    case KEY_LEFT:
      basket->moveLeft();
      break;
    }
  }

  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  srand(time(NULL));

  window = new Window();
  basket = new Basket(window->getWidth(), window->getHeight());

  for (long i = 0; i < BALLS_NUMBER; i++)
  {
    allBalls.push_back(new Ball(i, window->getWidth() / 2, window->getHeight() - 2, window->getWidth(), window->getHeight(), basket));
  }

  pthread_t ballThreads[BALLS_NUMBER];
  pthread_t windowThread;
  pthread_t keyboardThread;

  pthread_create(&windowThread, NULL, &windowUpdateCallback, NULL);
  pthread_create(&keyboardThread, NULL, &keyboardCallback, NULL);

  for (long i = 0; i < BALLS_NUMBER; i++)
  {
    int t = pthread_create(&ballThreads[i], NULL, ballCallback, (void *)i);

    if (t != 0)
    {
      exit(-1);
    }

    sleep(1);
  }

  pthread_join(windowThread, NULL);
  pthread_join(keyboardThread, NULL);

  for (int i = 0; i < allBalls.size(); i++)
  {
    int t = pthread_join(ballThreads[i], NULL);

    if (t)
    {
      exit(-1);
    }
  }

  return 0;
}
