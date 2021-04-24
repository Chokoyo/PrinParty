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
using namespace std;

int random(int x)
{
    return (rand() % x);
}

void clearBox(WINDOW *dwin)
{
    wclear(dwin);
    box(dwin, 0, 0);
    refresh();
    wrefresh(dwin);
}

void generateBoard(int b[16][12], int round)
{
    int count = 0;
    vector<int> colorSet{0, 1, 2, 3};
    vector<vector<int>> coordinateSet;
    vector<vector<int>> blockNumSet{{20, 38, 42, 40}, {20, 30, 42, 48}, {20, 30, 40, 50}};

    for (int i = 1; i < 15; i++)
    {
        for (int j = 1; j < 11; j++)
        {
            b[i][j] = colorSet[random(4)];
        }
    }
    // // generate coordinateSet
    // for (int i = 0; i < 140; i++)
    // {
    //     for (int j = 1; j < 15; j++)
    //     {
    //         for (int k = 1; k < 11; k++)
    //         {
    //             coordinateSet.push_back({j, k});
    //         }
    //     }
    // }

    // // shuffle all the arrays to create random game sets
    // for (int i = 0; i < 3; i++)
    //     random_shuffle(blockNumSet[i].begin(), blockNumSet[i].end());
    // random_shuffle(coordinateSet.begin(), coordinateSet.end());
    // random_shuffle(colorSet.begin(), colorSet.end());

    // set the border to 1
    for (int i = 0; i < 16; i++)
    {
        b[i][0] = -1;
        b[i][11] = -1;
    }
    for (int j = 0; j < 12; j++)
    {
        b[0][j] = -1;
        b[15][j] = -1;
    }

    // // fill color 1,2,3
    // for (int i = 0; i < 3; i++)
    // {
    //     for (int j = 0; j < blockNumSet[round - 1][i]; j++)
    //     {
    //         b[coordinateSet[count][0]][coordinateSet[count][1]] = colorSet[i];
    //         count++;
    //     }
    // }
}

void printBoard(WINDOW *dwin, int b[16][12])
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            switch (b[i][j])
            {
            case -1:
                // mvwprintw(dwin, 2 + i, 2 + 2 * j, "█");
                // mvwprintw(dwin, 2 + i, 3 + 2 * j, "█");
                break;

            default:
                wattron(dwin, COLOR_PAIR(b[i][j] + 1));
                mvwprintw(dwin, 2 + i, 2 + 2 * j, "█");
                mvwprintw(dwin, 2 + i, 3 + 2 * j, "█");
                wattroff(dwin, COLOR_PAIR(b[i][j] + 1));
                break;
            }
        }
    }

    // print the seperator
    for (int i = 1; i < 19; i++)
    {
        mvwaddstr(dwin, i, 27, "│");
    }
    wrefresh(dwin);
}

void countDown(WINDOW *dwin, int time, int y, int x)
{
    // Count down 5 seconds
    for (int i = time; i > 0; i--)
    {
        mvwprintw(dwin, y, x, to_string(i).c_str());
        wrefresh(dwin);
        usleep(1000000);
    }
    mvwprintw(dwin, y, x - 3, "Start!");
    wrefresh(dwin);
    usleep(1000000);
    mvwprintw(dwin, y, x - 3, "      ");
    wrefresh(dwin);
}

void printChoices(WINDOW *dwin)
{
    // print the choice
    mvwprintw(dwin, 2, 29, "Choose the color with");
    mvwprintw(dwin, 3, 29, "maxium total area!");
    for (int i = 1; i <= 4; i++)
    {
        wattron(dwin, COLOR_PAIR(i));
        mvwprintw(dwin, 3 + 2 * i, 42, "█");
        mvwprintw(dwin, 3 + 2 * i, 43, "█");
        wattroff(dwin, COLOR_PAIR(i));
    }
    wrefresh(dwin);
    refresh();
}

int pSelect1(WINDOW *dwin, int choiceNum, int sep, int y, int x, int pNum, vector<string> &t)
{
    int choice = 0, input;
    auto start = chrono::steady_clock::now();
    keypad(dwin, true);
    wattron(dwin, 5);
    mvwprintw(dwin, y, x, ("p" + to_string(pNum) + " 🡺").c_str());
    while (1)
    {
        input = wgetch(dwin);
        if (input == 10) // 10 is the enter key
        {
            auto now = chrono::steady_clock::now();
            auto tt = chrono::duration_cast<chrono::milliseconds>(now - start);
            t[0] = to_string(tt.count());
            break;
        }
        mvwaddstr(dwin, y + 2 * choice, x, "     ");
        switch (input)
        {
        case KEY_UP:
            choice--;
            if (choice < 0)
                choice = 0;
            break;

        case KEY_DOWN:
            choice++;
            if (choice >= choiceNum)
                choice = choiceNum - 1;
            break;

        default:
            break;
        }
        mvwaddstr(dwin, y + 2 * choice, x, ("p" + to_string(pNum) + " 🡺").c_str());
        refresh();
    }
    wattroff(dwin, 5);
    return choice;
}

