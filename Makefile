FLAGS = -I ./include -I ./include/ncursestw -L ./lib 

candy.o: candy.cpp playerforthirdgame.h
		g++ $(FLAGS) -c candy.cpp -lncursestw -ldl -pthread

candy: candy.o
		g++ $(FLAGS) candy.o -o candy -lncursestw -ldl -pthread

maze.o: maze.cpp player4game.h
		g++ $(FLAGS) -c maze.cpp -lncursestw -ldl -pthread

maze: maze.o
		g++ $(FLAGS) maze.o -o maze -lncursestw -ldl -pthread

area.o: area.cpp
		g++ $(FLAGS) -c area.cpp -lncursestw -ldl -pthread

area: area.o
		g++ $(FLAGS) area.o -o area -lncursestw -ldl -pthread

pong.o: pong.cpp
		g++ $(FLAGS) -c pong.cpp -lncursestw -ldl -pthread

pong: pong.o
		g++ $(FLAGS) pong.o -o pong -lncursestw -ldl -pthread

main.o: main.cpp
		g++ $(FLAGS) -c main.cpp -lncursestw -ldl -pthread

main: main.o
		g++ $(FLAGS) main.o -o main -lncursestw -ldl -pthread

clean:
	rm -f main main.o pong.o pong area area.o maze.o maze candy.o candy

all:
	make main area pong candy maze
.PHONY: clean all