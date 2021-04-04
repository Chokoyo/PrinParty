#ifndef CURSOR_H
#define CURSOR_H
#include <ncurses.h>
class Cursor
{
private:
    WINDOW *pwin;
    int x, y, x_max, y_max;
    char appearance;

public:
    Cursor(WINDOW *pwin, int y, int x, char appearance);
    int move();
    int get_y();
    int get_x();
    void move_up();
    void move_down();
    void move_left();
    void move_right();
    void printLoc();
};

#endif