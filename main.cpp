#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <vector>

#include "window.h"
#include "ball.h"

using namespace std;

Window * window;

int main(int argc, char * argv[]) {
  window = new Window();

  vector<std::thread> ballThreads(20);
  std::thread windowThread(windowUpdateCallback);

  std::thread exitThread(exitCallback);

  for(int i = 0; i < ballThreads.size; i++) {
    std::ballThread ballThread(ballCallback, i);
    ballThreads.push_back(ballThread);
  } 
  
  windowThread.join();
  exitThread.join();
  
  for(int i = 0; i < ballThreads.size; i++) {
    ballThreads[i].join();
  }

  //window->drawBall(20, 20);
  //window->~Window();
  return 0;
}

void windowUpdateCallback() {

}

void exitCallback() {

}

void ballCallback(int id) {

}

