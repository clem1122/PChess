#include "board.h"
#include "move.h"
#include <iostream>
#include <cstring>
#include <cctype>

// Board Constructor
Board::Board() {
	const char *startFEN = "rnbqkbnrpppppppp................................PPPPPPPPRNBQKBNR";
	memcpy(&FEN, startFEN, 64 * sizeof(char));
	pieces = FENtoPieces(FEN);
}

// Board Constructor with FEN parameter
Board::Board(const char* _FEN) {
	memcpy(&FEN, _FEN, 64 * sizeof(char)); 
	pieces = FENtoPieces(FEN);
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
Board Board::withMove(const Move move) {
	int startIndex = Board::coordtoIndex(move.start);
	int endIndex = Board::coordtoIndex(move.end);
	
	char newFEN[64];
	memcpy(&newFEN, &FEN, 64 * sizeof(char));
	newFEN[startIndex] = '.';
	newFEN[endIndex] = FEN[startIndex]; 

	Board *newBoard = new Board(newFEN);
	
    return *newBoard;
}

// Utility function to convert FEN string to pieces
Piece* Board::FENtoPieces(const char* _FEN) {
	Piece *p = new Piece[64]; 
	for(int i = 0; i < 64; i++) {
		if(_FEN[i] != '.') {
			p[i] = Piece(_FEN[i], Board::indextoCoord(i), (bool)std::isupper(_FEN[i]));
		}
	}
    return p;
}

// Utility function to convert pieces to FEN string
char* Board::PiecestoFEN(const Piece* _pieces) {
	char *newFEN = new char[64];
	for(int i = 0; i < 64; i++) {
			newFEN[i] = _pieces[i].type;
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

// Utility function to create move

Move Board::create_move(const char* msg){
	char start[3];
	char end[3];	
	
	memcpy(start, msg, 2);
	memcpy(end, msg+2, 2);


	if (isValidCoord(start, end)) {
	
		int startIndex = coordtoIndex(start);
		
		Piece piece = pieces[startIndex];
//		std::cout << "piecetype : " << piece.type << std::endl;
		return Move(start, end, piece, false, false, false, false);
		
	} else {
		std::cout << "Illegal Move : bad coord" << std::endl;
		return Move();
	}


}

void Board::playMove(Move move) {
	Board newBoard = withMove(move);
	memcpy(&FEN, &(newBoard.FEN), 64 * sizeof(char));
	pieces = newBoard.pieces;
}

bool Board::is_piece_correctly_moving(const Move move){

	// Get infos from move
	char departure_column=move.start[0];
	char arrival_column=move.end[0];
	int departure_row=move.start[1] - '0';
	int arrival_row=move.end[1] - '0';

	
	if (move.movingPiece.type=='r' 
	 || move.movingPiece.type=='R' 
	 || move.movingPiece.type=='q' 
	 || move.movingPiece.type=='Q')
	{
		//Rook/Queen must have a move along a column or a row	
		if (departure_column == arrival_column || departure_row == arrival_row){
			return true;
		}
	}
		
	if (move.movingPiece.type=='b' 
	 || move.movingPiece.type=='B' 
	 || move.movingPiece.type=='q' 
	 || move.movingPiece.type=='Q')
	{
		//Bishop/Queen must increase row and column the same way
		int gap = std::abs(arrival_row-departure_row);

		if (std::abs(arrival_column - departure_column) == gap){
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
	//Pawn can only move 1 row depending on its color or 2 if it is on its starting place
	
		int row_gap=departure_row-arrival_row;
		int column_gap=departure_column-arrival_column;
		bool isMovingUp = row_gap>0;
		bool isOnStartingRow = false;
		
		//Check if pawn moves toward good direction
		bool isMovingGoodDirection = move.movingPiece.isWhite && isMovingUp; 
		
		//Check if on starting row
		if ( (move.movingPiece.isWhite && departure_row==2) 
		 || (not move.movingPiece.isWhite && departure_row==7) ){
		 
		 	isOnStartingRow = true;
		 } 


		if (isMovingGoodDirection){
			if (column_gap==0 && not move.isCapture){

				if (std::abs(row_gap)==1){
					return true;
				}

				if (std::abs(row_gap)==2 && isOnStartingRow){
					return true;
				}

			if (std::abs(column_gap)==1 && std::abs(row_gap)==1 && move.isCapture){
				return true;
				
			}
		}

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
	}
	
	return false;
}


bool Board::is_there_obstacle(const Move move){
	//Return true if there is a piece able to block the move of the piece on its way.
	//This function does NOT check the case of a piece ON the arrival square, another function is in charge of this
	
	// Get infos from move
	char start_col=move.start[0];
	char end_col=move.end[0];
	char start_row=move.start[1];
	char end_row=move.end[1];
	char coord_considered[2];

	// Rook/Queen case
	if (move.movingPiece.type=='r' 
	 || move.movingPiece.type=='R' 
	 || move.movingPiece.type=='q' 
	 || move.movingPiece.type=='Q'){
	 
	 	if (end_row == start_row) //Move along a row
	 	{	 	
	 		coord_considered[1]=start_row;
	 		int gap = std::abs(end_col-start_col);
	 		int direction = (end_col-start_col)/gap; //Positive toward right, negative toward left
	 		
	 		for (int i=1 ; i<gap ; i++)
	 		{
	 			coord_considered[0]=start_col + i*direction; //Check squares on the left or right depending on direction
	 			int index_considerd=coordtoIndex(coord_considered);
	 			if (is_piece_on_square(index_considerd)){return true;}
	 		
	 		}
	 	}
	 	
	 	if (end_col == start_col) //Move along a column
	 	{
	 		coord_considered[0]=start_col;
	 		int gap = std::abs(end_row-start_row);
	 		int direction = (end_row - start_row)/gap; //Positive toward up, negative toward down
	 		
	 		for (int i=1 ; i<gap ; i++)
	 		{
	 			coord_considered[1]=start_row + i*direction; //Check squares on the up or down depending on direction
	 			int index_considered=coordtoIndex(coord_considered);
	 			
	 			if (is_piece_on_square(index_considered)){return true;}
	 		}
	 	}
	 }
	 
	 // Bishop/Queen case
	 if (move.movingPiece.type=='b' 
	 || move.movingPiece.type=='B' 
	 || move.movingPiece.type=='q' 
	 || move.movingPiece.type=='Q'){
	 
	 	int gap = std::abs(end_row-start_row);
	 	int direction_row = (end_row-start_row)/gap;
	 	int direction_col = (end_col - start_col);
	 	
	 	for (int i=1 ; i<gap ; i++)
	 	{
	 		coord_considered[0] = start_col + i*direction_col;
	 		coord_considered[1] = start_row + i*direction_row;
	 		int index_considered=coordtoIndex(coord_considered);
	 		
	 		if (is_piece_on_square(index_considered)){return true;}
	 	}
	 }
	 
	 // Pawn case
	 if (move.movingPiece.type=='p' || move.movingPiece.type=='P'){
	 
	 	int gap = std::abs(end_row - start_row);
	 	int direction = end_row - start_row;
	 	
	 	if (gap==2)
	 	{
	 		coord_considered[0] = start_col;
	 		coord_considered[1] = start_row + direction;
	 		int index_considered=coordtoIndex(coord_considered);
	 		
	 		if (is_piece_on_square(index_considered)){return true;}
	 	}
	 
	 }
	 
	 // King case does not need to be done becasue it only moves one square at a time
	 // Knight case does not need to be done because knight precisely do not bother with piece on their way
	
	return false;
}
bool Board::isValidCoord(const char* _start, const char* _end) {
	char departure_column=_start[0];
	char arrival_column=_end[0];
	int departure_row=_start[1] - '0';
	int arrival_row=_end[1] - '0';

	//Check if the coordinates do have sense
	return 	'a' <= departure_column && departure_column <= 'h'
		&&  'a' <= arrival_column   && arrival_column   <= 'h'
		&&   1  <= departure_row    && departure_row    <=  8
		&&   1  <= arrival_row      && arrival_row      <=  8
		&&        (departure_column != arrival_column 
		||         departure_row    != arrival_row);
		
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





