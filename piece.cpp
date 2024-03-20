#include "piece.h"
#include <cstring>


Piece::Piece() {

}

Piece::Piece(const char _type, const char* _coord, bool _isWhite) {
	type = _type;
	memcpy(coord, _coord, 4 * sizeof(char));
	isWhite = _isWhite;
}

