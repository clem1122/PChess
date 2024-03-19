#pragma once
#include "piece.h"
#include "move.h"

class Board{
public:
	char FEN[64];
	char specialRulesData[6];
	Piece* pieces;
	
	Board();
	Board(const char* FEN);
	~Board();
	
	char indexToCoord(const int &index);
	int coordToIndex(const char* &coord);
	Board playMove(const Move move);
	
	Piece* FENtoPieces(const char* _FEN);
	char* PiecestoFEN(const Piece* _pieces);
	
	bool isLegal(const Move move);
}; 
	
	
