#pragma once
#include "piece.h"

class Move{
public:
	char start[2]; // TODO : Gérer le stack overflow
	char end[2];
	
	Piece movingPiece; // = new Piece("Q", "d1", true);
	
	bool isCapture;
	bool isPromotion;
	bool isCastling;
	bool isEnPassant;
	
	Move();
	Move(const char* _start, const char* _end, Piece _movingPiece, bool _isCapture, bool _isPromotion, bool _isCastling, bool _isEnPassant);
	
	
};
