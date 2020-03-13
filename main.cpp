#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <vector>
#include <unistd.h>

#include "window.h"
#include "ball.h"

using namespace std;

const int BALLS_NUMBER = 10;

Window * window;
vector<Ball*> allBalls;
bool running = true;

void* windowUpdateCallback(void* arg) {
  while(running) {
    usleep(10000);
    window->reload(allBalls);
  }

  pthread_exit(NULL);
}

void* exitCallback(void* arg) {
  while(running) {
    char key = getchar();

    if(key == 'q') {
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

int main(int argc, char * argv[]) {
  srand(time(NULL));
  window = new Window();
  
  pthread_t ballThreads[BALLS_NUMBER];
  pthread_t windowThread;   
  pthread_t exitThread;

  pthread_create(&windowThread, NULL, &windowUpdateCallback, NULL);
  pthread_create(&exitThread, NULL, &exitCallback, NULL); 

  for(long i = 0; i < BALLS_NUMBER; i++) {
    allBalls.push_back(new Ball(i, window->getWidth()/2, window->getHeight() - 3, window->getWidth(), window->getHeight()));
    int t = pthread_create(&ballThreads[i], NULL, ballCallback, (void *) i );    

    if(t != 0) {
      exit(-1);
    }

    sleep(1);
  } 

  pthread_join(windowThread, NULL);
  pthread_join(exitThread, NULL);
    
  for (int i = 0; i < allBalls.size(); i++) {
    int t = pthread_join(ballThreads[i], NULL);

    if (t) {
      exit(-1);
    }
  }

  return 0;
}
