#ifndef POINT_H
#define POINT_H

using namespace std;

class Point {
    public:
        int x;
        int y;

        Point(int pos_x, int pos_y) {
            this->x = pos_x;
            this->y = pos_y;
        }; 

        void setValues (int pos_x, int pos_y) {
            this->x = pos_x;
            this->y = pos_y;
        };
};

#endif
