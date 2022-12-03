#ifndef SNAKE_H
#define SNAKE_H

class Snake
{
public:
    Snake(Console& cons);
    ~Snake();
    snake_place();

private:
    char symbol;
    int size;
    char direction;
    char prev_direction;
    int tail_X;
    int tail_Y;
    int head_X;
    int head_Y;
    Position snake_pos;
    Console cons;
};

#endif