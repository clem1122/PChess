#pragma once
#include "piece.h"
#include <string>

class Move{
private:
	std::string start_;
	std::string end_;
	
	Piece movingPiece_; // = new Piece("Q", "d1", true);
	
	bool isCapture_;
	bool isPromotion_;
	bool isCastling_;
	bool isEnPassant_;

public:
	Move();
	Move(std::string _start, std::string _end, Piece _movingPiece, bool _isCapture, bool _isPromotion, bool _isCastling, bool _isEnPassant);
	std::string start()const{return start_;}
	std::string end()const{return end_;}

	
	Piece movingPiece()const{return movingPiece_;} // = new Piece("Q", "d1", true);
	
	bool isCapture()const{return isCapture_;};
	bool isPromotion()const{return isPromotion_;}
	bool isCastling()const{return isCastling_;}
	bool isEnPassant()const{return isEnPassant_;}
	
	void set_isCapture(bool b){isCapture_ = b;}

	~Move();
	
};
