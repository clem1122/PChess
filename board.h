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
	
	char* indextoCoord(const int &index);
	int coordtoIndex(const char* coord);
	Board playMove(const Move move);
	
	Piece* FENtoPieces(const char* _FEN);
	char* PiecestoFEN(const Piece* _pieces);
	
	bool isLegal(const Move move);
	bool is_piece_on_square(int index_arrival);
	bool is_white_on_square(int index_arrival);
	bool is_piece_correctly_moving(const Move move);
	
	bool isCheck(const char* _FEN);
	
	void print();
}; 
	
	
