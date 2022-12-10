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
    int getSnakeSpeed() const;
    void setSnakeSpeed(int speed);
    int getSize() const;
    Position getSegmentOfSnakePositionAt(int i) const;

private:
    char symbol;
    const int down = 115;
    const int up = 119;
    const int left = 97;
    const int right = 100;
    int snake_speed = 100000;
    int size;
    char direction;
    char prev_direction;
    Position head;
    Position tail;
    Position* snake_pos;
    int snakeCapacity;
    void gotoxy(int x, int y) const;
    void reallocateSnakeSize();
};

#endif