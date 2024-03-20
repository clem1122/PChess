#pragma once
#include "piece.h"

class Move{
public:
	char start[2];
	char end[2];
	
	Piece movingPiece; // = new Piece("Q", "d1", true);
	
	bool isCapture;
	bool isPromotion;
	bool isCastling;
	bool isEnPassant;
	
	Move(const char* start, const char* end);
	
};
