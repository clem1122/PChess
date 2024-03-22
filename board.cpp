#include "board.h"
#include <iostream>
#include <cstring>
#include <cctype>

// Board Constructor
Board::Board() {
	const char *startFEN = "rnbqkbnrpppppppp................................PPPPPPPPRNBQKBNR";
	memcpy(&FEN, startFEN, 64 * sizeof(char)); 
}

// Board Constructor with FEN parameter
Board::Board(const char* _FEN) {
	memcpy(&FEN, _FEN, 64 * sizeof(char)); 
	
}

// Board Destructor
Board::~Board() {
    // Implement destructor logic here
}

// Utility function to convert index to coordinate
char* Board::indextoCoord(const int &index) {
    char* coord = new char[2];
    const char* ref = "abcdefgh";
    int row = 8 - (index / 8);
    char column = ref[index % 8];
    
    coord[0] = column;
    coord[1] = '0' + row; // conversion in char
    return coord;
}

// Utility function to convert coordinate to index
int Board::coordtoIndex(const char* coord) {
    char column = coord[0]; //"a4" -> "a"
    int row = coord[1] - '0'; //"a4" -> 4
    int columnNb = 0;
    const char* ref = "abcdefgh";
    for(int i = 0; i < 8; i++){
    	if (column == ref[i]){
    		columnNb = i; // a = 0, h = 7
    		break; 
    	}
    }
    int index = (8-row) * 8 + columnNb;
    return index; // tkt ça marche
}

// Utility function to play a move
Board Board::playMove(const Move move) {
	int startIndex = Board::coordtoIndex(move.start);
	int endIndex = Board::coordtoIndex(move.end);
	
	char newFEN[64];
	memcpy(&newFEN, &FEN, 64 * sizeof(char));
	newFEN[startIndex] = '.';
	newFEN[endIndex] = move.movingPiece.type; 

	Board *newBoard = new Board(newFEN);
	
    return *newBoard;
}

// Utility function to convert FEN string to pieces
Piece* Board::FENtoPieces(const char* _FEN) {
	Piece *p = new Piece[64];
	int pieceNb = 0; 
	for(int i = 0; i < 64; i++) {
		if(_FEN[i] != '.') {
			p[pieceNb] = Piece(_FEN[i], Board::indextoCoord(i), (bool)std::isupper(_FEN[i]));
			std::cout << p[pieceNb].type << std::endl;
			pieceNb++;
		}
	}
    return p;
}

// Utility function to convert pieces to FEN string
char* Board::PiecestoFEN(const Piece* _pieces) {
	char *newFEN = new char[64];
	for(int i = 0; i < 64; i++) {
			newFEN[index] = _pieces[i].type;
	}
    return newFEN;
}

// Utility function to check some infos on the board


bool Board::is_piece_on_square(int index_arrival){

	if (FEN[index_arrival] != '.'){
		return true;
	}
	
	return false;
}

bool Board::is_white_on_square(int index_arrival){

	if (is_piece_on_square(index_arrival) && isupper(FEN[index_arrival])){
		return true;
	}
	
	return false;
}

// Game logic function to check if a move is legal



