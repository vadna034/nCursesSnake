all: main

main: main.cpp src/board.hpp
	g++ main.cpp -lncurses -o main
