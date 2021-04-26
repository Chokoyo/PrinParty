// Author: Wang Sinan
// U. No.: 3035770599
// ENGG1340 Group Project
// File Name: maze.cpp
// Description: The two players will need to move from the upper left corner to the bottom right corner.
#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <vector>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <locale.h>
#include "player4game.h"
#include <chrono>
using namespace std;
using namespace chrono;
#define down 1
#define right 2
#define left 3
#define up 4
//reference: the algorithm of prim to generate the maze(link: https://www.zhangshengrong.com/p/YjNKnj67aW/)
struct block_info //define a struct to store the information of block
{
    int row;
    int column;
    int direct;
};

vector<block_info> blocks;

struct point
{
    int x;
    int y;
};

void init(vector<vector<int>> a, int m, int n)
{
    for (int i = 0; i <= m + 1; i++)
    {
        for (int j = 0; j <= n + 1; j++)
        {
            a[i][j] = 1; //initialize the vector of blocks
        }
    }
}

void push(int x, int y, int direct)
{
    blocks.push_back({x, y, direct});
}

void calculate(int x_num, int y_num, int m, int n)
{ //add information about the blocks around according to the current location
    if (x_num + 1 <= m)
    {
        push(x_num + 1, y_num, down);
    } //down
    if (y_num + 1 <= n)
    {
        push(x_num, y_num + 1, right);
    } //right
    if (x_num - 1 >= 1)
    {
        push(x_num - 1, y_num, up);
    } //up
    if (y_num - 1 >= 1)
    {
        push(x_num, y_num - 1, left);
    } //left
}

