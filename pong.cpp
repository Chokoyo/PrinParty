// Author: Gu Zhuangcheng
// U. No.: 3035827110
// ENGG1340 Group Project
// File Name: pong.cpp
// Description: The is a ping pong game implemented by multi-thread programming

#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <vector>
#include <algorithm>
#include <chrono>
#include <unistd.h>
#include <thread>
using namespace std;

// global variables
int board[15][60] = {}, scores[] = {0, 0};
int xDirect[] = {-2, 2}, yDirect[] = {-1, 1};
bool tThreadEnd = 0, ballThreadEnd = 0;

// function prototypes
int random(int x);
void printScore(WINDOW *dwin, int playerNum);
void printSeperator(WINDOW *dwin, int playerNum);
void printBuffle(WINDOW *dwin, int y, int x, bool clear);

// structure for the ball
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

// generate a random number range from 0 to x-1
int random(int x)
{
    return (rand() % x);
}

// print the score for the player(s)
void printScore(WINDOW *dwin, int playerNum)
{
    mvwprintw(dwin, 15, 31, "Score");
    for (int i = 0; i < playerNum; i++)
    {
        mvwprintw(dwin, 16, 38 + i * 10, "        ");
        mvwprintw(dwin, 16, 34 + i * 10, ("p" + to_string(i + 1) + ": ").c_str());
        mvwprintw(dwin, 16, 38 + i * 10, to_string(scores[i]).c_str());
    }
    wrefresh(dwin);
}

// moveBall thread
void moveBall(WINDOW *dwin, int playerNum)
{
    int detect = 0;
    while (1)
    {
        // control to stop and run of the thread
        if (tThreadEnd == 1)
        {
            ballThreadEnd == 1;
            break;
        }
        // initialize th ball position
        myBall.position = {7, 29};
        myBall.direction = {yDirect[random(2)], xDirect[random(2)]};
        this_thread::sleep_for(chrono::milliseconds(997));
        while (1)
        {
            detect = board[myBall.nextPos()[0]][myBall.nextPos()[1]];
            // detect whether ball in not catch
            if (myBall.position[1] <= 3)
            {
                mvwaddstr(dwin, myBall.position[0], myBall.position[1], " ");
                if (playerNum == 1 && scores[0] >= 0)
                    scores[0]--;
                else
                    scores[1]++;
                printScore(dwin, playerNum);
                break;
            }
            else if (myBall.position[1] >= 56)
            {
                mvwaddstr(dwin, myBall.position[0], myBall.position[1], " ");
                if (playerNum == 1 && scores[0] >= 0)
                    scores[0]--;
                else
                    scores[0]++;
                printScore(dwin, playerNum);
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

            // move the ball to the next position
            mvwaddstr(dwin, myBall.position[0], myBall.position[1], " ");
            myBall.move();
            mvwaddstr(dwin, myBall.position[0], myBall.position[1], "●");
            wrefresh(dwin);
            this_thread::sleep_for(chrono::milliseconds(199));
        }
    }
}

// timer thread
void timer(WINDOW *dwin)
{
    mvwprintw(dwin, 15, 2, "TIME");
    // this thread will run independently
    for (int i = 30; i >= 0; i--)
    {
        mvwprintw(dwin, 16, 5, "          ");
        mvwprintw(dwin, 16, 5, (to_string(i) + "s").c_str());
        wrefresh(dwin);
        // delay the thread for 1 sec in each iteration
        this_thread::sleep_for(chrono::milliseconds(997));
    }
    tThreadEnd = 1;
}

// print the seperator
void printSeperator(WINDOW *dwin, int playerNum)
{
    for (int i = 1; i < 59; i++)
    {
        mvwprintw(dwin, 14, i, "─");
    }
    for (int j = 15; j < 19; j++)
    {
        mvwprintw(dwin, j, 29, "│");
    }
    wrefresh(dwin);
}

// print or clear the player's buffle
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

// the pong game function
void pong(int round, vector<int> score, int numOfPlayer)
{
    // initialize ncurses
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    raw();
    curs_set(0);
    // initialize the random seed
    srand(time(NULL));

    // initialize variable
    WINDOW *win = newwin(20, 60, 0, 0);
    keypad(win, true);
    if (numOfPlayer == 1)
        scores[0] += 10;
    int input, p1 = 5, p2 = 5;
    vector<thread> timeThread(3), ballThread(3);

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

    // print the basic information
    box(win, 0, 0);
    printSeperator(win, numOfPlayer);
    mvwprintw(win, 0, 3, "[GAME: Pong]");
    mvwprintw(win, 19, 8, "[ROUND 1/2]");
    mvwprintw(win, 15, 2, "Time");
    printScore(win, numOfPlayer);
    mvwprintw(win, 7, 19, "Press Any Key to Start");
    wrefresh(win);
    wgetch(win);
    mvwprintw(win, 7, 22, "                      ");

    for (int i = 1; i <= 2; i++) // totally 2 rounds
    {
        tThreadEnd = 0;
        ballThreadEnd = 0;
        //clear the screen
        wclear(win);
        box(win, 0, 0);
        printSeperator(win, numOfPlayer);
        mvwprintw(win, 0, 3, "[GAME: Pong]");
        mvwprintw(win, 19, 8, ("[round " + to_string(i) + "/2]").c_str());
        printScore(win, numOfPlayer);
        printBuffle(win, p1, 2, 0);
        printBuffle(win, p2, 56, 0);
        wrefresh(win);
        timeThread[i - 1] = thread(timer, win);
        ballThread[i - 1] = thread(moveBall, win, numOfPlayer);

        // start the thread
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
            if (numOfPlayer == 1)
            {
                switch (input)
                {
                case KEY_UP:
                    p1--;
                    if (p1 < 1)
                        p1 = 1;
                    p2--;
                    if (p2 < 1)
                        p2 = 1;
                    break;
                case KEY_DOWN:
                    p1++;
                    if (p1 >= 9)
                        p1 = 9;
                    p2++;
                    if (p2 >= 9)
                        p2 = 9;
                    break;
                default:
                    break;
                }
            }
            else
            {
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
            }
            printBuffle(win, p1, 2, 0);
            printBuffle(win, p2, 56, 0);
            wrefresh(win);
        }
    }
    wgetch(win);
    endwin();
}

int main(int argc, char *argv[])
{
    string score1 = argv[1], score2 = argv[2], pNum = argv[3];
    pong(0, {stoi(score1), stoi(score2)}, stoi(pNum)); /*pong(round,score[],playerNum})*/
    return 0;
}