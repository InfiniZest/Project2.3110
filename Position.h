#ifndef POSITION_H
#define POSITION_H

class Position
{
public:
    Position();
    ~Position();
    void setX(int index, int value);
    void setY(int index, int value);
    int get_horizontal(int index) const;
    int get_vertical(int index) const;

private:
    int vertical = 40;
    int horizontal = 200;
    int* x;
    int* y;
};

#endif