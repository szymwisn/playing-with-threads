#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <vector>

#include "window.h"
#include "ball.h"

using namespace std;

int main(int argc, char * argv[]) {
  Window* window = new Window();

  window->drawBall(20, 20);

  window->~Window();
  return 0;
}

