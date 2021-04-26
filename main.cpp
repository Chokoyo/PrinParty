#include <ncurses.h>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <iostream>
#include <sys/time.h>
#include "cursor.h"
using namespace std;

void printwin(WINDOW *win);
void initNcurses();

int main()
{
    // initalize ncurses
    initNcurses();
    srand(time(NULL));
    if (!has_colors())
    {
        printw("This terminal doesn't support color display");
        getch();
        exit(1);
    }

    // vairable declearation
    int number = 0;
    ifstream fin;
    ifstream finfinal;
    string finalline;
    string line;
    string thefileName;
    vector<string> thesavings;
    string chosensaving;
    string threeinformation;
    vector<int> sequence;
    int specificse;
    int deletenumber;
    int stage = 0, input = 0, y = 0, x = 0, y_max, x_max;
    vector<int> gameSeq = {0, 1, 2, 3}, score = {0, 0};
    string menu[4][7] = {{"Party Mode (2 Player)",
                          "Single Game",
                          "Quick Start",
                          "Load Game",
                          "Back"},
                         {"Game 1: Largest Area (2 Player)",
                          "Game 2: Ping Pong (2 Player)",
                          "Game 3: Collect Candies (2 Player)",
                          "Game 4: Maze Advanture (2 Player)",
                          "Game 1: Largest Area (1 Player)",
                          "Game 2: Ping Pong (1 Player)",
                          "Back"},
                         {"./area 0 0 2",
                          "./pong 0 0 2",
                          "./candy 0 0",
                          "./maze 0 0",
                          "./area 0 0 1",
                          "./pong 0 0 2"},
                         {"./area",
                          "./pong",
                          "./candy",
                          "./maze",
                          "./area",
                          "./pong"}};
    string command, fileName;
    WINDOW *win = newwin(20, 60, 0, 0); /*newwin(height, width, y, x)*/
    getmaxyx(win, y_max, x_max);
    printwin(win);
    keypad(win, true);
    ofstream fout;
    time_t t = time(0);
    tm *now = localtime(&t);
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
            input = wgetch(win);
            if (input == 'p')
            {
                endwin();
                system("clear");
                exit(0);
            }
            stage++;
        case 1: // menu page
            curs_set(0);
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
            // summon random game sequence
            random_shuffle(gameSeq.begin(), gameSeq.end());
            for (int i = 0; i < 4; i++)
            {
                command = menu[3][gameSeq[i]] + " " + to_string(score[0]) +
                          " " + to_string(score[1]) + " 2";
                printwin(win);
                system("clear");
                system(command.c_str());
                system("clear");
                initNcurses();
                keypad(win, true);
                // Ask the User Whether to go to the next game
                mvwprintw(win, 1, 5, "Continue to the next game");
                mvwprintw(win, 2, 5, "Quit and Save");
                y = 1;
                mvwprintw(win, y, 2, "➤");
                while (1)
                {
                    input = wgetch(win);
                    mvwprintw(win, y, 2, "  ");
                    if (input == 10)
                        break;
                    else if (input == KEY_UP)
                        y = 1;
                    else if (input == KEY_DOWN)
                        y = 2;
                    mvwprintw(win, y, 2, "➤");
                }
                if (y == 1) // continue to the next game
                    continue;
                if (y == 2) // Save and quit the game
                {
                    t = time(0);
                    fileName = to_string(1900 + now->tm_year);
                    if (to_string(1 + now->tm_mon).length() == 1)
                    {
                        fileName += "0";
                    }
                    fileName += to_string(1 + now->tm_mon);
                    if (to_string(now->tm_mday).length() == 1)
                    {
                        fileName += "0";
                    }
                    fileName += to_string(now->tm_mday);
                    if (to_string(now->tm_hour).length() == 1)
                    {
                        fileName += "0";
                    }
                    fileName += to_string(now->tm_hour);
                    if (to_string(now->tm_min).length() == 1)
                    {
                        fileName += "0";
                    }
                    fileName += to_string(now->tm_min);
                    if (to_string(now->tm_sec).length() == 1)
                    {
                        fileName += "0";
                    }
                    fileName += to_string(now->tm_sec);
                    fout.open("savings/" + fileName + ".save");
                    if (fout.fail())
                    {
                        wclear(win);
                        mvwprintw(win, 1, 2, fileName.c_str());
                        wrefresh(win);
                        exit(1);
                    }
                    for (int i = 0; i < 4; i++)
                    {
                        fout << gameSeq[i] << " ";
                    }
                    fout << endl;
                    fout << i << endl;
                    fout.close();
                    endwin();
                    system("clear");
                    exit(0);
                }
            }
            break;
        case 3: // single game page
            printwin(win);
            for (int i = 0; i < 7; i++)
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
                    if (y > 7)
                        y = 7;
                    break;

                default:
                    break;
                }
                mvwprintw(win, y, 2, "➤");
                wrefresh(win);
            }
            if (stage == 12)
                stage = 1;
            continue;
        case 4: // quick start page
            printwin(win);
            system("clear");
            system(menu[2][rand() % 7].c_str());
            system("clear");
            initNcurses();
            keypad(win, true);
            stage = 3;
            continue;
        case 5: // load game page
            system("ls savings/ >sinto.txt");
            system("mv savings/sinto.txt sinto.txt");
            system("sort -r sinto.txt > finalsinto.txt");
            thefileName = "finalsinto.txt";
            fin.open(thefileName);
            if (fin.fail())
            {
                cout << "file open error" << endl;
                exit(0);
            }
            else
            {
                while (getline(fin, line))
                {
                    thesavings.push_back(line);
                }
            }
            fin.close();
            thesavings.push_back("back");
            printwin(win);
            for (int i = 0; i < 6; i++)
            {
                mvwprintw(win, i + 1, 5, thesavings[i].c_str());
            }
            y = 1;
            mvwprintw(win, y, 2, "➤");
            while (1)
            {
                input = wgetch(win);
                if (input == 10 && y == 6)
                {
                    stage = 1;
                    break;
                }

                if (input == 10) // 10 present the enter key
                {
                    chosensaving = thesavings[y - 1];
                    finfinal.open("savings/" + chosensaving);
                    if (finfinal.fail())
                    {
                        cout << "file open error" << endl;
                        exit(0);
                    }
                    else
                    {
                        while (getline(finfinal, finalline))
                        {
                            if (number == 0)
                            {
                                for (int i = 0; i < finalline.length(); i++)
                                {
                                    if (finalline[i] != ' ')
                                    {
                                        specificse = finalline[i] - '0';
                                        sequence.push_back(specificse);
                                    }
                                }
                            }
                            if (number == 1)
                            {
                                deletenumber = stoi(finalline);
                            }
                            number += 1;
                        }

                        for (int i = deletenumber + 1; i < sequence.size(); i++)
                        {
                            if (sequence[i] == 0)
                            {
                                system("clear");
                                system("./area 0 0 2");
                                system("clear");
                                initNcurses();
                                keypad(win, true);
                            }
                            else if (sequence[i] == 1)
                            {
                                system("clear");
                                system("./pong 0 0 2");
                                system("clear");
                                initNcurses();
                                keypad(win, true);
                            }
                            else if (sequence[i] == 2)
                            {
                                system("clear");
                                system("./candy 0 0 2");
                                system("clear");
                                initNcurses();
                                keypad(win, true);
                            }
                            else if (sequence[i] == 3)
                            {
                                system("clear");
                                system("./maze 0 0 2");
                                system("clear");
                                initNcurses();
                                keypad(win, true);
                            }
                        }
                    }
                    finfinal.close();
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
                    if (y > 6)
                        y = 6;
                    break;

                default:
                    break;
                }
                mvwprintw(win, y, 2, "➤");
                wrefresh(win);
            }
            if (y != 6)
            {
                break;
            }
            else
            {
                continue;
            }

        case 6: // Game 1:
            system("clear");
            system("./area 0 0 2");
            system("clear");
            initNcurses();
            keypad(win, true);
            stage = 3;
            continue;
        case 7: // Game 2:
            system("clear");
            system("./pong 0 0 2");
            system("clear");
            initNcurses();
            keypad(win, true);
            stage = 3;
            continue;
        case 8: // Game 3:
            system("clear");
            system("./candy 0 0");
            system("clear");
            initNcurses();
            keypad(win, true);
            stage = 3;
            continue;
        case 9: // Game 4:
            system("clear");
            system("./maze 0 0");
            system("clear");
            initNcurses();
            keypad(win, true);
            stage = 3;
            continue;
        case 10: // Game 5:
            system("clear");
            system("./area 0 0 1");
            system("clear");
            initNcurses();
            keypad(win, true);
            stage = 3;
            continue;
        case 11: // Game 6:
            system("clear");
            system("./pong 0 0 1");
            system("clear");
            initNcurses();
            keypad(win, true);
            stage = 3;
            continue;
        case 12: // test page
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

void initNcurses()
{
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    raw();
    curs_set(0);
}