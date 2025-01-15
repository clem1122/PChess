#include "game.h"
#include "board.h"
#include "move.h"
#include "piece.h"
#include <iostream>
#include <cstring>

int main() {

	Game game("..............Q..p.......K......p..p....P..P...................k");
	//	Board b("..............Q..p.......K......p..p....P..P...................k");
	game.play("g7g3");
	game.printHistory();
	return 0;
}


