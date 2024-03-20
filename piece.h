#pragma once
class Piece{
public:
	char type;
	char coord[2];
	bool isWhite;
	Piece();
	Piece(const char _type, const char* _coord, bool _isWhite);
	
};
	