bool Board::is_piece_correctly_moving(const Move move){

	// Get infos from move
	
	char departure_column=move.start[0];
	char arrival_column=move.end[0];
	int departure_row=move.start[1] - '0';
	int arrival_row=move.end[1] - '0';

	
	if (move.movingPiece.type=='r' || move.movingPiece.type=='R' || move.movingPiece.type=='q' || move.movingPiece.type=='Q'){
		//Rook/Queen must have a move along a column or a row
		
		int similarities=0;
		
		if (departure_column==arrival_column){similarities+=1;}
		if (departure_row==arrival_row){similarities+=1;}
		
		if (similarities==1){
			return true;
		}
	}
		
	if (move.movingPiece.type=='b' || move.movingPiece.type=='B' || move.movingPiece.type=='q' || move.movingPiece.type=='Q'){
		//Bishop/Queen must increase row and column the same way
		
		int gap=arrival_row-departure_row;
		
		if ((arrival_column - gap)==departure_column){
			return true;
		}
	}
		
	if (move.movingPiece.type=='k' || move.movingPiece.type=='K'){
		//King can only change its row/column by 1
		
		int row_gap=std::abs(departure_row-arrival_row);
		char column_gap=std::abs(departure_column-arrival_column);
		
		if (row_gap>1){return false;}
		if (column_gap>1){return false;}
		
		return true;
	}
	
	if (move.movingPiece.type=='p' || move.movingPiece.type=='P'){
		//Pawn can only move 1 row depending on its color or 2 if it is in its starting place
	
		int row_gap=departure_row-arrival_row;
		int column_gap=departure_column-arrival_column;
		
		if (move.movingPiece.isWhite && row_gap==1){return true;}
		if (not move.movingPiece.isWhite && row_gap==-1){return true;}

		//Check if pawn moves toward good direction
		if (move.movingPiece.isWhite && row_gap<0){return false;}
		if (not move.movingPiece.isWhite && row_gap>0){return false;}
		
		//If it moves more than 2 squares, not good
		if (std::abs(row_gap)>2){return false;}
		
		//If it moves 2 squares, check color and if still on the starting row
		if (std::abs(row_gap)==2){
		
			if (move.movingPiece.isWhite && departure_row!=2){return false;}
			if (not move.movingPiece.isWhite && departure_row!=7){return false;}
		}
		
		//If it moves horizontally, not good unless capturing
		if (std::abs(column_gap)>1){return false;}
		
		if (std::abs(column_gap)==1 && not move.isCapture){return false;}
		
		return true;

	}
	
	if (move.movingPiece.type=='n' || move.movingPiece.type=='N'){
		//Knight can only move on 8 squares easily seen with the FEN
		
		int startIndex = Board::coordtoIndex(move.start);
		int endIndex = Board::coordtoIndex(move.end);
		
		int FEN_gap=std::abs(startIndex-endIndex);
		
		if (FEN_gap==6 || FEN_gap==10 || FEN_gap==15 || FEN_gap==17){
			return true;
		}
	
	}
	
	return false;
}


bool Board::isLegal(const Move move) {

	//int startIndex = Board::coordtoIndex(move.start);
	//char played_piece=FEN[startIndex];
	
	if(Board::is_piece_correctly_moving(move)){return true;}
	
    return false;
}

// Game logic to check if there is check on the king POV ('k' or 'K' for now)
bool Board::isCheck(const char* _FEN) {
	bool check = false;
	int king_index = 100;
	char POV = 'k';
	for(int i = 0; i < 64; i++) {
		if(_FEN[i] == POV) {
		king_index = i;
		}
	}
	
	if (king_index ==100){
		throw "King not found";
	}
	// check line for rook or queen
	int p = king_index + 1;
	while(p%8 != 1){
		if(_FEN[p] != '.'){
			if ((_FEN[p] == 'R') | (_FEN[p] == 'Q')){
				return true;
			}
			break;  
		}
		p += 1;
	}
	
	p = king_index - 1;
	while(p%8 != 0){
		if(_FEN[p] != '.'){
			if ((_FEN[p] == 'R') | (_FEN[p] == 'Q')){
				return true;
			}
			break;  
		}
		p -= 1;
	}

	p = king_index + 8;
	while(p < 64){
		if(_FEN[p] != '.'){
			if ((_FEN[p] == 'R') | (_FEN[p] == 'Q')){
				return true;
			}
			break;  
		}
		p = p + 8; 
	}
	
	p = king_index - 8;
	while(p >= 0){
		if(_FEN[p] != '.'){
			if ((_FEN[p] == 'R') | (_FEN[p] == 'Q')){
				return true;
			}
			break;  
		}
		p = p - 8; 
	}
	
	// check diagonals for bishop or queen //
	// check some indexes for knight and king and pawn
	
	return check;
}
void Board::print(){
	for (int i = 0; i<64;i++){
		std::cout << FEN[i] << ' ';
		if ((i+1) % 8 == 0 && i != 0) {
			std::cout << std::endl;
		}
	}
}





