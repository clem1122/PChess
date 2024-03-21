#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>
#include "base.h"
#include <cstring>

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

int main (int argc, char * argv[])
{
    struct sockaddr_in saddr;
    struct hostent * server;
    int s, ret;
	char * buf;
	char *name;

	if (argc == 1) {
		std::cerr << "usage: " << argv[0] 
			  << " [ adresse IP/nom du serveur ]" << std::endl;
		return 0;
	}

        s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (s < 0) {
                std::cerr << "cannot create socket" << std::endl;
                return 0;
        }

        saddr.sin_family = AF_INET;
        saddr.sin_port = htons(DEFAULT_PORT);
        server = gethostbyname(argv[1]);
        if (server == NULL) {
                std::cerr << "gethostbyname() failed" << std::endl;
		close(s);
                return 0;
        }
        else {
                memcpy(&saddr.sin_addr, server->h_addr, 4);
        }

        ret = connect(s, (struct sockaddr *)&saddr, sizeof(saddr));
        if (ret < 0) {
                std::cerr << "cannot connect to remote server" << std::endl;
                close(s);
                return 0;
        }

	buf = receive(s);
	std::cout << buf << std::endl;
	name = argv[2];
	send(s, name);
	
	

	close(s);
	delete [] buf;
	return 0;
}
