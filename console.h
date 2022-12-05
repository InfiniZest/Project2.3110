#ifndef CONSOLE_H
#define CONSOLE_H

class Console {
 private:
  int vertical;
  int horizontal;

 public:
  Console();
  ~Console();
  int get_horizontal();
  int get_vertical();
  void draw_borders();
  int kbhit();
  void gotoxy(int x, int y);
};

#endif
