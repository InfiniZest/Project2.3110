#include "console.h"
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <ncurses.h>
#include <locale.h>

Console::Console() {
  initscr();
  setlocale(LC_CTYPE, "");
  getmaxyx(stdscr, vertical, horizontal);
}

Console::~Console() {
  endwin();
}

int Console::get_horizontal() {
  return horizontal;
}

int Console::get_vertical() {
  return vertical;
}

void Console::draw_borders() {

  for (int i=0; i<vertical; ++i)
    {
      gotoxy(0,i);
      printf("X");
      gotoxy(horizontal - 20,i + 1);
      printf("X");
      gotoxy(horizontal,i + 1);
      printf("X");
    }

  for (int i=0; i<horizontal; ++i)
    {
      gotoxy(i,0);
      printf("X");
      gotoxy(i + 1,vertical);
      printf("X");
    }
}

void Console::draw_labels()
{
  gotoxy(horizontal - 18, 3);
  printf("Score: 0");
  gotoxy(horizontal - 18, 6);
  printf("Controls:");
  gotoxy(horizontal - 18, 7);
  printf("W -> Move up");
  gotoxy(horizontal - 18, 8);
  printf("S -> Move down");
  gotoxy(horizontal - 18, 9);
  printf("A -> Move left");
  gotoxy(horizontal - 18, 10);
  printf("D -> Move right");
}

void Console::update_score(int score)
{
  gotoxy(horizontal - 11, 3);
  if (score > 9999999999)
  {
    printf("∞");  
  } else
  {
    printf("%d", score);
  }
}

int Console::kbhit()
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


void Console::gotoxy(int x, int y) {
  printf("%c[%d;%df",0x1B,y,x);
}
