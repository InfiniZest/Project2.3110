#include "console.h"
#include "Snake.h"
#include "Position.h"
#include "Food.h"
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <ncurses.h>

int main()
{
  int score = 0;

  /* class init */

  Console cons;
  Snake* snake = new Snake();
  Food food(cons);

  system("clear");
  system("stty -echo");
  curs_set(0);                    // makes console cursor invisible
  
  /* Draws snake, borders, and food in console */

  snake->snake_place();
  cons.draw_borders();
  bool isValidPosition;           // determines whether the food is not on top of the snake
  do 
  {
    isValidPosition = true;
    food.placeFood(cons);
    for (int i = 0; i < snake->getSize(); ++i)
    {
      if (snake->getSegmentOfSnakePositionAt(i).getX() == food.getFoodX() && snake->getSegmentOfSnakePositionAt(i).getY() == food.getFoodY())
      {
        isValidPosition = false;
      }
    }
  } while (!isValidPosition);

  food.food_print();

  /* use system call to make terminal send all keystrokes directly to stdin */

  system ("/bin/stty raw");

  while (!(snake->game_over(cons)))
  {

    /* while key not pressed */

    while (!(cons.kbhit()))
    {
      usleep(snake->getSnakeSpeed());
      snake->snake_move(cons, food, score);
      if (snake->game_over(cons))
      {
        break;
      }
    }

    /* store previous direction and fetch a new one */
    
    snake->setPrevDirection(snake->getDirection());
    snake->setDirection(getchar());
  }
  
  delete snake;
  
  /* use system call to set terminal behaviour to more normal behaviour */
  
  system("/bin/stty cooked");
  system("stty echo");
  system("clear");
  endwin();

  printf("\n\n Final score: %d \n\n", score);

  return 0;
}