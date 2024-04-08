#include "move.h"
#include <cstring>
#include <iostream>


Move::Move(){

}

Move::Move(const char* _start, const char* _end, Piece _movingPiece, bool _isCapture, bool _isPromotion, bool _isCastling, bool _isEnPassant){

	movingPiece_ = _movingPiece;
	isCapture_ = _isCapture;
	isPromotion_ = _isPromotion;
	isCastling_ = _isCastling;
	isEnPassant_ = _isEnPassant;
	
	strncpy(start_, _start, 2);
	strncpy(end_, _end, 2);

	start_[2] = '\0';
	end_[2] = '\0';

	
}



















