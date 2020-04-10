#ifndef BASKET_H
#define BASKET_H

#include <vector>
#include <stdlib.h>

#include "ball.h"
#include "point.h"

using namespace std;

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
    vector<Ball *> allBalls;
    vector<Ball *> coughtBalls;

    void prepareBasket(int width, int height);
    void definePreviousEdges();
    vector<Point *> deepCopyEdge(vector<Point *> edge);

public:
    Basket(int winWidth, int winHeight);
    ~Basket();

    void catchBalls(vector<Ball *> allBalls); // przekazac wszystkie ballsy, porownac wspolrzedne, sprawdzic czy ball wpadl do kubla, jesli tak - dodac ballsy do coughtBalls, wywolac ball->moveInBasket w moveTop, moveRight itp.
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
