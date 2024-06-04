#pragma once
#include "piece.h"

class Move{
private:
	char start_[3];
	char end_[3];
	
	Piece movingPiece_; // = new Piece("Q", "d1", true);
	
	bool isCapture_;
	bool isPromotion_;
	bool isCastling_;
	bool isEnPassant_;

public:
	Move();
	Move(const char* _start, const char* _end, Piece _movingPiece, bool _isCapture, bool _isPromotion, bool _isCastling, bool _isEnPassant);
	char* start()const{return const_cast<char*>(start_);}
	char* end()const{return const_cast<char*>(end_);}

	
	Piece movingPiece()const{return movingPiece_;} // = new Piece("Q", "d1", true);
	
	bool isCapture()const{return isCapture_;};
	bool isPromotion()const{return isPromotion_;}
	bool isCastling()const{return isCastling_;}
	bool isEnPassant()const{return isEnPassant_;}
	
	void set_isCapture(bool b){isCapture_ = b;}

	~Move();
	
};
