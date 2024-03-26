#include <string.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#include "base.h"
#include "game.h"
#include "move.h"

struct client {
	int * fd;
	char * ip;
};

Game game = Game();

void send(int s, char msg[]) {
	ssize_t size;
	size_t len = strlen(msg); 
	size = write(s, &len, sizeof(len));
	if (size != sizeof(len));
	size = write(s, msg, 1 + strlen(msg));
}

char* receive(int s) {
	size_t len;
	ssize_t size;
	size = read(s, &len, sizeof(len));
	if (size != sizeof(len));
	char *buf = new char [len + 1];
	size = read(s, buf, 1 + len);
	return buf;

}

char* stringToChar(std::string s) {
	char* charArray = new char[s.length() + 1];
	strcpy(charArray, s.c_str());
	return charArray;

}

void * hconnect (void * t)
{
	
	
	client* d =  (client*)t;
	int client_fd = *(d->fd);
	char client_ip[INET_ADDRSTRLEN];
    sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    
	
	getpeername(client_fd, (sockaddr *)&addr, &addr_len);
    inet_ntop(AF_INET, &addr.sin_addr, client_ip, INET_ADDRSTRLEN);
	int f = *((int *)d->fd);
	std::cout << "connect" << std::endl;
	if (game.socketJ1 == 0) {
		std::cout << "first connexion " << "socket : " << f << std::endl;
		game.socketJ1 = f;	
		//game.nameJ1 = name;
		
		
	} else {
		game.socketJ2 = f;
		//game.nameJ2 = name;
		std::cout << "second connexion " <<  " socket : " << f << std::endl;
		send(game.socketJ1, stringToChar("1"));
		send(game.socketJ2, stringToChar("4"));
		if(game.socketJ2 == game.socketJ1) {std::cout << "ohoh" << std::endl;}
	}
	
	free(d);
	pthread_detach(pthread_self());
	return NULL;	
}

void* CommunicationRoutine(void* _) {
	char* msg;
	bool isJ1Turn = true;
	bool isMoveValid;
	Move move;
	int playerSocket;
	int waiterSocket;

	
	std::cout << "c'est parti..." << std::endl;
	
	while(true) {
		sleep(1);
		if(game.socketJ1 != 0 && game.socketJ2 != 0) {
			if(isJ1Turn) {
				playerSocket = game.socketJ1;
				waiterSocket = game.socketJ2;
			} else {
				playerSocket = game.socketJ2;
				waiterSocket = game.socketJ1;
			}
			
			do {
				msg = receive(playerSocket);
				move = game.board.create_move(msg);									
				isMoveValid = game.board.isLegal(move) && 
				(move.movingPiece.isWhite != (playerSocket == game.socketJ2)); // soit isWhite et J1 soit !isWhite et J2 
				if(not isMoveValid) {
					std::cout << "Unvalid piece movement : " << msg << std::endl;
					send(playerSocket, stringToChar("err0"));
				}
				
			} while(!isMoveValid);
			std::cout <<"Move : " << msg << std::endl;
			game.board.playMove(move);
			game.board.print();
			send(waiterSocket, msg);

			
			isJ1Turn = !isJ1Turn;
		}
		 
	}
	return nullptr;
	   
}

int main (int argc, char ** argv)

{
        const char * server = "0.0.0.0";
        struct sockaddr_in sin;
        int s, f, ret;
		pthread_t tid;
		int optval = 1;

        sin.sin_family = AF_INET;
        sin.sin_port = htons(DEFAULT_PORT);
        ret = inet_aton(server, &sin.sin_addr);
        if (ret == 0) {
		fprintf(stderr, "address %s invalid\n", server);
		return 0;
	}

        s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (s < 0) {
		fprintf(stderr, "cannot create socket\n");
		return 0;
	}

        ret = setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
        if (ret != 0) {
                fprintf(stderr, "setsockopt() failed\n");
                return 0;
        }

        ret = bind(s, (struct sockaddr *)&sin, sizeof(sin));
        if (ret != 0) {
		fprintf(stderr, "bind() failed\n");
		return 0;
	}

        ret = listen(s, 10);
        if (ret != 0) {
		fprintf(stderr, "listen() failed\n");
		return 0;
	}
	
	pthread_create(&tid, NULL, CommunicationRoutine, nullptr);
    while (1) {
        f = accept(s, NULL, 0);
        
        if (f == -1) {
			fprintf(stderr, "accept() failed\n");
			return 0;
		}
		client * d = new client;
		
		int * fd = new int;
		*fd = f;
		d->fd = fd;
		
		
		pthread_create(&tid, NULL, hconnect, (void *)d);
		
    }

    return 0;
}
