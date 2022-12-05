#ifndef FOOD_H
#define FOOD_H
#include "console.h"
#include <cstdlib>
#include <ctime>

class Food
{
public:
  Food(Console& cons);
  void food_print();
  int getFoodX() const;
  int getFoodY() const;
  void placeFood(Console& cons);

private:
  int x;
  int y;
  char symbol;
  void gotoxy(int x, int y) const;
};

#endif