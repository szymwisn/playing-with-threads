#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <vector>
#include <unistd.h>

#include "window.h"
#include "ball.h"

using namespace std;

const int BALLS_NUMBER = 1;

Window * window;
vector<Ball*> allBalls;
bool running = true;

void* windowUpdateCallback(void* arg) {
  do {
    usleep(5000);
    window->reload(allBalls);
  } while(running);

  pthread_exit(NULL);
}

void* exitCallback(void* arg) {
  do {
    char key = getchar();

    if(key == 'q') {
      running = false;
      exit(0);
    }
  } while(running);
  
  pthread_exit(NULL);
}

void* ballCallback(void* id) {
  do {
    usleep(50000);
    allBalls[(long) id]->moveBall();
  } while(running);

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
      cout << "Error in thread creation: " << t << endl;
    }
  } 

  pthread_join(windowThread, NULL);
  pthread_join(exitThread, NULL);
    
  for (int i = 0; i < allBalls.size(); i++) {
    int t = pthread_join(ballThreads[i], NULL);

    if (t) {
        cout << "Error in thread joining: " << t << endl;
    }
  }

  return 0;
}
