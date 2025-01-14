#include "game.h"
#include "board.h"
#include "move.h"
#include "piece.h"
#include <iostream>
#include <cstring>

int main() {

	Board b("..............Q..p.......K......p..p....P..P...................k");
	b.print();
	b.play("g7g3");
	return 0;
}


