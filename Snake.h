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
    int vertical = 40;
    int horizontal = 200;
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
    // int tail_X;
    // int tail_Y;
    // int head_X;
    // int head_Y;
    Position snake_pos[40 * 200];
    void gotoxy(int x, int y) const;
};

#endif