#include "game.h"
#include "board.h"
#include "move.h"
#include "piece.h"
#include <iostream>

int main() {

	const char* msg = "e2e4";
	Piece p;
	Board b;
	Move move = b.create_move(msg);
//	Move move = Move(start, end, p, false, false, false, false);
	std::cout << "4: Start : " << move.start << " End : " << move.end << std::endl;

	return 0;
}


