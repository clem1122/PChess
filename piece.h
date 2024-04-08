#pragma once

class Piece{
private:
	char type_;
	char coord_[2];
	bool isWhite_;


public: 
	Piece();
	Piece(const char _type, const char* _coord, bool _isWhite);
	
	char type()const{return type_;}
	char* coord(){return coord_;}
	bool isWhite()const{return isWhite_;}
	

};
	
