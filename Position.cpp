#include "Position.h"
#include <stdio.h>

Position::Position(int vertical, int horizontal)
{
    this->vertical = vertical;
    this->horizontal = horizontal;
    x = new int[vertical * horizontal];
    y = new int[vertical * horizontal];
}

void Position::setX(int index, int value)
{
    if (index < (vertical * horizontal))
    {
        x[index] = value;
    }
}

void Position::setY(int index, int value)
{
    if (index < (vertical * horizontal))
    {
        y[index] = value;
    }
}

Position::~Position()
{
    delete [] x;
    delete [] y;
}