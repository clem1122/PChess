#include "piece.h"
#include <cstring>


Piece::Piece() {
	type_ = '.';
}

Piece::Piece(const char _type, const char* _coord, bool _isWhite) {
	type_ = _type;
	memcpy(coord_, _coord, 4 * sizeof(char));
	isWhite_ = _isWhite;
}

