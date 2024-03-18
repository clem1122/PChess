#include "move.h"

Move::Move(const char* _start, const char* _end){
	memcpy(start, _start, 2 * sizeof(char));
	memcpy(end, _end, 2 * sizeof(char));
}
