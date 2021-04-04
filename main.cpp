#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <fstream>
#include "cursor.h"
using namespace std;

void printwin(WINDOW *win);

int main()
{
    // initalize ncurses
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    raw();
    curs_set(0);
    if (!has_colors())
    {
        printw("This terminal doesn't support color display");
        getch();
        return -1;
    }

    // vairable declearation
    int stage = 0, input = 0, y = 0, x = 0, y_max, x_max;
    string menu[3][5] = {{"Party mode", "Single game", "Quick start", "Load game", "Back"},
                         {"1. game",
                          "2. game",
                          "3. game",
                          "4. game",
                          "Back"},
                         {}};
    WINDOW *win = newwin(20, 60, 0, 0); /*newwin(height, width, y, x)*/
    getmaxyx(win, y_max, x_max);
    printwin(win);
    keypad(win, true);
    Cursor *pcursor = new Cursor(win, 1, 1, '@');

    while (1)
    {
        switch (stage)
        {
        case 0: // start page
            printwin(win);
            mvwprintw(win, 8, 13, "█▀█ █▀█ █ █▄ █ █▀█ ▄▀█ █▀█ ▀█▀ █▄█");
            mvwprintw(win, 9, 13, "█▀▀ █▀▄ █ █ ▀█ █▀▀ █▀█ █▀▄  █   █ ");
            wattron(win, A_STANDOUT);
            mvwprintw(win, 14, 18, "Press any key to begin");
            wattroff(win, A_STANDOUT);
            wrefresh(win);
            wgetch(win);
            stage++;
        case 1: // menu page
            printwin(win);
            for (int i = 0; i < 5; i++)
            {
                mvwprintw(win, i + 1, 5, menu[0][i].c_str());
            }
            y = 1;
            mvwprintw(win, y, 2, "➤");
            while (1)
            {
                input = wgetch(win);
                if (input == 10) // 10 present the enter key
                {
                    stage = y + 1;
                    break;
                }
                mvwprintw(win, y, 2, "  ");
                switch (input)
                {
                case KEY_UP:
                    y--;
                    if (y == 0)
                        y = 1;
                    break;
                case KEY_DOWN:
                    y++;
                    if (y > 5)
                        y = 5;
                    break;

                default:
                    break;
                }
                mvwprintw(win, y, 2, "➤");
                wrefresh(win);
            }
            if (stage == 6)
                stage = 0;
            continue;
        case 2: // party game page
            break;
        case 3: // single game page
            printwin(win);
            for (int i = 0; i < 5; i++)
            {
                mvwprintw(win, i + 1, 5, menu[1][i].c_str());
            }
            y = 1;
            mvwprintw(win, y, 2, "➤");
            while (1)
            {
                input = wgetch(win);
                if (input == 10) // 10 present the enter key
                {
                    stage = y + 5;
                    break;
                }
                mvwprintw(win, y, 2, "  ");
                switch (input)
                {
                case KEY_UP:
                    y--;
                    if (y == 0)
                        y = 1;
                    break;
                case KEY_DOWN:
                    y++;
                    if (y > 5)
                        y = 5;
                    break;

                default:
                    break;
                }
                mvwprintw(win, y, 2, "➤");
                wrefresh(win);
            }
            if (stage == 10)
                stage = 1;
            continue;
        case 4: // quick start page
            printwin(win);
            pcursor->printLoc();
            while (pcursor->move() != 'x')
            {
                pcursor->printLoc();
            }
            break;
        case 5: // load game page
            break;
        case 6: // Game 1:
            break;
        case 6: // Game 2:
            break;
        case 6: // Game 3:
            break;
        case 6: // Game 4:
            break;
        case 10: // test page
            printwin(win);

            while (pcursor->move() != 'x')
            {
                pcursor->printLoc();
            }
            break;
        default:
            break;
        }
        break;
    }

    getch();
    endwin();
    return 0;
}

void printwin(WINDOW *win)
{
    wclear(win);
    box(win, 0, 0);
    refresh();
    wrefresh(win);
}