vector<int> pSelect2(WINDOW *dwin, int choiceNum, int sep, int y, int x, int pNum, vector<string> &t)
{
    vector<int> choice(2, 0);
    vector<bool> chosen(2, 0);
    int input;
    auto start = chrono::steady_clock::now();
    keypad(dwin, true);
    wattron(dwin, 5);
    mvwprintw(dwin, y, x, "p1 🡺");
    mvwprintw(dwin, y, x + 11, "🡸  p2");
    while (1)
    {
        input = wgetch(dwin);
        if (input == 'e')
        {
            auto now1 = chrono::steady_clock::now();
            auto tt1 = chrono::duration_cast<chrono::milliseconds>(now1 - start);
            t[0] = to_string(tt1.count());
            chosen[0] = 1;
            if (chosen[0] == 1 && chosen[1] == 1)
                break;
        }
        if (input == 10) // 10 is the enter key
        {
            auto now2 = chrono::steady_clock::now();
            auto tt2 = chrono::duration_cast<chrono::milliseconds>(now2 - start);
            t[1] = to_string(tt2.count());
            chosen[1] = 1;
            if (chosen[0] == 1 && chosen[1] == 1)
                break;
        }

        mvwaddstr(dwin, y + 2 * choice[0], x, "     ");
        mvwaddstr(dwin, y + 2 * choice[1], x + 11, "     ");
        switch (input)
        {
        case 'w':
            if (chosen[0] == 0)
                choice[0]--;
            if (choice[0] < 0)
                choice[0] = 0;
            break;

        case 's':
            if (chosen[0] == 0)
                choice[0]++;
            if (choice[0] >= choiceNum)
                choice[0] = choiceNum - 1;
            break;
        case KEY_UP:
            if (chosen[1] == 0)
                choice[1]--;
            if (choice[1] < 0)
                choice[1] = 0;
            break;

        case KEY_DOWN:
            if (chosen[1] == 0)
                choice[1]++;
            if (choice[1] >= choiceNum)
                choice[1] = choiceNum - 1;
            break;

        default:
            break;
        }
        mvwaddstr(dwin, y + 2 * choice[0], x, "p1 🡺");
        mvwaddstr(dwin, y + 2 * choice[1], x + 11, "🡸  p2");
        refresh();
    }
    wattroff(dwin, 5);
    return choice;
}

void erase(WINDOW *dwin, int y1, int x1, int y2, int x2)
{
    for (int i = y1; i <= y2; i++)
    {
        for (int j = x1; j <= x2; j++)
        {
            mvwaddch(dwin, i, j, ' ');
        }
    }
    wrefresh(dwin);
    refresh();
}

vector<int> assignScore(WINDOW *dwin, int b[16][12], vector<int> choices, int playerNum, vector<string> t)
{
    vector<int> counts(4, 0), scores(2, 0);
    erase(dwin, 1, 29, 3, 58);
    erase(dwin, 5, 35, 13, 50);

    // print players' choice
    mvwprintw(dwin, 1, 29, "Time");
    for (int i = 28; i < 59; i++)
    {
        mvwaddstr(dwin, 3, i, "─");
    }
    for (int i = 0; i < playerNum; i++)
    {
        mvwprintw(dwin, 5 + 3 * choices[i], 29, ("p" + to_string(i + 1) + "🡺").c_str());
        mvwprintw(dwin, 2, 31 + 12 * i, ("p" + to_string(i + 1) + ": " + t[i] + "ms").c_str());
    }
    if (choices[0] == choices[1] && playerNum == 2)
    {
        mvwprintw(dwin, 5 + 3 * choices[0], 29, "p1");
        mvwprintw(dwin, 6 + 3 * choices[0], 29, "p2");
    }

    // print the color blocks
    for (int i = 1; i <= 4; i++)
    {
        wattron(dwin, COLOR_PAIR(i));
        mvwprintw(dwin, 2 + 3 * i, 37, "█");
        mvwprintw(dwin, 2 + 3 * i, 38, "█");
        wattroff(dwin, COLOR_PAIR(i));
        mvwprintw(dwin, 2 + 3 * i, 34, to_string(counts[i - 1]).c_str());
    }

    // count the number of each color block
    for (int i = 1; i < 15; i++)
    {
        for (int j = 1; j < 11; j++)
        {
            counts[b[i][j]]++;
            mvwaddstr(dwin, i + 2, 2 + 2 * j, "  ");
            mvwprintw(dwin, 5 + 3 * b[i][j], 34, to_string(counts[b[i][j]]).c_str());
            mvwaddstr(dwin, 5 + 3 * b[i][j], 40 + counts[b[i][j]] / 3, "█");
            wrefresh(dwin);
            usleep(100000);
        }
    }

    // assign the score
    for (int i = 0; i < 4; i++)
    {
        int max = 0, maxIndex;
        for (int j = 0; j < 4; j++)
        {
            if (counts[j] > max)
            {
                max = counts[j];
                maxIndex = j;
            }
        }

        for (int k = 0; k < 2; k++)
        {
            if (choices[k] == maxIndex)
                scores[k] = 6 - 2 * i;
        }
        for (int m = 0; m < counts.size(); m++)
        {
            if (counts[m] == max)
                counts[m] = 0;
        }
    }

    wrefresh(dwin);
    refresh();
    return scores;
}

