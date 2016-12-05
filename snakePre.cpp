#include "console.h"

#include <iostream>
#include <cstdlib>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <ncurses.h>

using namespace std;

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
public:
    snake();
    ~snake() {
        cout<<"the destructor is running" << size << endl;
    }
};

class snake_pos {
public:
    int Y[40*200];
    int X[40*200];
    snake x;
public:
    snake_pos();
    void snake_place(snake *, int *, int *);
    int game_over(snake *, int *, int *);
};

class food {
public:
    int X;
    int Y;
    char symbol;
    snake x2;
    snake_pos y;
public:
    food();
    void food_print(int *, int *, char *);
    void snake_move(snake *, snake_pos *, int *, int *, char *, int *);
};

class misc {
public:
    snake x3;
    snake_pos y1;
public:
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
    cons.draw_borders();
    food1.food_print(&food1.X, &food1.Y, &food1.symbol);

    system ("/bin/stty raw");
    while(!(pos1.game_over(&snake1, pos1.X, pos1.Y))) {
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
    symbol = '*';
    size = 10;
    direction = direct.get_horizontal();
    prev_direction = direct.get_vertical();
    tail_X = 5;
    tail_Y = 5;
    head_X = tail_X+size-1;
    head_Y = 5;
    cout << "This constructor is running" << tail_X << tail_Y << head_X << symbol << size << direction << prev_direction <<  endl;
}

snake_pos::snake_pos() {
    memset(X, 0, sizeof(*X));
    memset(Y, 0, sizeof(*Y));
    cout << "Snake_pos constructor running" <<endl;
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

int misc::game_over(snake *x1, int *X, int *Y) {

    int i;

    for(i = 0; i<x1->size-1; ++i) {

        if ((X[i]==x1->head_X) && (Y[i]==x1->head_Y))
        {
            return 1;
        }
    }

    if ((x1->head_X==200) || (x1->head_X==1) || (x1->head_Y==40) || (x1->head_Y==1))
        {
            return 1;
        }

    return 0;
}

food::food() {
    X = (rand()%(200-5))+1;
    Y = (rand()%(40-5))+1;
    symbol = 'F';
    cout << X << Y << symbol << "The food constructor is running" <<endl;
}

void food::food_print(int *X, int*Y, char *symbol) {
    Console cons2;
    cons2.gotoxy(*X,*Y);
    printf("%c", *symbol);
}

void food::snake_move(snake *x2, snake_pos *y, int *X, int *Y, char *symbol, int *score) {
    void move_head(snake, snake_pos);

    if (!((x2->head_X==*X) && (x2->head_Y==*Y))) {
        void move_tail(snake, snake_pos);
    }
    else {
        x2->size++;
        *score = *score+1;
        y->X = rand()%(195);
        y->Y = rand()%(35);
        food_print(X, Y, symbol);
    }
}

void move_tail(snake *x2, snake_pos *y) {
    int i;
    Console cons3;

    // remove last cell of tail
    cons3.gotoxy(y->X[0],y->Y[0]);
    printf(" ");


    // update new tail position
    for (i=0; i<x2->size; ++i)
    {
        y->X[i]=y->X[i+1];
        y->Y[i]=y->Y[i+1];
    }
}

void move_head(snake *x2, snake_pos *y) {
    Console cons4;

    switch (x2->direction)
    {
    case 100:
        if (x2->prev_direction==97)
        {
            x2->head_X--;
            break;
        }
        x2->head_X++;
        break;

    case 97:
        if (x2->prev_direction==100)
        {
            x2->head_X++;
            break;
        }
        x2->head_X--;
        break;


    case 119:
        if (x2->prev_direction==115)
        {
            x2->head_Y++;
            break;
        }
        x2->head_Y--;
        break;


    case 115:
        if (x2->prev_direction==119)
        {
            x2->head_Y--;
            break;
        }
        x2->head_Y++;
        break;


    default:
        break;
    }

    y->X[x2->size]=x2->head_X;
    y->Y[x2->size]=x2->head_Y;

    cons4.gotoxy(y->X[x2->size],y->Y[x2->size]);
    printf("%c",x2->symbol);
}
