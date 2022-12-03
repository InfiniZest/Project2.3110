#ifndef FOOD_H
#define FOOD_H

class Food
{
public:
    Food(Console& cons);

private:
  int x;
  int y;
  char symbol;
  Console cons;
};


#endif