#include "game.h"
#include "board.h"
#include "move.h"
#include "piece.h"
#include <iostream>
#include <cstring>

int main() {

	Board b("............Q..........k...........P...P..P.P...PP..P.P.RNB.KB.R");
	b.print();
	b.play("e3e4");
	return 0;
}


