#include "game.h"
#include "board.h"
#include "move.h"
#include "piece.h"
#include <iostream>
#include <cstring>

int main() {


	//Game game("rnbqkbnrpppppppp................................PPPPPPPPRNpQKBNR");
	//std::cout << game.board.threatSquares(false) << std::endl;	
	Game game;
	std::cout << game.board.protectedPieces(true) << std::endl; 
	game.play("b1a4");
	game.play("b1c3");

	return 0;
}


