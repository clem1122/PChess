#pragma once
#include "board.h"

class Game{
public:
	int socketJ1;
	int socketJ2;
	char* nameJ1;
	char* nameJ2;
	bool isOver;
	
	Board board;
	Game();
	~Game();
};

//172.23.230.84
