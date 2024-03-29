#include "move.h"
#include <cstring>
#include <iostream>


Move::Move(){
	std::cout << "constructor 1" << std::endl; 
}

Move::Move(const char* _start, const char* _end, Piece _movingPiece, bool _isCapture, bool _isPromotion, bool _isCastling, bool _isEnPassant){

	std::cout << "1: Start : " << _start << " End : " << _end << std::endl;
	movingPiece = _movingPiece;
	isCapture = _isCapture;
	isPromotion = _isPromotion;
	isCastling = _isCastling;
	isEnPassant = _isEnPassant;
	
	strncpy(start, _start, 2);
	strncpy(end, _end, 2);
	std::cout << "2: Start : " << _start << " End : " << _end << std::endl;
	
	start[2] = '\0';
	end[2] = '\0';
	std::cout << "3: Start : " << _start << " End : " << _end << std::endl;
	
}



















