#include "Food.h"
#include <stdio.h>
#include <cstdlib>

Food::Food(Console& cons)
{
  symbol = 'F';
}

void Food::food_print()
{
  gotoxy(food_pos.getX(), food_pos.getY());
  printf("%c", symbol);
}

int Food::getFoodX() const
{
  return food_pos.getX();
}

int Food::getFoodY() const
{
  return food_pos.getY();
}

void Food::placeFood(Console& cons)
{
  srand(time(0));
  food_pos.setX((rand() % (cons.get_horizontal() - 23)) + 3);
  food_pos.setY((rand() % (cons.get_vertical() - 23)) + 3);
}

void Food::gotoxy(int x, int y) const 
{
  printf("%c[%d;%df", 0x1B, y, x);
}