int maze(vector<int> score)
{
    setlocale(LC_ALL, "");
    initscr();
    raw();
    noecho();
    curs_set(0);
    int sumRmark = score[1];
    int sumLmark = score[0];
    int x_num;
    int y_num;
    for (int q = 0; q < 3; q++)
    { //determine the size of the maze according to the round of the game
        x_num = 1;
        y_num = 1;
        int m;
        int n;
        vector<vector<int>> a;
        if (q == 0)
        {
            m = 11;
            n = 23;
        }
        else if (q == 1)
        {
            m = 13;
            n = 25;
        }
        else
        {
            m = 15;
            n = 27;
        }

        int Rmark = 0;
        int Lmark = 0;

        for (int i = 0; i < m + 2; i++)
        {
            a.push_back({});
        }

        for (int i = 0; i < m + 2; i++)
        {
            for (int j = 0; j < n + 2; j++)
            {
                a[i].push_back(1);
            }
        }
        if (!has_colors())
        {
            printw("This terminal doesn't support color display");
            getch();
            return -1;
        }
        start_color();
        init_pair(1, COLOR_BLACK, COLOR_CYAN);
        init_pair(2, COLOR_BLACK, COLOR_GREEN);

        int yMax, xMax;
        int thirdgwinyMax, thirdgwinxMax;
        thirdgwinyMax = m + 4;
        thirdgwinxMax = n + 4;
        getmaxyx(stdscr, yMax, xMax);
        WINDOW *thirdgwin = newwin(m + 4, n + 4, 0, n + 8); //create a new window for game4
        box(thirdgwin, 0, 0);
        if (q == 0) //show the round number
            mvwprintw(thirdgwin, thirdgwinyMax - 1, 2, "ROUND 1");
        else if (q == 1)
            mvwprintw(thirdgwin, thirdgwinyMax - 1, 2, "ROUND 2");
        else
            mvwprintw(thirdgwin, thirdgwinyMax - 1, 2, "ROUND 3");
        WINDOW *Lwin = newwin(m + 4, n + 4, 0, 0);
        box(Lwin, 0, 0);
        if (q == 0)
            mvwprintw(Lwin, thirdgwinyMax - 1, 2, "ROUND 1");
        else if (q == 1)
            mvwprintw(Lwin, thirdgwinyMax - 1, 2, "ROUND 2");
        else
            mvwprintw(Lwin, thirdgwinyMax - 1, 2, "ROUND 3");
        wattron(Lwin, A_REVERSE);
        mvwprintw(Lwin, thirdgwinyMax / 2, thirdgwinxMax / 2 - 13, "Press any key to continue!");
        wattroff(Lwin, A_REVERSE);
        wattron(thirdgwin, A_REVERSE);
        mvwprintw(thirdgwin, thirdgwinyMax / 2, thirdgwinxMax / 2 - 13, "Press any key to continue!");
        wattroff(thirdgwin, A_REVERSE);
        wrefresh(thirdgwin);
        wgetch(Lwin); //wait for the user to type in
        mvwprintw(Lwin, thirdgwinyMax / 2, thirdgwinxMax / 2 - 13, "                          ");
        mvwprintw(thirdgwin, thirdgwinyMax / 2, thirdgwinxMax / 2 - 13, "                          ");
        box(Lwin, 0, 0);
        box(thirdgwin, 0, 0);
        if (q == 0)
            mvwprintw(thirdgwin, thirdgwinyMax - 1, 2, "ROUND 1");
        else if (q == 1)
            mvwprintw(thirdgwin, thirdgwinyMax - 1, 2, "ROUND 2");
        else
            mvwprintw(thirdgwin, thirdgwinyMax - 1, 2, "ROUND 3");
        if (q == 0)
            mvwprintw(Lwin, thirdgwinyMax - 1, 2, "ROUND 1");
        else if (q == 1)
            mvwprintw(Lwin, thirdgwinyMax - 1, 2, "ROUND 2");
        else
            mvwprintw(Lwin, thirdgwinyMax - 1, 2, "ROUND 3");

        point startpoint;
        point end; //initialize the start point
        startpoint.x = 1;
        startpoint.y = 1;
        end.x = m;
        end.y = n;
        init(a, m, n);
        srand((unsigned)time(NULL));
        calculate(x_num, y_num, m, n);
        a[1][1] = 2; //remove the first block
        while (blocks.size())
        {
            int num = blocks.size();
            int randnum = rand() % num;
            x_num = blocks[randnum].row;
            y_num = blocks[randnum].column;
            //move the current location according to the direction
            switch (blocks[randnum].direct)
            {
            case down:
            {
                x_num = blocks[randnum].row + 1;
                y_num = blocks[randnum].column;
                break;
            }
            case right:
            {
                x_num = blocks[randnum].row;
                y_num = blocks[randnum].column + 1;
                break;
            }
            case left:
            {
                x_num = blocks[randnum].row;
                y_num = blocks[randnum].column - 1;
                break;
            }
            case up:
            {
                x_num = blocks[randnum].row - 1;
                y_num = blocks[randnum].column;
                break;
            }
            }
            if (a[x_num][y_num] == 1)
            { //if the point is a block, we remove both blocks
                a[blocks[randnum].row][blocks[randnum].column] = 2;
                a[x_num][y_num] = 2;
                calculate(x_num, y_num, m, n); //update information in the block_info
            }
            blocks.erase(blocks.begin() + randnum); //delete the randum-th element in the block vector
        }
        //show the maze in the window according to the block vector
        for (int i = 0; i < m + 2; i++)
        {
            for (int j = 0; j < n + 2; j++)
            {
                if (a[i][j] == 1)
                {
                    mvwprintw(thirdgwin, i + 1, j + 1, "█");
                }
            }
        }
        for (int i = 0; i < m + 2; i++)
        {
            for (int j = 0; j < n + 2; j++)
            {
                if (a[i][j] == 2)
                {
                    mvwprintw(thirdgwin, i + 1, j + 1, " ");
                }
            }
        }

        for (int i = 0; i < m + 2; i++)
        {
            for (int j = 0; j < n + 2; j++)
            {
                if (a[i][j] == 1)
                {
                    mvwprintw(Lwin, i + 1, j + 1, "█");
                }
            }
        }

        for (int i = 0; i < m + 2; i++)
        {
            for (int j = 0; j < n + 2; j++)
            {
                if (a[i][j] == 2)
                {
                    mvwprintw(Lwin, i + 1, j + 1, " ");
                }
            }
        }
        refresh();
        wrefresh(thirdgwin);
        wrefresh(Lwin);
        wattron(thirdgwin, COLOR_PAIR(1));
        mvwprintw(thirdgwin, 2, 2, "R");
        wattroff(thirdgwin, COLOR_PAIR(1));

        wattron(Lwin, COLOR_PAIR(2));
        mvwprintw(Lwin, 2, 2, "L");
        wattroff(Lwin, COLOR_PAIR(2));
        wrefresh(Lwin);
        wrefresh(thirdgwin);
        //declare two players to move
        Player *R = new Player(thirdgwin, Lwin, 2, 2, 'R');
        Player *L = new Player(thirdgwin, Lwin, 2, 2, 'L');
        //record the start time
        auto start = steady_clock::now();
        mvprintw(m + 4, n + 1, "⇧");
        mvprintw(m + 4, 2 * n + 9, "⇧");
        refresh();
        while (true)
        {

            int choice = wgetch(thirdgwin);
            if (choice == 'p')
                break;
            if (choice == 'v')
                break;
            //if anyone of the player has reached the destination, we give a higher score to that player
            if (R->getx() == n + 1 && R->gety() == m + 1)
            {
                Rmark = 6;
                Lmark = 3;
                break;
            }

            if (L->getx() == n + 1 && L->gety() == m + 1)
            {
                Rmark = 3;
                Lmark = 6;
                break;
            }
            //let the player to move
            switch (choice)
            {
            case KEY_UP:
                if (a[R->gety() - 2][R->getx() - 1] != 1)
                {
                    R->mvup();
                    R->display();
                    break;
                }
                else
                    break;
            case KEY_DOWN:
                if (a[R->gety()][R->getx() - 1] != 1)
                {
                    R->mvdown();
                    R->display();
                    break;
                }
                else
                    break;
            case KEY_LEFT:
                if (a[R->gety() - 1][R->getx() - 2] != 1)
                {
                    R->mvleft();
                    R->display();
                    break;
                }
                else
                    break;
            case KEY_RIGHT:
                if (a[R->gety() - 1][R->getx()] != 1)
                {
                    R->mvright();
                    R->display();
                    break;
                }
                else
                    break;

            case 'w':
                if (a[L->gety() - 2][L->getx() - 1] != 1)
                {
                    L->mvup();
                    L->display();
                    break;
                }
                else
                    break;

            case 's':

                if (a[L->gety()][L->getx() - 1] != 1)
                {
                    L->mvdown();
                    L->display();
                    break;
                }
                else
                    break;

            case 'a':

                if (a[L->gety() - 1][L->getx() - 2] != 1)
                {
                    L->mvleft();
                    L->display();
                    break;
                }
                else
                    break;

            case 'd':

                if (a[L->gety() - 1][L->getx()] != 1)
                {
                    L->mvright();
                    L->display();
                    break;
                }
                else
                    break;

            default:
                break;
            }
            wrefresh(thirdgwin);
            wrefresh(Lwin);
            //record the current time
            auto now = steady_clock::now();
            auto duration = duration_cast<seconds>(now - start);
            //if the time is up, the round ends and no one gets scores
            if (stoi(to_string(duration.count())) > 60)
            {
                break;
            }
        }
        //add every round's scores to the total score
        sumLmark += Lmark;
        sumRmark += Rmark;
        wclear(thirdgwin);
        wclear(Lwin);
        box(thirdgwin, 0, 0);
        box(Lwin, 0, 0);
        mvprintw(m + 4, n + 1, " ");
        mvprintw(m + 4, 2 * n + 9, " ");
        refresh();
        wattron(thirdgwin, A_REVERSE);
        mvwprintw(thirdgwin, thirdgwinyMax / 2 - 1, thirdgwinxMax / 2 - 6, "RIGHT PLAYER: ");
        mvwprintw(thirdgwin, thirdgwinyMax / 2 - 1, thirdgwinxMax / 2 + 9, to_string(sumRmark).c_str());
        wattron(thirdgwin, A_REVERSE);
        wattron(Lwin, A_REVERSE);
        mvwprintw(Lwin, thirdgwinyMax / 2 - 1, thirdgwinxMax / 2 - 6, "LEFT PLAYER: ");
        mvwprintw(Lwin, thirdgwinyMax / 2 - 1, thirdgwinxMax / 2 + 8, to_string(sumLmark).c_str());
        wattroff(Lwin, A_REVERSE);
        wrefresh(thirdgwin);
        wrefresh(Lwin);
        sleep(5);
        wclear(thirdgwin);
        wclear(Lwin);
        wrefresh(thirdgwin);
        wrefresh(Lwin);
        clear();
        refresh();
    }
    endwin();
    return 0;
}

int main(int argc, char *argv[])
{ //read in the total scores from other PrinParty games
    string score1 = argv[1], score2 = argv[2];
    maze({stoi(score1), stoi(score2)});
    return 0;
}