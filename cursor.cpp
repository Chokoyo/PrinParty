#include "cursor.h"
#include <ncurses.h>
using namespace std;

WINDOW *pwin;
int x, y, x_max, y_max;
char appearance;

Cursor::Cursor(WINDOW *pwin, int y, int x, char appearance)
{
    this->pwin = pwin;
    this->y = y;
    this->x = x;
    this->appearance = appearance;
    getmaxyx(pwin, y_max, x_max);
    keypad(pwin, true);
}

int Cursor::get_y()
{
    return y;
}
int Cursor::get_x()
{
    return x;
}

void Cursor::move_up()
{
    y--;
    if (y == 0)
        y = 1;
}

void Cursor::move_down()
{
    y++;
    if (y > y_max - 2)
        y = y_max - 2;
}

void Cursor::move_left()
{
    x--;
    if (x == 0)
        x = 1;
}

void Cursor::move_right()
{
    x++;
    if (x > x_max - 2)
        x = x_max - 2;
}
int Cursor::move()
{
    int input = wgetch(pwin);
    mvwaddch(pwin, y, x, ' ');
    switch (input)
    {
    case KEY_UP:
        move_up();
        break;
    case KEY_DOWN:
        move_down();
        break;
    case KEY_LEFT:
        move_left();
        break;
    case KEY_RIGHT:
        move_right();
        break;
    }
    return input;
}
void Cursor::printLoc()
{
    mvwaddch(pwin, y, x, appearance);
    wrefresh(pwin);
}