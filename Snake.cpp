#include "Snake.h"
#include "Position.h"
#include "Food.h"
#include "console.h"
#include <stdio.h>

Snake::Snake()
{
    snake_pos = Position();
    symbol = '*';
    size = 10;
    direction = right;
    prev_direction = down;
    tail_X = 5;
    tail_Y = 5;
    head_X = tail_X + size-1;
    head_Y = 5;
}

Snake::~Snake()
{
}

void Snake::snake_place()
{
    for (int i = 0; i < size; i++)
    {
        gotoxy(tail_X, tail_Y);
        printf("%c", symbol);
        snake_pos.setX(i, tail_X);
        snake_pos.setY(i, tail_Y);
        tail_X += 1;
    }
}

bool Snake::game_over(Console& cons)
{
    for (int i = 0; i < size; ++i)
    {
        if ((snake_pos.get_horizontal(i) == head_X) && (snake_pos.get_vertical(i) == head_Y))
        {
          return true;
        }
    }


    if ((head_X == cons.get_horizontal()) || (head_X == 1) || (head_Y == cons.get_vertical()) || (head_Y == 1))
    {
      return true;
    }


  return false;

}

void Snake::snake_move(Console& cons, Food& food, int& score)
{
    move_head();

    if (!((head_X == food.getFoodX()) && (head_Y == food.getFoodY())))
    {
        move_tail();
    }
    else
    {
        size++;
        score += 1;
        food.placeFood(cons);
        food.food_print();
    }
}

void Snake::move_tail()
{
    // remove last cell of tail
    gotoxy(snake_pos.get_horizontal(0), snake_pos.get_vertical(0));
    printf(" ");

    // update new tail position
    for (int i = 0; i < size; ++i)
    {
        snake_pos.setX(i, snake_pos.get_horizontal(i + 1)); 
        snake_pos.setY(i, snake_pos.get_vertical(i + 1));
    }
}

void Snake::move_head()
{
    switch (direction)
    {
        case 100:   // right
            if (prev_direction == left)
            {
                head_X--;
                break;
            }
            head_X++;
            break;

        case 97:    // left
            if (prev_direction == right)
            {
                head_X++;
                break;
            }
            head_X--;
            break;
        case 119:    // up
            if (prev_direction == down)
            {
                head_Y++;
                break;
            }
            head_Y--;
            break;
        case 115:    // down
            if (prev_direction == up)
            {
                head_Y--;
                break;
            }
            head_Y++;
            break;
        default:
            break;
    }

    // update tail position
    snake_pos.setX(size, head_X);
    snake_pos.setY(size, head_Y);

    gotoxy(snake_pos.get_horizontal(size), snake_pos.get_vertical(size));
    printf("%c", symbol);
}

void Snake::setPrevDirection(char direction)
{
    prev_direction = direction;
}

char Snake::getDirection() const
{
    return direction;
}

void Snake::setDirection(char direction)
{
    this->direction = direction;
}

void Snake::gotoxy(int x, int y) const 
{
    printf("%c[%d;%df",0x1B,y,x);
}