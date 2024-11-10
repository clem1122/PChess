#include "piece.h"
#include <string>
#include <iostream>


Piece::Piece() {
	type_ = '.';
}

Piece::Piece(const char _type, std::string _coord, bool _isWhite) {
	type_ = _type;
	if (_coord.length() != 2) {
		std::cout << "Error Piece :" << _coord << ">" << std::endl;
	}
	coord_ = _coord;
	isWhite_ = _isWhite;
}

Piece::~Piece() {

}

