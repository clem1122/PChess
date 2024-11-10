#include "move.h"
#include <cstring>
#include <iostream>


Move::Move(){

}

Move::Move(std::string _start, std::string _end, Piece _movingPiece, bool _isCapture, bool _isPromotion, bool _isCastling, bool _isEnPassant){

	movingPiece_ = _movingPiece;
	isCapture_ = _isCapture;
	isPromotion_ = _isPromotion;
	isCastling_ = _isCastling;
	isEnPassant_ = _isEnPassant;
	
	start_ = _start;
	end_ =  _end;
	
}

Move::~Move() {

}



















