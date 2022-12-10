#include "Position.h"
#include <stdio.h>

Position::Position()
{
    int x;
    int y;
}

void Position::setX(int value)
{
    x = value;
}

void Position::setY(int value)
{
    y = value;
}

int Position::getX() const
{
    return x;
}

int Position::getY() const
{
    return y;
}