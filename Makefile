OBJS = main.o game.o move.o piece.o board.o
FLAGS = -O -Wall -Werror -Wshadow



move.o : move.cpp move.h
	c++ -c move.cpp $(FLAGS)

piece.o : piece.cpp piece.h
	c++ -c piece.cpp $(FLAGS)

board.o : board.cpp board.h piece.cpp piece.h move.cpp move.h
	c++ -c board.cpp $(FLAGS)
	
game.o : game.cpp game.h board.cpp board.h
	c++ -c game.cpp $(FLAGS)
	
main.o : main.cpp game.cpp game.h
	c++ -c main.cpp $(FLAGS)
	 
main : $(OBJS)
	c++ -o main $(OBJS) $(FLAGS)
	
clear: 
	rm -f $(OBJS) main
	
build:
	make clear main
	
	
