#include "piece.h"
#include <cstring>

Piece::Piece(const char _type, const char(&_coord)[4], bool _isWhite) {
	type = _type;
	memcpy(coord, _coord, 4 * sizeof(char));
	isWhite = _isWhite;
}

