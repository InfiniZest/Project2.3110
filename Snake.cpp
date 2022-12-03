#include "Snake.h"
#include "console.h"
#include <stdio.h>

Snake::Snake(Console& cons)
{
    symbol='*';
    size=10;
    direction=right;
    prev_direction=down;
    tail_X=5;
    tail_Y=5;
    head_X= tail_X + size-1;
    head_Y=5;
    snake_pos = new Position(cons.get_vertical, cons.get_horizontal);
    this->cons = cons;
}

Snake::~Snake()
{
    delete [] snake_pos;
}

void Snake::snake_place()
{
    for (int i = 0; i < size; i++)
    {
        cons.gotoxy(tail_X, tail_Y);
        printf("%c", symbol);
        snake_pos->setX(i, tail_X);
        snake_pos->setY(i, tail_Y);
        tail_X += 1;
    }
}

