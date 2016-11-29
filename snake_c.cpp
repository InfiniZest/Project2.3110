#include "console.h"

#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <ncurses.h>


#define vertical 40
#define horizontal 200
#define down 115
#define up 119
#define left 97
#define right 100

class snake {
public:
  char symbol;
  int size;
  char direction;
  char prev_direction;
  int tail_X;
  int tail_Y;
  int head_X;
  int head_Y;

  // void snake_init(snake *snake1); Must use this as a constructor
    snake(snake *sanke1);
    snake();
  };

class snake_pos {
private:
    int Y[vertical*horizontal];
    int X[vertical*horizontal];

public:
  //void pos_init(snake_pos *pos1); Must use this as a constructor
    snake_pos(snake_pos *pos1);
    snake_pos();
    int game_over(snake *snake1, snake_pos *pos1);
    void snake_place(snake *snake1, snake_pos *pos1);
    void move_tail(snake *snake1, snake_pos *pos1);
    void move_head(snake *snake1, snake_pos *pos1);
};

class food {
private:
  int X;
  int Y;
  char symbol;
public:
  //void food_init(food *food1);  //Must use this as a constructor
    food(food *food1);
    food();
    void food_print(food *food1);
    void snake_move(snake *snake1, snake_pos *pos1, food *food1, int*);
};

class borders {
public:
    void set_borders();
};

class gameScore {
public:
    void print_score(int*);
};

// int kbhit(void);

int main()
{
  int snake_speed=100000;
  int score=0;

  Console cons;


  /* struct init */

  snake snake1;
  snake_pos pos1;
  food food1;
  //snake_init(&snake1);
  //pos_init(&pos1);
  //food_init(&food1);


  /* set initial field */

  system("clear");
  system("stty -echo");
  curs_set(0);                    // doesn't work for some reason
  //snake_place(&snake1,&pos1);
  pos1.snake_place(&snake1, &pos1);
  cons.draw_borders();
  //food_print(&food1);
  food1.food_print(&food1);


  /* use system call to make terminal send all keystrokes directly to stdin */

  system ("/bin/stty raw");


  /* while snake not got collided into itself */

  //while(!(game_over(&snake1,&pos1)))
  while(!(pos1.game_over(&snake1,&pos1))) {

      /* while key not pressed */

      while ( !(cons.kbhit()) )
        {
          usleep(snake_speed);
          //snake_move(&snake1,&pos1,&food1,&score);
          food1.snake_move(&snake1,&pos1,&food1,&score);
          //if (game_over(&snake1,&pos1))
          if (pos1.game_over(&snake1,&pos1))
            {
              break;
            }

        }
      /* store previous direction and fetch a new one */

      snake1.prev_direction=snake1.direction;
      snake1.direction=getchar();
  }

  /* use system call to set terminal behaviour to more normal behaviour */
  system ("/bin/stty cooked");
  system("stty echo");
  system("clear");
  printf("\n\n Final score: %d \n\n", score);



  return 0;

}

//void snake_init(snake *snake1) Must create this as constructor definition
snake::snake(snake *snake1) {
  snake1->symbol='*';
  snake1->size=10;
  snake1->direction=right;
  snake1->prev_direction=down;
  snake1->tail_X=5;
  snake1->tail_Y=5;
  snake1->head_X=snake1->tail_X+snake1->size-1;
  snake1->head_Y=5;
}

void snake_pos::snake_place(snake *snake1, snake_pos *pos1) {
    int i;
    for (i=0; i<snake1->size; ++i)
    {
      printf("%c",snake1->symbol);
      pos1->X[i]=snake1->tail_X;
      pos1->Y[i]=snake1->tail_Y;
      snake1->tail_X+=1;
    }

}

void borders::set_borders() {
  int i;
  for (i=0; i<vertical; ++i)
    {
      printf("X");
      printf("X");
    }

  for (i=0; i<horizontal; ++i)
    {
      printf("X");
      printf("X");
    }
}

void food::snake_move(snake *snake1, snake_pos *pos1, food *food1, int *score) {
  move_head(snake1,pos1);

  if (!((snake1->head_X==food1->X) && (snake1->head_Y==food1->Y)))
    {
        //move_tail(snake1,pos1);
        pos1->move_tail(snake1,pos1);
    }
  else
    {
      snake1->size++;
      *score=*score+1;
      food1->X=rand()%(horizontal-5);
      food1->Y=rand()%(vertical-5);
      food_print(food1);
    }
}

void snake_pos::move_tail(snake *snake1, snake_pos *pos1) {
  int i;

  // remove last cell of tail
  printf(" ");


  // update new tail position
  for (i=0; i<snake1->size; ++i)
    {
      pos1->X[i]=pos1->X[i+1];
      pos1->Y[i]=pos1->Y[i+1];
    }
}

void snake_pos::move_head(snake *snake1, snake_pos *pos1) {
  switch (snake1->direction)
    {
    case right:
      if (snake1->prev_direction==left)
        {
          snake1->head_X--;
          break;
        }
      snake1->head_X++;
      break;

    case left:
      if (snake1->prev_direction==right)
        {
          snake1->head_X++;
          break;
        }
      snake1->head_X--;
      break;


    case up:
      if (snake1->prev_direction==down)
        {
          snake1->head_Y++;
          break;
        }
      snake1->head_Y--;
      break;


    case down:
      if (snake1->prev_direction==up)
        {
          snake1->head_Y--;
          break;
        }
      snake1->head_Y++;
      break;


    default:
      break;
    }


  // update tail position
  pos1->X[snake1->size]=snake1->head_X;
  pos1->Y[snake1->size]=snake1->head_Y;

  gotoxy(pos1->X[snake1->size],pos1->Y[snake1->size]);
  printf("%c",snake1->symbol);
}

//void food::food_init(food *food1) { Create constructor definition
food::food(food *food1) {
  food1->X=(rand()%(horizontal-5))+1;
  food1->Y=(rand()%(vertical-5))+1;
  food1->symbol='F';
}

void food::food_print(food *food1) {
  printf("%c",food1->symbol);
}

//void pos_init(snake_pos *pos1) Create constructor definition
snake_pos::snake_pos(snake_pos *pos1)
{
  memset(pos1, 0, sizeof(*pos1));
}


int snake_pos::game_over(snake *snake1, snake_pos *pos1)
{
  int i;

  for (i=0; i<snake1->size-1; ++i)
    {
      if ((pos1->X[i]==snake1->head_X) && (pos1->Y[i]==snake1->head_Y))
        {
          return 1;
        }
    }

  if ((snake1->head_X==horizontal) || (snake1->head_X==1) || (snake1->head_Y==vertical) || (snake1->head_Y==1))
    {
      return 1;
    }


  return 0;
}

/*

int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
    {
      ungetc(ch, stdin);
      return 1;
    }

  return 0;
}
*/
