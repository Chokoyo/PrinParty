#include <ncurses.h>
#include <ctime>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <unistd.h>
#include <thread>
#include <iostream>
using namespace std;

int board[15][60] = {}, scores[] = {0, 0};
int xDirect[] = {-2, 2}, yDirect[] = {-1, 1};
bool tThreadEnd = 0, ballThreadEnd = 0;

int random(int x);

struct ball
{
    string symbol = "●";
    vector<int> position = {7, 29}; // default at the middle
    vector<int> direction = {yDirect[random(2)], xDirect[random(2)]};
    vector<int> nextPos()
    {
        vector<int> res(2, 0);
        res[0] = position[0] + direction[0];
        res[1] = position[1] + direction[1];
        return res;
    };
    void move()
    {
        position[0] += direction[0];
        position[1] += direction[1];
    };
} myBall;

int random(int x)
{
    return (rand() % x);
}

void printScore(WINDOW *dwin)
{
    mvwprintw(dwin, 15, 31, "SCORE");
    for (int i = 0; i < 2; i++)
    {
        mvwprintw(dwin, 16, 34 + i * 10, ("p" + to_string(i + 1) + ": ").c_str());
        mvwprintw(dwin, 16, 38 + i * 10, to_string(scores[i]).c_str());
    }
    wrefresh(dwin);
}

void moveBall(WINDOW *dwin)
{
    int detect = 0;
    while (1)
    {
        if (tThreadEnd == 1)
        {
            ballThreadEnd == 1;
            break;
        }
        myBall.position = {7, 29};
        myBall.direction = {yDirect[random(2)], xDirect[random(2)]};
        this_thread::sleep_for(chrono::milliseconds(997));
        while (1)
        {
            detect = board[myBall.nextPos()[0]][myBall.nextPos()[1]];
            // mvwinstr(win, myBall.nextPos()[0], myBall.nextPos()[1], c);
            if (myBall.position[1] <= 3)
            {
                mvwaddstr(dwin, myBall.position[0], myBall.position[1], " ");
                scores[1]++;
                printScore(dwin);
                break;
            }
            else if (myBall.position[1] >= 56)
            {
                mvwaddstr(dwin, myBall.position[0], myBall.position[1], " ");
                scores[0]++;
                printScore(dwin);
                break;
            }
            if (detect == 1)
            {
                myBall.direction[1] = 0 - myBall.direction[1];
            }
            else if (detect == -1)
            {
                myBall.direction[0] = 0 - myBall.direction[0];
            }
            mvwaddstr(dwin, myBall.position[0], myBall.position[1], " ");
            myBall.move();
            mvwaddstr(dwin, myBall.position[0], myBall.position[1], "●");
            wrefresh(dwin);
            this_thread::sleep_for(chrono::milliseconds(199));
        }
    }
}

void timer(WINDOW *dwin)
{
    mvwprintw(dwin, 15, 2, "TIME");
    for (int i = 50; i >= 0; i--)
    {
        mvwprintw(dwin, 16, 5, "          ");
        mvwprintw(dwin, 16, 5, (to_string(i) + "s").c_str());
        wrefresh(dwin);
        this_thread::sleep_for(chrono::milliseconds(997));
    }
    tThreadEnd = 1;
}

void printSeperator(WINDOW *dwin, int playerNum)
{
    for (int i = 1; i < 59; i++)
    {
        mvwprintw(dwin, 14, i, "─");
    }
    if (playerNum == 2)
    {
        for (int j = 15; j < 19; j++)
        {
            mvwprintw(dwin, j, 29, "│");
        }
    }
    wrefresh(dwin);
}

void printBuffle(WINDOW *dwin, int y, int x, bool clear)
{
    for (int i = 0; i < 5; i++)
    {
        if (clear)
        {
            mvwprintw(dwin, y + i, x, "  ");
            board[y + i][x] = 0;
            board[y + i][x + 1] = 0;
        }
        else
        {
            mvwprintw(dwin, y + i, x, "██");
            board[y + i][x] = 1;
            board[y + i][x + 1] = 1;
        }
    }
}

void pong(int round, vector<int> score, int numOfPlayer)
{
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    raw();
    curs_set(0);
    srand(time(NULL));

    WINDOW *win = newwin(20, 60, 0, 0);
    keypad(win, true);

    int input, p1 = 5, p2 = 5;
    vector<thread> timeThread(3), ballThread(3);
    // for (int i = 0; i < 3; i++)
    // {
    //     timeThread.push_back(thread(timer, win));
    //     ballThread.push_back(thread(moveBall, win));
    // }

    // fill the board
    for (int i = 0; i < 60; i++)
    {
        board[0][i] = -1;
        board[14][i] = -1;
    }
    for (int i = 0; i < 15; i++)
    {
        board[i][0] = -1;
        board[i][59] = -1;
    }

    for (int i = 1; i <= 1; i++) // totally 3 rounds
    {
        tThreadEnd = 0;
        ballThreadEnd = 0;
        //clear the screen
        wclear(win);
        box(win, 0, 0);
        printSeperator(win, numOfPlayer);
        mvwprintw(win, 0, 3, "[GAME: Pong]");
        mvwprintw(win, 19, 8, ("[round " + to_string(i) + "/3]").c_str());
        printScore(win);
        wrefresh(win);
        timeThread[i - 1] = thread(timer, win);
        ballThread[i - 1] = thread(moveBall, win);
        timeThread[i - 1].detach();
        ballThread[i - 1].detach();
        while (1)
        {
            if (tThreadEnd == 1)
                break;
            // user movement
            input = wgetch(win);
            printBuffle(win, p1, 2, 1);
            printBuffle(win, p2, 56, 1);
            switch (input)
            {
            case 'w':
                p1--;
                if (p1 < 1)
                    p1 = 1;
                break;
            case 's':
                p1++;
                if (p1 >= 9)
                    p1 = 9;
                break;
            case KEY_UP:
                p2--;
                if (p2 < 1)
                    p2 = 1;
                break;
            case KEY_DOWN:
                p2++;
                if (p2 >= 9)
                    p2 = 9;
                break;
            default:
                break;
            }
            printBuffle(win, p1, 2, 0);
            printBuffle(win, p2, 56, 0);
            wrefresh(win);
        }
    }
    wgetch(win);
    endwin();
}

int main()
{
    // cout << "here" << endl;

    try
    {
        pong(0, {0, 0}, 2);
    }
    catch (...)
    {
    }
}