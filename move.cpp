#include "move.h"
#include <cstring>
#include <iostream>

Move::Move(const char* _start, const char* _end, Piece _movingPiece, bool _isCapture, bool _isPromotion, bool _isCastling, bool _isEnPassant){
	
	movingPiece = _movingPiece;
	isCapture = _isCapture;
	isPromotion = _isPromotion;
	isCastling = _isCastling;
	isEnPassant = _isEnPassant;
	char departure_column=_start[0];
	char arrival_column=_end[0];
	int departure_row=_start[1] - '0';
	int arrival_row=_end[1] - '0';

	//Check if the coordinates do have sense
	if ( 	'a'<=departure_column && departure_column<='h'
		&& 'a'<=arrival_column && arrival_column<='h'
		&& 1<=departure_row && departure_row<=8
		&& 1<=arrival_row && arrival_row<=8
		&& departure_column!=arrival_column 
		&& departure_row != arrival_row){
	
		memcpy(start, _start, 2 * sizeof(char));
		memcpy(end, _end, 2 * sizeof(char));
		
	}
	
	else{}
	//Raise error and send message if not good
}


