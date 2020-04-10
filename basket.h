#ifndef BASKET_H
#define BASKET_H

#include <vector>
#include <stdlib.h>

#include "point.h"
#include "ball.h"

using namespace std;

class Ball;

class Basket
{
    int winWidth;
    int winHeight;
    vector<Point *> leftEdge;
    vector<Point *> rightEdge;
    vector<Point *> bottomEdge;
    vector<Point *> prevLeftEdge;
    vector<Point *> prevRightEdge;
    vector<Point *> prevBottomEdge;
    vector<Ball *> coughtBalls;

    void prepareBasket(int width, int height);
    void definePreviousEdges();
    vector<Point *> deepCopyEdge(vector<Point *> edge);

public:
    Basket(int winWidth, int winHeight);
    ~Basket();

    void catchBall(Ball *ball);
    void moveTop();
    void moveRight();
    void moveBottom();
    void moveLeft();

    vector<Point *> getLeftEdge();
    vector<Point *> getRightEdge();
    vector<Point *> getBottomEdge();
    vector<Point *> getPrevLeftEdge();
    vector<Point *> getPrevRightEdge();
    vector<Point *> getPrevBottomEdge();
};

#endif
