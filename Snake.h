#ifndef SNAKE_H
#define SNAKE_H
#include "Food.h"
#include "Position.h"
#include "console.h"

class Snake
{
public:
    Snake();
    ~Snake();
    void snake_place();
    bool game_over(Console& cons);
    void snake_move(Console& cons, Food& food, int& score);
    void move_tail();
    void move_head();
    void setPrevDirection(char direction);
    char getDirection() const;
    void setDirection(char direction);

private:
    char symbol;
    int vertical = 40;
    int horizontal = 200;
    const int down = 115;
    const int up = 119;
    const int left = 97;
    const int right = 100;
    int size;
    char direction;
    char prev_direction;
    int tail_X;
    int tail_Y;
    int head_X;
    int head_Y;
    Position snake_pos;
    void gotoxy(int x, int y) const;
};

#endif