#include "basket.h"

Basket::Basket(int winWidth, int winHeight) {
    this->winWidth = winWidth;
    this->winHeight = winHeight;

    this->prepareBasket(10, 3);
}

vector<Point*> Basket::getLeftEdge() {
    return this->leftEdge;
}

vector<Point*> Basket::getRightEdge() {
    return this->rightEdge;
}

vector<Point*> Basket::getBottomEdge() {
    return this->bottomEdge;
}

vector<Point*> Basket::getPrevLeftEdge() {
    return this->prevLeftEdge;
}

vector<Point*> Basket::getPrevRightEdge() {
    return this->prevRightEdge;
}

vector<Point*> Basket::getPrevBottomEdge() {
    return this->prevBottomEdge;
}

void Basket::moveTop() {
    this->definePreviousEdges();

    if (this->leftEdge[0]->y > 1 && this->rightEdge[0]->y > 1) {
        for(Point* point : this->leftEdge) {
            point->y--;
        }

        for(Point* point : this->rightEdge) {
            point->y--;
        }

        for(Point* point : this->bottomEdge) {
            point->y--;
        }
    }
}

void Basket::moveRight() {
    this->definePreviousEdges();

    if (this->rightEdge[0]->x < this->winWidth - 2
            && this->rightEdge[1]->x < this->winWidth - 2
            && this->rightEdge[2]->x < this->winWidth - 2) {

        for(Point* point : this->leftEdge) {
            point->x++;
        }

        for(Point* point : this->rightEdge) {
            point->x++;
        }

        for(Point* point : this->bottomEdge) {
            point->x++;
        }
    }
}

void Basket::moveBottom() {
    this->definePreviousEdges();

    if (this->bottomEdge[0]->y < this->winHeight - 2) {
        for(Point* point : this->leftEdge) {
            point->y++;
        }

        for(Point* point : this->rightEdge) {
            point->y++;
        }

        for(Point* point : this->bottomEdge) {
            point->y++;
        }
    }
}

void Basket::moveLeft() {
    this->definePreviousEdges();

    if (this->leftEdge[0]->x > 1
            && this->leftEdge[1]->x > 1
            && this->leftEdge[2]->x > 1) {

        for(Point* point : this->leftEdge) {
            point->x--;
        }

        for(Point* point : this->rightEdge) {
            point->x--;
        }

        for(Point* point : this->bottomEdge) {
            point->x--;
        }
    }
}

void Basket::catchBalls(vector<Ball*> allBalls) {
    // TODO 
}

void Basket::prepareBasket(int width, int height) {
    int y = 20;
    for(int i = 0; i < height; i++) {
        Point* p = new Point(20, y += 1);
        this->leftEdge.push_back(p);
    }

    y = 20;
    for(int i = 0; i < height; i++) {
        Point* p = new Point(20 + width + 1, y += 1);
        this->rightEdge.push_back(p);
    }

    int x = 20;
    for(int i = 0; i < width; i++) {
        Point* p = new Point(x += 1, 20 + height);
        this->bottomEdge.push_back(p);
    }

    this->definePreviousEdges();
}

void Basket::definePreviousEdges() {
    this->prevLeftEdge = this->deepCopyEdge(this->leftEdge);
	this->prevRightEdge = this->deepCopyEdge(this->rightEdge);
	this->prevBottomEdge = this->deepCopyEdge(this->bottomEdge);
}

vector<Point*> Basket::deepCopyEdge(vector<Point*> edge) {
    vector<Point*> edgeCopy;

    for(int i = 0; i < edge.size(); i++){
		edgeCopy.push_back(edge[i]);
	}

    return edgeCopy;
}
