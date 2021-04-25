#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <vector>
#include "playerforthirdgame.h"
#include <chrono>
using namespace std;
using namespace chrono;

struct candy
{
    int candyx;
    int candyy;
};

int candyGame(vector<int> score)
{
    initscr();
    raw();
    noecho();
    curs_set(0);
    int sumRmark = score[1];
    int sumLmark = score[0];
    for (int m = 0; m < 3; m++)
    {
        int Rmark = 0;
        int Lmark = 0;
        vector<candy> greencandies;
        vector<candy> redcandies;
        vector<candy> bluecandies;
        vector<candy> yellowcandies;
        if (!has_colors())
        {
            printw("This terminal doesn't support color display");
            getch();
            return -1;
        }
        start_color();
        init_pair(1, COLOR_BLACK, COLOR_GREEN);
        init_pair(2, COLOR_BLACK, COLOR_CYAN);
        init_pair(3, COLOR_BLACK, COLOR_RED);
        init_pair(4, COLOR_BLACK, COLOR_BLUE);
        init_pair(5, COLOR_BLACK, COLOR_YELLOW);

        int yMax, xMax;
        int thirdgwinyMax, thirdgwinxMax;
        getmaxyx(stdscr, yMax, xMax);

        WINDOW *thirdgwin = newwin(yMax, xMax / 2, 0, xMax / 4); //create a new window for game3
        getmaxyx(thirdgwin, thirdgwinyMax, thirdgwinxMax);
        box(thirdgwin, 0, 0); //get the border
        if (m == 0)
            mvwprintw(thirdgwin, thirdgwinyMax - 1, 2, "ROUND 1");
        else if (m == 1)
            mvwprintw(thirdgwin, thirdgwinyMax - 1, 2, "ROUND 2");
        else
            mvwprintw(thirdgwin, thirdgwinyMax - 1, 2, "ROUND 3");
        wattron(thirdgwin, A_REVERSE);
        mvwprintw(thirdgwin, thirdgwinyMax / 2, thirdgwinxMax / 2 - 13, "Press any key to continue!");
        wattroff(thirdgwin, A_REVERSE);
        wgetch(thirdgwin);
        mvwprintw(thirdgwin, thirdgwinyMax / 2, thirdgwinxMax / 2 - 13, "                          ");
        box(thirdgwin, 0, 0);
        if (m == 0)
            mvwprintw(thirdgwin, thirdgwinyMax - 1, 2, "ROUND 1");
        else if (m == 1)
            mvwprintw(thirdgwin, thirdgwinyMax - 1, 2, "ROUND 2");
        else
            mvwprintw(thirdgwin, thirdgwinyMax - 1, 2, "ROUND 3");
        refresh();
        wrefresh(thirdgwin);

        Player *R = new Player(thirdgwin, 1, 1, 'R');
        Player *L = new Player(thirdgwin, 1, 1, 'L');
        auto start = steady_clock::now();
        int record = 0;
        while (true)
        {
            record++;
            int a = 0;
            srand((unsigned)time(NULL));
            wattron(thirdgwin, COLOR_PAIR(1));
            int candyy = (rand() % (thirdgwinyMax - 3)) + 2;
            int candyx = (rand() % (xMax / 2 - 2)) + 1;
            candy thecandy;
            thecandy.candyx = candyx;
            thecandy.candyy = candyy;
            for (int i = 0; i < greencandies.size(); i++)
            {
                if (greencandies[i].candyx == candyx && greencandies[i].candyy == candyy)
                    a += 1;
            }
            if (a == 0)
            {
                greencandies.push_back(thecandy);
                mvwprintw(thirdgwin, candyy, candyx, "C");
                wrefresh(thirdgwin);
            }
            wattroff(thirdgwin, COLOR_PAIR(1));

            if (record % 3 == 0)
            {
                wattron(thirdgwin, COLOR_PAIR(3));
                candyy = (rand() % (thirdgwinyMax - 3)) + 2;
                candyx = (rand() % (xMax / 2 - 2)) + 1;
                thecandy.candyx = candyx;
                thecandy.candyy = candyy;
                for (int i = 0; i < redcandies.size(); i++)
                {
                    if (redcandies[i].candyx == candyx && redcandies[i].candyy == candyy)
                        a += 1;
                }
                if (a == 0)
                {
                    redcandies.push_back(thecandy);
                    mvwprintw(thirdgwin, candyy, candyx, "C");
                    wrefresh(thirdgwin);
                }
                wattroff(thirdgwin, COLOR_PAIR(3));
            }

            if (record % 7 == 0)
            {
                wattron(thirdgwin, COLOR_PAIR(4));
                candyy = (rand() % (thirdgwinyMax - 3)) + 2;
                candyx = (rand() % (xMax / 2 - 2)) + 1;
                thecandy.candyx = candyx;
                thecandy.candyy = candyy;
                for (int i = 0; i < bluecandies.size(); i++)
                {
                    if (bluecandies[i].candyx == candyx && bluecandies[i].candyy == candyy)
                        a += 1;
                }
                if (a == 0)
                {
                    bluecandies.push_back(thecandy);
                    mvwprintw(thirdgwin, candyy, candyx, "C");
                    wrefresh(thirdgwin);
                }
                wattroff(thirdgwin, COLOR_PAIR(4));
            }

            if (record % 17 == 0)
            {
                wattron(thirdgwin, COLOR_PAIR(5));
                candyy = (rand() % (thirdgwinyMax - 3)) + 2;
                candyx = (rand() % (xMax / 2 - 2)) + 1;
                thecandy.candyx = candyx;
                thecandy.candyy = candyy;
                for (int i = 0; i < yellowcandies.size(); i++)
                {
                    if (yellowcandies[i].candyx == candyx && yellowcandies[i].candyy == candyy)
                        a += 1;
                }
                if (a == 0)
                {
                    yellowcandies.push_back(thecandy);
                    mvwprintw(thirdgwin, candyy, candyx, "C");
                    wrefresh(thirdgwin);
                }
                wattroff(thirdgwin, COLOR_PAIR(5));
            }

            int choice = wgetch(thirdgwin);
            if (choice == 'p')
                break;
            if (choice == 'v')
                break;
            switch (choice)
            {
            case KEY_UP:
                R->mvup();
                R->display();
                break;
            case KEY_DOWN:
                R->mvdown();
                R->display();
                break;
            case KEY_LEFT:
                R->mvleft();
                R->display();
                break;
            case KEY_RIGHT:
                R->mvright();
                R->display();
                break;

            case 'w':
                L->mvup();
                L->display();
                break;
            case 's':
                L->mvdown();
                L->display();
                break;
            case 'a':
                L->mvleft();
                L->display();
                break;
            case 'd':
                L->mvright();
                L->display();
                break;

            default:
                break;
            }
            for (int i = 0; i < greencandies.size(); i++)
            {
                if (greencandies[i].candyx == R->getx() && greencandies[i].candyy == R->gety())
                {
                    greencandies[i].candyx = -1;
                    greencandies[i].candyy = -1;
                    Rmark += 1;
                }
            }
            for (int i = 0; i < greencandies.size(); i++)
            {
                if (greencandies[i].candyx == L->getx() && greencandies[i].candyy == L->gety())
                {
                    greencandies[i].candyx = -1;
                    greencandies[i].candyy = -1;
                    Lmark += 1;
                }
            }

            for (int i = 0; i < redcandies.size(); i++)
            {
                if (redcandies[i].candyx == R->getx() && redcandies[i].candyy == R->gety())
                {
                    redcandies[i].candyx = -1;
                    redcandies[i].candyy = -1;
                    Rmark += 2;
                }
            }
            for (int i = 0; i < redcandies.size(); i++)
            {
                if (redcandies[i].candyx == L->getx() && redcandies[i].candyy == L->gety())
                {
                    redcandies[i].candyx = -1;
                    redcandies[i].candyy = -1;
                    Lmark += 2;
                }
            }

            for (int i = 0; i < bluecandies.size(); i++)
            {
                if (bluecandies[i].candyx == R->getx() && bluecandies[i].candyy == R->gety())
                {
                    bluecandies[i].candyx = -1;
                    bluecandies[i].candyy = -1;
                    Rmark += 3;
                }
            }
            for (int i = 0; i < bluecandies.size(); i++)
            {
                if (bluecandies[i].candyx == L->getx() && bluecandies[i].candyy == L->gety())
                {
                    bluecandies[i].candyx = -1;
                    bluecandies[i].candyy = -1;
                    Lmark += 3;
                }
            }

            for (int i = 0; i < yellowcandies.size(); i++)
            {
                if (yellowcandies[i].candyx == R->getx() && yellowcandies[i].candyy == R->gety())
                {
                    yellowcandies[i].candyx = -1;
                    yellowcandies[i].candyy = -1;
                    Rmark += 10;
                }
            }
            for (int i = 0; i < yellowcandies.size(); i++)
            {
                if (yellowcandies[i].candyx == L->getx() && yellowcandies[i].candyy == L->gety())
                {
                    yellowcandies[i].candyx = -1;
                    yellowcandies[i].candyy = -1;
                    Lmark += 10;
                }
            }
            sumLmark += Lmark;
            sumRmark += Rmark;
            auto now = steady_clock::now();
            auto duration = duration_cast<seconds>(now - start);
            if (stoi(to_string(duration.count())) > 30)
            {
                break;
            }
        }
        wclear(thirdgwin);
        box(thirdgwin, 0, 0);
        wattron(thirdgwin, A_REVERSE);
        mvwprintw(thirdgwin, thirdgwinyMax / 2 - 1, thirdgwinxMax / 2 - 6, "LEFT PLAYER: ");
        mvwprintw(thirdgwin, thirdgwinyMax / 2 - 1, thirdgwinxMax / 2 + 8, to_string(sumLmark).c_str());
        mvwprintw(thirdgwin, thirdgwinyMax / 2 + 1, thirdgwinxMax / 2 - 6, "RIGHT PLAYER: ");
        mvwprintw(thirdgwin, thirdgwinyMax / 2 + 1, thirdgwinxMax / 2 + 9, to_string(sumRmark).c_str());
        wattroff(thirdgwin, A_REVERSE);
        wrefresh(thirdgwin);
        sleep(5);

        clear();
        refresh();
    }
    endwin();
    return 0;
}

int main(int argc, char *argv[])
{
    string score1 = argv[1], score2 = argv[2];
    candyGame({stoi(score1), stoi(score2)});
    return 0;
}