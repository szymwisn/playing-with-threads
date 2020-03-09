#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <vector>

#include "window.h"
#include "ball.h"

using namespace std;

Window * window;
vector<Ball*> balls;
bool running = true;

void windowUpdateCallback() {
  do {
    window.reload(balls);
  } while(running);
}

void exitCallback() {
  do {
    char key = getchar();

    if(c == 'q') {
      running = false;
    }
  } while(running);
}

void ballCallback(int id) {
  do {
    balls[i].moveBall();
  } while(running);
}

int main(int argc, char * argv[]) {
  window = new Window();

  int N = 20;
  
  balls.resize(N);

  vector<thread> ballThreads;
  thread windowThread(windowUpdateCallback);

  thread exitThread(exitCallback);

  for(int i = 0; i < ballThreads.size(); i++) {
    balls.push_back(new Ball(i, window.getWidth()/2, window.getHeight(), window.getWidth(), window.getHeight()));
    thread ballThread(ballCallback, i);
    ballThreads.push_back(ballThread);
  } 
  
  windowThread.join();
  exitThread.join();
  
  for(int i = 0; i < ballThreads.size(); i++) {
    ballThreads[i].join();
  }

  //window->~Window();
  return 0;
}

