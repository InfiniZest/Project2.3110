#include "Food.h"
#include <stdio.h>
#include <cstdlib>

Food::Food(Console& cons)
{
  srand(time(0));  
  x = (rand() % (cons.get_horizontal() - 3)) + 3;
  y = (rand() % (cons.get_vertical() - 3)) + 3;
  symbol = 'F';
}

void Food::food_print()
{
  gotoxy(x, y);
  printf("%c", symbol);
}

int Food::getFoodX() const
{
  return x;
}

int Food::getFoodY() const
{
  return y;
}

// TODO, make sure food doesn't intersect with snake
void Food::placeFood(Console& cons)
{
  x = (rand() % (cons.get_horizontal() - 3)) + 3;
  y = (rand() % (cons.get_vertical() - 3)) + 3;
}

void Food::gotoxy(int x, int y) const 
{
  printf("%c[%d;%df", 0x1B, y, x);
}