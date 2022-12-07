#ifndef POSITION_H
#define POSITION_H

class Position
{
public:
    Position();
    void setX(int value);
    void setY(int value);
    int getX() const;
    int getY() const;
    // ~Position();
    // void setX(int index, int value);
    // void setY(int index, int value);
    // int get_horizontal(int index) const;
    // int get_vertical(int index) const;

private:
    // int vertical = 40;
    // int horizontal = 200;
    // int* x;
    int x;
    // int* y;
    int y;
};

#endif