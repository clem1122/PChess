#pragma once
#include <string>

class Piece{
private:
	char type_;
	std::string coord_;
	bool isWhite_;


public: 
	Piece();
	Piece(const char _type, const std::string _coord, bool _isWhite);
	
	char type()const{return type_;}
	std::string coord(){return coord_;}
	bool isWhite()const{return isWhite_;}
	
	~Piece();
	

};

