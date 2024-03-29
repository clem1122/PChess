#include "move.h"
#include <cstring>
#include <iostream>


Move::Move(){

}

Move::Move(const char* _start, const char* _end, Piece _movingPiece, bool _isCapture, bool _isPromotion, bool _isCastling, bool _isEnPassant){

	movingPiece = _movingPiece;
	isCapture = _isCapture;
	isPromotion = _isPromotion;
	isCastling = _isCastling;
	isEnPassant = _isEnPassant;
	
	strncpy(start, _start, 2);
	strncpy(end, _end, 2);

	start[2] = '\0';
	end[2] = '\0';

	
}



















