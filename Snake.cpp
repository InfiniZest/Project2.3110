#include "Snake.h"
#include <stdio.h>

Snake::Snake()
{
    symbol = '*';
    size = 10;
    snakeCapacity = size * 2;
    snake_pos = new Position[snakeCapacity];
    direction = right;
    prev_direction = down;
    tail.setX(5);
    tail.setY(5);
    head.setX(tail.getX() + size - 1);
    head.setY(5);
}

Snake::~Snake()
{
    delete [] snake_pos;
}

void Snake::snake_place()
{
    for (int i = 0; i < size; i++)
    {
        gotoxy(tail.getX(), tail.getY());
        printf("%c", symbol);
        snake_pos[i].setX(tail.getX());
        snake_pos[i].setY(tail.getY());
        tail.setX(tail.getX() + 1);
    }
}

bool Snake::game_over(Console& cons)
{
    
    for (int i = 0; i < size - 1; ++i)
    {
        if ((snake_pos[i].getX() == head.getX()) && (snake_pos[i].getY() == head.getY()))
        {
            return true;
        }
    }
    

    if ((head.getX() >= cons.get_horizontal()) || (head.getX() <= 1) || (head.getY() >= cons.get_vertical()) || (head.getY() <= 1))
    {
        return true;
    }

    return false;
}

void Snake::snake_move(Console& cons, Food& food, int& score)
{
    move_head();

    if (!((head.getX() == food.getFoodX()) && (head.getY() == food.getFoodY())))
    {
        move_tail();
    }
    else
    {
        size++;
        if (size + 5 >= snakeCapacity)
        {
            reallocateSnakeSize();
        }
        score += 1;
        bool isValidPosition;
        do 
        {
            isValidPosition = true;
            food.placeFood(cons);
            for (int i = 0; i < size; ++i)
            {
                if (snake_pos[i].getX() == food.getFoodX() && snake_pos[i].getY() == food.getFoodY())
                {
                    isValidPosition = false;
                }
            }
        } while (!isValidPosition);
        food.food_print();
    }
}

void Snake::move_tail()
{
    // remove last cell of tail
    gotoxy(snake_pos[0].getX(), snake_pos[0].getY());
    printf(" ");

    // update new tail position
    for (int i = 0; i < size; ++i)
    {
        snake_pos[i] = snake_pos[i + 1];
    }
}

void Snake::move_head()
{
    switch (direction)
    {
        case 100:   // right
            if (prev_direction == left)
            {
                head.setX(head.getX() + 1);
                break;
            }
            head.setX(head.getX() + 1);
            break;

        case 97:    // left
            if (prev_direction == right)
            {
                head.setX(head.getX() + 1);
                break;
            }
            head.setX(head.getX() - 1);
            break;
        case 119:    // up
            if (prev_direction == down)
            {
                head.setY(head.getY() + 1);
                break;
            }
            head.setY(head.getY() - 1);
            break;
        case 115:    // down
            if (prev_direction == up)
            {
                head.setY(head.getY() - 1);
                break;
            }
            head.setY(head.getY() + 1);
            break;
        default:
            break;
    }

    // update tail position
    snake_pos[size].setX(head.getX());
    snake_pos[size].setY(head.getY());

    gotoxy(snake_pos[size].getX(), snake_pos[size].getY());
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
    printf("%c[%d;%df", 0x1B, y, x);
}

int Snake::getSnakeSpeed() const
{
    return snake_speed;
}

void Snake::setSnakeSpeed(int speed)
{
    snake_speed = speed;
}

int Snake::getSize() const
{
    return size;
}

/* Returns a single location of part of the snake */

Position Snake::getSegmentOfSnakePositionAt(int i) const
{
    return snake_pos[i];
}

/* Use to increase the snake capacity */

void Snake::reallocateSnakeSize()
{
    Position* old = snake_pos;
    snakeCapacity += 10;
    snake_pos = new Position[snakeCapacity];
    for (int i = 0; i < size; i++)
    {
        snake_pos[i] = old[i]; 
    }

    delete [] old;
}