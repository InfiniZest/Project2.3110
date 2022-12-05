#include "Position.h"
#include <stdio.h>

Position::Position()
{
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

int Position::get_horizontal(int index) const
{
    return x[index];
}

int Position::get_vertical(int index) const
{
    return y[index];
}

Position::~Position()
{
    delete [] x;
    delete [] y;
}