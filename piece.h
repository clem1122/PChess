#pragma once
class Piece{
public:
	char type;
	char coord[4];
	bool isWhite;
	Piece(const char type, const char (&coord)[4], bool isWhite);
	
};
	
