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

private:
    int x;
    int y;
};

#endif