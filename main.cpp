#include "game.h"
#include "board.h"
#include "move.h"
#include "piece.h"
#include <iostream>
#include <cstring>

int main() {

	Board b("rnbqk.nrpppp.ppp............p....b.P.........N..PPP.PPPPRNBQKB.R");
	Move m = b.create_move("c1d2");
	b.withMove(m).print();
	b.print();
	const char* case_verif = "e1";
	std::cout << "case vérifiée " <<case_verif << std::endl;
	bool est_echec_blanc = b.isCheck(true,case_verif);
	bool ischeck = b.withMove(m).isCheck(true, case_verif);
	
	std::cout << "Echec en " << case_verif << " ? " << est_echec_blanc <<std::endl;
	std::cout << " 2 Echec en " << case_verif << " ? " << ischeck <<std::endl;
	

	return 0;
}


