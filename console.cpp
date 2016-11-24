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
      gotoxy(horizontal,i);
      printf("X");
 p   }

  for (int i=0; i<horizontal; ++i)
    {
      gotoxy(i,0);
      printf("X");
      gotoxy(i,vertical);
      printf("X");
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
