#ifndef POSITION_H
#define POSITION_H

class Position
{
public:
    Position(int vertical, int horizontal);
    ~Position();
    void Position::setX(int index, int value);
    void Position::setY(int index, int value);

private:
    int vertical;
    int horizontal;
    int* x;
    int* y;
}

#endif