void printScores(WINDOW *dwin, vector<int> scores, int playerNum)
{
    for (int i = 28; i < 59; i++)
    {
        mvwaddstr(dwin, 16, i, "─");
    }
    mvwaddstr(dwin, 17, 29, "Score");
    for (int i = 0; i < playerNum; i++)
    {
        mvwaddstr(dwin, 18, 31 + 12 * i, ("p" + to_string(i + 1) + ": " + to_string(scores[i])).c_str());
    }
}

int area(int round, vector<int> score, int numOfPlayer)
{
    setlocale(LC_ALL, "");
    initscr();
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);
    init_pair(5, COLOR_WHITE, COLOR_BLACK);
    noecho();
    raw();
    curs_set(0);
    srand(time(NULL));

    int board[16][12] = {};
    vector<int> choices(2, 0), scores(2, 0), colorCount(4, 0);
    vector<string> time(2, "");
    WINDOW *win = newwin(20, 60, 0, 0), *selecWin = derwin(win, 8, 22, 4, 29);

    box(win, 0, 0);
    mvwprintw(win, 0, 3, "[GAME: Area]");
    refresh();

    // Instructions

    // the game will have 3 rounds
    for (int i = 1; i <= 3; i++)
    {
        mvwprintw(win, 0, 3, "[GAME: Area]");
        mvwprintw(win, 19, 8, ("[round " + to_string(i) + "/3]").c_str());
        generateBoard(board, i);
        printBoard(win, board);
        countDown(win, 3, 9, 43);
        printChoices(win);
        // Check the number of player
        if (numOfPlayer == 1)
        {
            printScores(win, scores, numOfPlayer);
            choices[0] = pSelect1(selecWin, 4, 2, 1, 6, 1, time);
            score[0] += assignScore(win, board, choices, 1, time)[0];
        }
        else
        {
            printScores(win, scores, numOfPlayer);
            choices = pSelect2(selecWin, 4, 2, 1, 6, 2, time);
            scores = assignScore(win, board, choices, 2, time);
            score[0] += scores[0];
            score[1] += scores[1];
        }
        printScores(win, score, numOfPlayer);
        usleep(1000000);
        mvwprintw(win, 9, 7, "Press any key");
        mvwprintw(win, 10, 8, "to continue");
        wrefresh(win);
        // mvwprintw(win, 18, 35, to_string(choices[0]).c_str());
        wgetch(win);
        // clear the window
        clearBox(win);
    }
    endwin();
    return 0;
}

int main()
{
    // call for 1/2 player
    area(0, {0, 0}, 2);

    // auto start = chrono::steady_clock::now();
    // while (1)
    // {
    //     auto now = chrono::steady_clock::now();
    //     auto tt = chrono::duration_cast<chrono::seconds>(now - start);
    //     string a = to_string(tt.count());
    //     mvprintw(0, 0, "time=");
    //     mvprintw(0, 5, a.c_str());
    //     refresh();
    // }

    // double i = 0;
    // string a;
    // while (1)
    // {
    //     a = to_string(i);
    //     mvprintw(0, 0, "time=");
    //     mvprintw(0, 5, a.c_str());
    //     refresh();
    //     i = i + 0.1;
    //     usleep(100000);
    // }

    return 0;
}