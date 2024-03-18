OBJS = main.o board.o 
FLAGS = -O -Wall -Werror -Wshadow



move.o : move.cpp move.h
	c++ -c move.cpp $(FLAGS)

piece.o : piece.h piece.cpp
	c++ -c piece.cpp $(FLAGS)

board.o : board.cpp piece.cpp piece.h
	c++ -c board.cpp $(FLAGS)
	
main.o : main.cpp board.h
	c++ -c main.cpp $(FLAGS)
	 
main : $(OBJS)
	c++ -o main $(OBJS) $(FLAGS)
	
clear: 
	rm -f $(OBJS) main
	
build:
	make clear main
	
	
