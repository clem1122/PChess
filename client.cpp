#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <boost/asio.hpp>
#include <iostream>
#include "base.h"
#include <cstring>

using namespace boost::asio;
using ip::tcp;
using std::string;

char FEN[64];

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
	char * buf = new char [len + 1];
	size = read(s, buf, 1 + len);
	return buf;

}

string createRequest(std::string msg) {
    return "HTTP/1.1 200 OK\r\n"
           "Content-Type: text/plain\r\n"
           "Access-Control-Allow-Origin: *\r\n" // Allow requests from any origin
           "Access-Control-Allow-Methods: GET, POST, OPTIONS\r\n" // Allow specified methods
           "Access-Control-Allow-Headers: Content-Type\r\n" // Allow specified headers
           "\r\n" + msg;
}

void* HTMLManager(void* _) {
	io_service io;

    // Create a TCP acceptor
    
    tcp::acceptor acceptor(io);
	int port = 8080;
	//tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), port));
	acceptor.open(tcp::v4());
	
	
	while (true) {
    	try {
    		std::cout << "Port : " << port << std::endl;
		    
		    acceptor.bind(tcp::endpoint(tcp::v4(), port));
		    acceptor.listen();
		    
       		break; // Successful bind, exit loop
        
		} catch (boost::system::system_error& e) {
				std::cout << e.what() << std::endl;
		        port++;
		        if(port > 10000) {port = 8080;}
		        continue;
   		}
	}
	
    while (true) {
        // Accept incoming connections
        tcp::socket socket(io);
        acceptor.accept(socket);
		
        // Read the request
        boost::system::error_code error;
        boost::asio::streambuf request;
        boost::asio::read_until(socket, request, "\r\n\r\n", error);
		std::istream request_stream(&request);
    	std::stringstream request_data;
    	request_data << request_stream.rdbuf();

   		//Print the request data
    	//std::cout << "Request data:\n" << request_data.str() << std::endl;
		
        // Send the response

    	std::string response = createRequest(FEN);
    	boost::asio::write(socket, boost::asio::buffer(response));
        
        
    }


}

int main (int argc, char * argv[])
{
    struct sockaddr_in saddr;
    struct hostent * server;
    char *buf;
    int s, ret;
	char input[5];
	bool isMyTurn;
	pthread_t tid;

	pthread_create(&tid, NULL, HTMLManager, nullptr);
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
        
    
	std::cout << "Listening..." << std::endl;
	
	buf = receive(s);
	if (strcmp(buf, "1") == 0) {
		isMyTurn = true;
	} else if (strcmp(buf, "2")) {
		isMyTurn = false;
	} else {
		std::cout << "Error on data received" << std::endl;	
		isMyTurn = false;
	}
	

	while (true) { 
		if (isMyTurn) {
		    std::cout << "Move to play : ";
		    std::cin.getline(input, sizeof(input)); 
		    send(s, input); 
        }
        
		buf = receive(s);
		if(strcmp(buf, "err0") == 0) {
			std::cout << "Illegal move" << std::endl;
		} else {
		    std::cout << "FEN received : " << buf << std::endl;
		    memcpy(FEN, buf, 64 * sizeof(char));
		    isMyTurn = !isMyTurn;
		}
		 
		
    }
	delete [] buf; // Free memory allocated for response
	

	close(s);
	return 0;
}
