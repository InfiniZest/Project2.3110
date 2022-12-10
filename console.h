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
  void draw_labels();
  void update_score(int score);
  int kbhit();
  void gotoxy(int x, int y);
};

#endif
