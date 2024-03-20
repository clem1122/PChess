#include "board.h"
#include <iostream>
#include <cstring>
#include <cctype>

// Board Constructor
Board::Board() {
	const char *startFEN = "rnbqkbnrpppppppp................................PPPPPPPPRNBQKBNR";
	memcpy(&FEN, startFEN, 64 * sizeof(char)); 
}

// Board Constructor with FEN parameter
Board::Board(const char* _FEN) {
	memcpy(&FEN, _FEN, 64 * sizeof(char)); 
	
}

// Board Destructor
Board::~Board() {
    // Implement destructor logic here
}

// Utility function to convert index to coordinate
char* Board::indextoCoord(const int &index) {
    char* coord = new char[2];
    const char* ref = "abcdefgh";
    int row = 8 - (index / 8);
    char column = ref[index % 8];
    
    coord[0] = column;
    coord[1] = '0' + row;// conversion in char
    return coord;
}

// Utility function to convert coordinate to index
int Board::coordtoIndex(const char* coord) {
    char column = coord[0]; //"a4" -> "a"
    int row = coord[1] - '0'; //"a4" -> 4
    int columnNb = 0;
    const char* ref = "abcdefgh";
    for(int i = 0; i < 8; i++){
    	if (column == ref[i]){
    		columnNb = i; // a = 0, h = 7
    		break; 
    	}
    }
    int index = (8-row) * 8 + columnNb;
    return index; // tkt ça marche
}

// Utility function to play a move
Board Board::playMove(const Move move) {
	int startIndex = Board::coordtoIndex(move.start);
	int endIndex = Board::coordtoIndex(move.end);
	
	char newFEN[64];
	memcpy(&newFEN, &FEN, 64 * sizeof(char));
	newFEN[startIndex] = '.';
	newFEN[endIndex] = move.movingPiece.type; 

	Board *newBoard = new Board(newFEN);
	
    return *newBoard;
}

// Utility function to convert FEN string to pieces
Piece* Board::FENtoPieces(const char* _FEN) {
	Piece *p = new Piece[32];
	int pieceNb = 0; 
	for(int i = 0; i < 64; i++) {
		if(_FEN[i] != '.') {
			p[pieceNb] = Piece(_FEN[i], Board::indextoCoord(i), (bool)std::isupper(_FEN[i]));
			std::cout << p[pieceNb].type << std::endl;
			pieceNb++;

		}
	}
    return p;
}

// Utility function to convert pieces to FEN string
char* Board::PiecestoFEN(const Piece* _pieces) {
	//char newFEN[64]; 
    return nullptr;
}

// Game logic function to check if a move is legal
bool Board::isLegal(const Move move) {
    return true;
}

void Board::print(){
	for (int i = 0; i<64;i++){
		std::cout << FEN[i] << ' ';
		if ((i+1) % 8 == 0 && i != 0) {
			std::cout << std::endl;
		}
	}
}





