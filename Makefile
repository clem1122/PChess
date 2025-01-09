OBJS = main.o game.o move.o piece.o board.o
FLAGS = -O -Wall -Werror -Wshadow
CLIENT = client.o
SERVER = server.o

all: client server main

server.o : server.cpp board.h
	c++ -c server.cpp -o server.o $(FLAGS)

client.o : client.cpp
	c++ -c client.cpp -o client.o $(FLAGS)

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
	
server: $(SERVER) game.o board.o piece.o move.o
	c++ -o server $(SERVER) game.o board.o move.o piece.o -lpthread
	
client: $(CLIENT)
	c++ -o client $(CLIENT) -lpthread
	

	
clear: 
	rm -f $(OBJS) $(CLIENT) $(SERVER) main server client
	
build:
	make clear main
	
	
