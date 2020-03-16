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

const int BALLS_NUMBER = 3;

Window * window;
Basket* basket;

vector<Ball*> allBalls;
bool running = true;

void* windowUpdateCallback(void* arg) {
  while(running) {
    usleep(10000);
    window->reload(allBalls, basket);
  }

  pthread_exit(NULL);
}

void* exitCallback(void* arg) {
  while(running) {
    int key = wgetch(window->getWindow());

    if(key == KEY_EXIT) {
      running = false;
    }
  }
  
  pthread_exit(NULL);
}

void* ballCallback(void* id) {
  while(running) {
    usleep(allBalls[(long) id]->getSpeed());
    allBalls[(long) id]->moveBall();
  }

  pthread_exit(NULL);
}

void* basketCallback(void* arg) {
  while(running) {
    int key = getch();

    switch (key) {
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

int main(int argc, char * argv[]) {
  srand(time(NULL));

  window = new Window();
  basket = new Basket(window->getWidth(), window->getHeight());

  for(long i = 0; i < BALLS_NUMBER; i++) {
    allBalls.push_back(new Ball(i, window->getWidth()/2, window->getHeight() - 2, window->getWidth(), window->getHeight()));
  } 
  
  pthread_t ballThreads[BALLS_NUMBER];
  pthread_t windowThread;   
  pthread_t exitThread;
  pthread_t basketThread;

  pthread_create(&windowThread, NULL, &windowUpdateCallback, NULL);
  pthread_create(&exitThread, NULL, &exitCallback, NULL); 
  pthread_create(&basketThread, NULL, &basketCallback, NULL);

  for(long i = 0; i < BALLS_NUMBER; i++) {
    int t = pthread_create(&ballThreads[i], NULL, ballCallback, (void *) i );    

    if(t != 0) {
      exit(-1);
    }

    sleep(1);
  } 

  pthread_join(windowThread, NULL);
  pthread_join(exitThread, NULL);
  pthread_join(basketThread, NULL);
    
  for (int i = 0; i < allBalls.size(); i++) {
    int t = pthread_join(ballThreads[i], NULL);

    if (t) {
      exit(-1);
    }
  }

  return 0;
}
