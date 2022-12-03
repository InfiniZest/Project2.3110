#include "Food.h"
#include <stdio.h>

Food::Food(Console& cons)
{
    x = (rand() % (cons.get_horizontal() - 5)) + 1;
    y = (rand() % (cons.get_vertical() - 5)) + 1;
    symbol = 'F';
    this->cons = cons;
}

void Food::food_print()
{
  cons.gotoxy(x, y);
  printf("%c", symbol);
}
