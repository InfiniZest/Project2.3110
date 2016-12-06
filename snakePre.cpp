/*****************************************
*  Project2:snakePre.cpp (snake_c.cpp)   *
*             CISC3110-TTH               *
*            Name:Imran Khan             *
******************************************/

#include "console.h"
#include <cstdlib>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <ncurses.h>

// No destructors have been given to any of the classes
// since I couldn't figure an argument required other
// than a cout statement.
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
    Console direct;

    snake();
};

class snake_pos {
public:
    static const int vertical = 40;      //
    static const int horizontal = 200;   //
    static const int down = 115;         // Originally MACROS, unsure if done
    static const int up = 119;           // correctly as asked
    static const int left = 97;          //
    static const int right = 100;        //

    int Y[(size_t)1 * vertical*horizontal];
    int X[(size_t)1 * vertical*horizontal];
    snake x;

    snake_pos(void);
    void snake_place(snake *, int *, int *);
};

class food {
public:
    int X;
    int Y;
    char symbol;
    snake x2;
    snake_pos y;

    food();
    void food_print(int *, int *, char *);
    void snake_move(snake *, snake_pos *, int *, int *, char *, int *);
    void move_head(snake *, snake_pos *);
    void move_tail(snake *, snake_pos *);
};

class misc {
public:
    snake x3;
    snake_pos y1;

    int game_over(snake *, snake_pos *);
};

int main() {
    int snake_speed = 100000;
    int score = 0;
    Console cons;

    snake snake1;
    snake_pos pos1;
    food food1;
    misc misc1;

    system("clear");
    system("stty -echo");
    curs_set(0);
    pos1.snake_place(&snake1, pos1.X, pos1.Y);

    // Borders has not filled corners with Xs.
    cons.draw_borders();

    // Food_print has not been fixed from preventing collisions with the snake and borders.
    food1.food_print(&food1.X, &food1.Y, &food1.symbol);

    system ("/bin/stty raw");

    while(!(misc1.game_over(&snake1, &pos1))) {
        while (!(cons.kbhit())) {
            usleep(snake_speed);
            food1.snake_move(&snake1, &pos1, &food1.X, &food1.Y, &food1.symbol, &score);
            if(misc1.game_over(&snake1, &pos1)) {
                break;
            }
        }

        snake1.prev_direction = snake1.direction;
        snake1.direction = getchar();
    }

    system ("/bin/stty cooked");
    system("stty echo");
    system("clear");
    printf("\n\n Final score: %d \n\n", score);

    return 0;
}

snake::snake() {
    snake_pos *a;
    symbol = '*';
    size = 10;
    direction = a->right;
    prev_direction = a->down;
    tail_X = 5;
    tail_Y = 5;
    head_X = tail_X+size-1;
    head_Y = 5;
}

snake_pos::snake_pos() {
    memset(X, 0, sizeof(*X));
    memset(Y, 0, sizeof(*Y));
}

void snake_pos::snake_place(snake *x1, int *X, int *Y) {
    int i;
    Console cons1;

    for (i = 0; i<x1->size; i++)
    {
        cons1.gotoxy(x1->tail_X, x1->tail_Y);
        printf("%c", x1->symbol);
        X[i] = x1->tail_X;
        Y[i] = x1->tail_Y;
        x1->tail_X+=1;
    }
}

int misc::game_over(snake *x3, snake_pos *y1) {
    int i;

    for(i = 0; i<x3->size-1; ++i) {

        if ((y1->X[i] == x3->head_X) && (y1->Y[i] == x3->head_Y))
        {
            return 1;
        }
    }

    if ((x3->head_X == y1->horizontal) || (x3->head_X == 1) || (x3->head_Y == y1->vertical) || (x3->head_Y == 1))
        {
            return 1;
        }

    return 0;
}

food::food() {
    snake x;
    snake_pos *y;
    X = (rand()%(y->horizontal-5))+1;
    Y = (rand()%(y->vertical-5))+1;
    symbol = 'F';
}

void food::food_print(int *X, int*Y, char *symbol) {
    Console cons2;
    cons2.gotoxy(*X,*Y);
    printf("%c", *symbol);
}

void food::snake_move(snake *x2, snake_pos *y, int *X, int *Y, char *symbol, int *score) {
    move_head(x2,y);

    if (!((x2->head_X == *X) && (x2->head_Y == *Y))) {
        move_tail(x2, y);
    }
    else {
        x2->size++;
        *score = *score+1;
        *X = rand()%(y->horizontal-5);
        *Y = rand()%(y->vertical-5);
        food_print(X, Y, symbol);
    }
}

void food::move_tail(snake *x2, snake_pos *y) {  /*******************************/
    int i;                                       // The tail prints the key     //
    Console cons3;                               // pressed within the terminal //
                                                 // only if WSAD (controls) are //
    // remove last cell of tail                  // pressed                     //
    cons3.gotoxy(y->X[0],y->Y[0]);               //******************************/
    printf(" ");


    // update new tail position
    for (i = 0; i<x2->size; ++i)
    {
        y->X[i]=y->X[i+1];
        y->Y[i]=y->Y[i+1];
    }
}

void food::move_head(snake *x2, snake_pos *y) {
    Console cons4;

    switch (x2->direction)
    {
    case y->right:
        if (x2->prev_direction == y->left)
        {
            x2->head_X--;
            break;
        }
        x2->head_X++;
        break;

    case y->left:
        if (x2->prev_direction == y->right)
        {
            x2->head_X++;
            break;
        }
        x2->head_X--;
        break;


    case y->up:
        if (x2->prev_direction == y->down)
        {
            x2->head_Y++;
            break;
        }
        x2->head_Y--;
        break;


    case y->down:
        if (x2->prev_direction == y->up)
        {
            x2->head_Y--;
            break;
        }
        x2->head_Y++;
        break;


    default:
        break;
    }

    y->X[x2->size] = x2->head_X;
    y->Y[x2->size] = x2->head_Y;

    cons4.gotoxy(y->X[x2->size],y->Y[x2->size]);
    printf("%c",x2->symbol);
}
