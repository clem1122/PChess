#include "game.h"
#include "board.h"
#include "move.h"
#include "piece.h"
#include <iostream>
#include <cstring>

int main() {

	Board b("rnbqkbnrpppppppp................................PPPPPPPPRNBQKBNR");
	const char* case_verif = "e1";
	std::cout << "case vérifiée " <<case_verif << std::endl;
	bool est_echec_blanc = b.isCheck(b,true,case_verif);
	
	std::cout << "Echec en " << case_verif << " ? " << est_echec_blanc <<std::endl;
	
	

	return 0;
}


