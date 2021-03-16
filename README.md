# PrinPart
A ENGG1340-Group-Project developed by Gu Zhuangcheng & Wangsinan

## Description of our game

PrinParty will include four mini-games. Two players will play the four games in random order. After playing every game, the player will get a score. When they finish all games, their scores will add up, and the higher scorer wins the game.

## Rules of our game

### Game 1: 

There will be four areas of different colors for players to choose from, and they need to select the biggest one. The player who first chooses the correct color area will get more scores. If they don’t choose the biggest color area, the bigger one will get more scores.

### Game 2: 

In this game, two players need to pull up a weight in a specific time. They need to hit the keyboard in a certain way to pull up the weight. Finally, the person whose weight is higher when time is up will get more scores.

### Game 3: 

On the screen, there will emerge different balloons, and they have different marks. Two players need to move their cursors onto the balloon and click it to get the mark. In the end of the game, the player whose mark is higher will get higher scores.

### Game 4: 

Two players will play on one map. They will start from the same place, and they need to get to a destination. The player who first reaches the destination will get more scores, and the game will end immediately once a person has reached the destination. On the map, there will randomly emerge stars. If the first player had passed the stars, he would get more scores.



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
