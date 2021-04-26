# PrinParty
A ENGG1340-Group-Project developed by Gu Zhuangcheng(3035827110) & Wang Sinan(3035770599)

- [PrinParty](#prinparty)
  * [Description of our game](#description-of-our-game)
  * [Rules of our game](#rules-of-our-game)
    + [Game 1: Largest Area](#game-1--largest-area)
    + [Game 2: Pong](#game-2--pong)
    + [Game 3: Collect Candy](#game-3--collect-candy)
    + [Game 4: Maze Advanture](#game-4--maze-advanture)
  * [Game Features](#game-features)
  * [Coding Requirements](#coding-requirements)
  * [Game Control](#game-control)
  * [Compile Insturctions](#compile-insturctions)

## Description of our game

PrinParty will include four mini-games. Two players will play the four games in random order. After playing every game, the player will get a score. When they finish ever single game, a total mark will be should. The player can also choose to play any single game from the menu page.

![main](https://github.com/Chokoyo/PrinParty/blob/main/pics/main_menu.gif)

## Rules of our game

### Game 1: Largest Area

There will be four areas of different colors for players to choose from, and they need to select the one with largest total area. The player who first chooses the correct color area will get more scores. If they don’t choose the biggest color area, the bigger one will get more scores.

![area](https://github.com/Chokoyo/PrinParty/blob/main/pics/game_area.gif)

### Game 2: Pong

In this game, two players need to move their buffles to catch with the moving ping pong ball. If the player failed to do so, his opponent will git one score. There are in total two rounds in this game, and the moving speed of the ball will be increased in the second round.

![pong](https://github.com/Chokoyo/PrinParty/blob/main/pics/game_pong.gif)

### Game 3: Collect Candy

On the screen, there will emerge different candies, and they have different marks (Yellow > Blue > Red > Green). Two players need to move their cursors onto the candy to get the mark. In the end of the game, the player whose mark is higher wins the game.

![candy](https://github.com/Chokoyo/PrinParty/blob/main/pics/game_candy.gif)

### Game 4: Maze Advanture

Two players will play on one map. They will start from the same place, and they need to get to a destination (at the right bottom corner). The player who first reaches the destination will get more scores, and the game will end immediately once a person has reached the destination. 

![maze](https://github.com/Chokoyo/PrinParty/blob/main/pics/game_maze.gif)

##  Game Features
1. Using ncurses to implement frame refresh.
2. Using the getch() function that can let the program to read directly from the keyboard input.
3. Allow user to pause the game anytime by saving the game using File I/O.
4. Using random seed to generate different games sets.
5. Using the #include <thread> to support multi-thread programming (in pong.cpp)
6. Using ncurses library to support colorful display.
7. Using dynamic data management to reduce resource usage.
8. Using the Object-Oriented Program to implement.


## Coding Requirements

1. Generation of random game sets or events

    The main.cpp will randomly decide the sequence of 4 mini-games at the beginning of the game.
    
    In each mini-game, the players will encounter randomly generated game sets. For instance, in the game of "Largest Area", the players are expected to choose the largest color blocks in which their area is randomly generated. In the game of "Maze Adventure", the routes, obstacles will be randomly generated.

2. Data structures for storing game status

    In this party game, there will be a scoreboard used to records the accumulative points that the players earned after each round of the game. The scoreboard will be stored in a 2-D array where its length is equal to the number of players(2-4) decided at the start of the game.

    In some of the mini-games, the players will use a simulated cursor(controlled by keyboard) for making choices or movements. We will use the struct statement to create user-defined data types which contain the x-position and y-position in integer.

    This game also allowed the players to store their game progress at the end of each mini-game in "Party Mode". The game status will also be stored in the savings/ directory.
4. Dynamic memory management

    In this project, we will use STL vectors as well as new and delete statements when initialing some of the variables so that the system will automatically deallocate the memory when it is no longer needed.

5. File input/output (e.g., for loading/saving game status)

    There is an in-built game saving function in them which allows the player the pause and save the game. The game status will be store in a .save in savings/ directory which enables the play to continue playing the game next time. 

6. Program codes in multiple files

    Each mini-game will be implemented in separated .cpp files. And we will also use the Object-Oriented Program to implement, and each object will be coded in different files.
    
## Game Control
In the main menu page, user are allowed to use <kbd>↑</kbd><kbd>↓</kbd> for moving the selector up and down, and use <kbd>Enter</kbd> key to make choices.

The "Largest Area" game support 1 player and 2 player. Please use either <kbd>↑</kbd><kbd>↓</kbd> or <kbd>w</kbd><kbd>s</kbd> for move the selector and <kbd>Enter</kbd> or <kbd>e</kbd> key for making choices.

In "Pong" game, user need to use either <kbd>↑</kbd><kbd>↓</kbd> or <kbd>w</kbd><kbd>s</kbd> to move their buffles up and down.

In "Candy" and "Maze", user need to uses <kbd>↑</kbd><kbd>↓</kbd><kbd>←</kbd><kbd>→</kbd> or <kbd>w</kbd><kbd>s</kbd><kbd>a</kbd><kbd>d</kbd>.

## Compile Insturctions
1. In the working directories (Under PrinParty/), first use ```chmod 700 load_dependency.sh``` to allow the shell script to execute.

2. Then use ```./load_dependency.sh``` to load the ncurses library, note that this script will automatically open the main menu page for you.

3. If want to play the game when the dependecies are already loaded, please use ```./main``` to start the game.

**Notes**
1. If any conpiled binary files failed, the user can use ```make all``` command to recompile.
2. The user's terminal should be at least have a size of 20(height)*60(width) before starting the game. Resizing the window after the program started is not permitted.
3. Please **do not use** command prompt (use powershell instead) and any program other than "bash" to play the game.
4. If encounter any problem during the marking, please contact zcgu@connect.hku.hk or wsn1226@connect.hku.hk
