#include "game.h"
#include "board.h"
#include "move.h"
#include <iostream>

int main() {
	Board* b = new Board();
	b->print();
	b->FENtoPieces(b->FEN);

	return 0;
}


