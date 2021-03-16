# PrinPart
A ENGG1340-Group-Project developed by Gu Zhuangcheng & Wangsinan

## Introduction


## Coding Requirements
1. Generation of random game sets or events
The main.cpp will randomly decides the sequence of 4 mini-games at the beginning of the game.
In each mini-game, the players will encounter randomly generated game sets. For instance, in the game of "Color blocks", the players are expected to choose the largest color blocks which their area is randomly generated. In the game of "Maze", the routes, obstacles, and extra bonus stars will be randomly generated.

2. Data structures for storing game status
In this party games, there will be a scoreboard used to records the accumulative points that the players earned after each round of game. The scoreboard will be stored in an 2-D array where its length is equal to the number of players(2-4) decided at the start of the game.

In some of the mini-games, the players will use a simulated cursor(controlled by keybords) for making choices or movements. We will use the struct statement to create user-defined data types which contains the x-position and y-position in integer.

This game also allowed to the players to store their game progress at any point of the game. The game status will also be defined using user-defined data type 

4. Dynamic memory management


5. File input/output (e.g., for loading/saving game status)
There is a  in-built game saving  function in the which allow the player the pause and save the game by pressing F2 key on the keyboards. The game status will be store in an .gamesaving file which enable the play to continue playing the game next time. This saving will also record the random seed of the game, so that the players are able to replay.

6. Program codes in multiple files
Each mini-game will be implemented in seperated .cpp files. And we will also use the Object-Oriented Program to implement, and each objects will be coded in different files.
