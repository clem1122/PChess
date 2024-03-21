#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#include "base.h"
#include "game.h"

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

char * receive(int s) {
	size_t len;
	ssize_t size;
	size = read(s, &len, sizeof(len));
	if (size != sizeof(len));
	char * buf = new char [len + 1];
	size = read(s, buf, 1 + len);
	return buf;

}

void * hconnect (void * t)
{
	
	client *d =  (client*)t;
	int client_fd = *(d->fd);
	char client_ip[INET_ADDRSTRLEN];
    sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
	
	getpeername(client_fd, (sockaddr *)&addr, &addr_len);
    inet_ntop(AF_INET, &addr.sin_addr, client_ip, INET_ADDRSTRLEN);
	int f = *((int *)d->fd);

	send(f, client_ip);
	char* name = receive(f);
	if (game.socketJ1 == 0) {
		std::cout << "first connexion : " << name  << " socket : " << f << std::endl;
		game.socketJ1 = f;	
		game.nameJ1 = name;
	} else {
		game.socketJ2 = f;
		game.nameJ2 = name;
		std::cout << "second connexion : " << name << " socket : " << f << std::endl;
		if(game.socketJ2 == game.socketJ1) {std::cout << "ohoh" << std::endl;}
	}
	close(f);

	free(d);
	pthread_detach(pthread_self());
	return NULL;	
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
