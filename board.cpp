#include "board.h"
#include "move.h"
#include <iostream>
#include <cstring>
#include <cctype>

// Board Constructor
Board::Board() {
	const char *startFEN = "rnbqkbnrpppppppp................................PPPPPPPPRNBQKBNR";
	memcpy(&FEN_, startFEN, 64 * sizeof(char));
	memcpy(&specialRulesData_, "wKQkq", 5 * sizeof(char));
	en_passant_index_=99;
	pieces_ = FENtoPieces(FEN_);
	
}

// Board Constructor with FEN parameter
Board::Board(const char* _FEN) {
	memcpy(&FEN_, _FEN, 64 * sizeof(char)); 
	pieces_ = FENtoPieces(FEN_);
}

// Board Destructor
Board::~Board() {
    
}

// Utility function to modify easily the special rules array

void Board::change_turn(){

	if (specialRulesData_[0]=='w'){
	
		specialRulesData_[0]='b';
	}
	
	else
	{
		specialRulesData_[0]='w';
	}
}

void Board::change_en_passant_square(bool has_a_pawn_moved, bool is_pawn_white, const char* end_coord){
	//Change the index in the special rule array 
	// This new index correspond to the square behind the new position of the pawn, where a En Passant can be done
	if (has_a_pawn_moved)
	{
		int end_index = Board::coordtoIndex(end_coord);
		int en_passant_square = 99;
		
		//Select the index of the square behind the pawn
		if (is_pawn_white){en_passant_square = end_index + 8; }
		if (not is_pawn_white){en_passant_square = end_index - 8; }
		
		en_passant_index_=en_passant_square;
	}
	
	else
	{
		en_passant_index_=99;
	}
}

void Board::block_castling(const Move move, bool isQueenTower){

	if (move.movingPiece().type() == 'K')
	{
		specialRulesData_[1]='-';
		specialRulesData_[2]='-';
	}
	
	if (move.movingPiece().type() == 'k')
	{
		specialRulesData_[3]='-';
		specialRulesData_[4]='-';
	}
	

	
	if (move.movingPiece().type() == 'R')
	{
		if (not isQueenTower){specialRulesData_[1]='-';}
		if (isQueenTower){specialRulesData_[2]='-';}
	}
	
	if (move.movingPiece().type() == 'r')
	{
		if (not isQueenTower){specialRulesData_[3]='-';}
		if (isQueenTower){specialRulesData_[4]='-';}
	}

}
// Utility function to convert index to coordinate
char* Board::indextoCoord(const int &index) {
    char* coord = new char[3];
    const char* ref = "abcdefgh";
    int row = 8 - (index / 8);
    char column = ref[index % 8];
    
    coord[0] = column;
    coord[1] = '0' + row; // conversion in char
    coord[2] = '\0';
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
    return index;
}

// Utility function to play a move
Board Board::withMove(const Move move) {
	int startIndex = Board::coordtoIndex(move.start());
	int endIndex = Board::coordtoIndex(move.end());
	
	char newFEN[64];
	memcpy(&newFEN, &FEN_, 64 * sizeof(char));
	newFEN[startIndex] = '.';
	newFEN[endIndex] = FEN_[startIndex];
	
	// En passant : We must erase the captured pawn
	if (move.isEnPassant())
	{
		int captured_pawn_index = 0;

		if (move.movingPiece().isWhite()){captured_pawn_index = en_passant_index_ + 8;}
		if (not move.movingPiece().isWhite()){captured_pawn_index = en_passant_index_ - 8;}
		
		newFEN[captured_pawn_index]='.';
	}
	
	// Castling : We must also move the tower
	if (move.isCastling())
	{	
		int past_tower_index = 99;
		int new_tower_index = 99;
		char tower_type = 'R';
		
		if (not move.movingPiece().isWhite()) {tower_type = 'r';}
		if (move.end()[0] == 'g')
		{
			past_tower_index = endIndex + 1;
			new_tower_index = endIndex - 1;
		}
		
		if (move.end()[0] =='c')
		{
			past_tower_index = endIndex - 2;
			new_tower_index = endIndex+ 1;
		}
		
		newFEN[past_tower_index] = '.';
		newFEN[new_tower_index] = tower_type;
	}

	// Promotion : we must replace the pawn
	if (move.isPromotion())
	{	
		newFEN[endIndex] = move.movingPiece().isWhite() ? 'Q' : 'q';
	
	}
	Board *newBoard = new Board(newFEN);
	
    return *newBoard;
}

// Utility function to convert FEN string to pieces
Piece* Board::FENtoPieces(const char* _FEN) {
	Piece *p = new Piece[64]; 
	for(int i = 0; i < 64; i++) {
		if(_FEN[i] != '.') {
			char* temp_coord = Board::indextoCoord(i); //Create
			p[i] = Piece(_FEN[i], temp_coord, (bool)std::isupper(_FEN[i]));
			//delete[] temp_coord; //Delete
		}
	}
    return p;
}

// Utility function to convert pieces to FEN string
char* Board::PiecestoFEN(const Piece* _pieces) {
	char *newFEN = new char[64];
	for(int i = 0; i < 64; i++) {
			newFEN[i] = _pieces[i].type();
	}
    return newFEN;
}

// Utility function to check some infos on the board
bool Board::is_piece_on_square(int index_arrival){
	return (FEN_[index_arrival] != '.');
}

bool Board::is_white_on_square(int index_arrival){

	if (is_piece_on_square(index_arrival) && isupper(FEN_[index_arrival])){
		return true;
	}
	
	return false;
}

// Utility function around move
const char* Board::create_msg(const char* departure_coord, const char* arrival_coord){

	char* fictive_msg =  new char[4];
        strncpy(fictive_msg, departure_coord, 2);
        strncpy(fictive_msg + 2, arrival_coord, 2);
	
	return fictive_msg;
}

Move Board::create_move(const char* msg){
	//Create move
	char start[3];
	char end[3];	
	strncpy(start, msg, 2);
	strncpy(end, msg+2, 2);
	start[2] = '\0';
	end[2] = '\0';


	if (isValidCoord(start, end)) 
	{
		int startIndex = coordtoIndex(start);
		Piece piece = pieces_[startIndex];

		bool _is_capturing = Board::is_piece_capturing(start, end, piece);
		bool _is_castling = Board::is_piece_castling(start, end, piece);
		bool _is_en_passant = Board::is_piece_taking_en_passant(end, piece);
		bool _is_promotioning = Board::is_piece_promotioning(end, piece);

		return Move(start, end, piece, _is_capturing, _is_promotioning, _is_castling, _is_en_passant);
	} 
	
	else
	{
		std::cout << "Illegal Move : "<<start<<" "<<end<<" is a bad coord" << std::endl;
		return Move();
	}

		
}


void Board::playMove(Move move) {

	// Create the new board
	Board newBoard = withMove(move);	
	char* opponent_king_coord = indextoCoord(newBoard.find_king(not is_playing_player_white())); //Create
	
	// Is there check or checkmate
	if (newBoard.isCheck(not is_playing_player_white(),opponent_king_coord))
	{
		std::cout<<"Echec"<<std::endl;
		
		if (newBoard.isCheckmate(not is_playing_player_white()))
		{
			std::cout<<"Echec et mat !"<<std::endl;
		}
	}

	// Change special rules
	Board::change_special_rules_after_move(move);
	
	// Change actual FEN and array of pieces
	memcpy(&FEN_, &(newBoard.FEN_), 64 * sizeof(char));
	pieces_ = newBoard.pieces_;


	delete[] opponent_king_coord;

}



void Board::change_special_rules_after_move(Move move){
	//Change special rules after move
	
	//CHANGE TURN
	Board::change_turn();
	
	//CASTLING if the piece is a king or a rook
		if (move.movingPiece().type() == 'K' || move.movingPiece().type() == 'k'){
			Board::block_castling(move,false);
		}
		
		if (move.movingPiece().type() == 'r' || move.movingPiece().type() == 'R'){
			if ( strcmp(move.start(),"a1") == 0 || strcmp(move.start(),"a8") == 0)
			{
				Board::block_castling(move,true);
			}
			
			if ( strcmp(move.start(),"h1") == 0 || strcmp(move.start(),"h8") == 0)
			{
				Board::block_castling(move,false);
			}

		}
	
	//EN PASSANT if the piece is a pawn which has moved 2 rows
	int departure_row=move.start()[1] - '0';
	int arrival_row=move.end()[1] - '0';
	int row_gap = std::abs(departure_row - arrival_row);
	
	if ( (move.movingPiece().type() == 'p' || move.movingPiece().type() == 'P') && (row_gap==2) )
	{
		Board::change_en_passant_square(true,move.movingPiece().isWhite(),move.end());
	}
	
	else 
	{
		Board::change_en_passant_square(false,move.movingPiece().isWhite(),move.end());
	}

}


// Utility functions to create the object Move
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

bool Board::is_piece_capturing(const char* start, const char* end, Piece piece){
	//Check if a move correspond to a capture
	int arrival_index = Board::coordtoIndex(end);
	
	if (Board::is_piece_on_square(arrival_index))
	{
	
		bool isPieceOnArrivalWhite = pieces_[Board::coordtoIndex(end)].isWhite();
		if (isPieceOnArrivalWhite != piece.isWhite())
		{
			return true;
		}
	}
	return false;

}

bool Board::is_piece_castling(const char* start, const char* end, Piece piece){
	//Check if a move correspond to a castlening
	if (piece.type() == 'K')
	{
		
		if ( (strcmp(start,"e1") == 0 && strcmp(end,"c1") == 0)
		  || (strcmp(start,"e1") == 0 && strcmp(end,"g1") == 0) )
		  
		  {
		  	std::cout << "Roque valide" << std::endl;
		  	return true;
		  }
	}
	
	
	if (piece.type() == 'k')
	{
		
		if ( (strcmp(start,"e8") == 0 && strcmp(end,"c8") == 0)
		  || (strcmp(start,"e8") == 0 && strcmp(end,"g8") == 0) )
		  
		  {
		  	return true;
		  }
	}
	
	return false;
}

bool Board::is_piece_taking_en_passant(const char* coord_end, Piece piece){
	//Check if a move correspond to a En passant move
	
	if (piece.type() == 'p' || piece.type() == 'P')
	{
		int end_index = coordtoIndex(coord_end);
		
		if (end_index == en_passant_index_)
		{
			return true;
		}
	
	}
	
	return false;
}

bool Board::is_piece_promotioning(const char* coord_end, Piece piece){

	int final_row = piece.isWhite() ? 8 : 1;
	return (piece.type() == 'p' || piece.type() == 'P') && (coord_end[1] - '0' == final_row);	

	
}
//Functions to check if a move is legal
bool Board::isLegal(const Move move) {


	Board board_after_move = withMove(move); 
	
	// If at the end of the move, the king is checked, the move is mandatory illegal
	int kingIndex = board_after_move.find_king(move.movingPiece().isWhite());	
	char* kingCoord = indextoCoord(kingIndex);
	
	//Whatever happens, if at the end of the move, player is checked, the move is illegal
	if(board_after_move.isCheck(move.movingPiece().isWhite(), kingCoord)) 
	{

		delete[] kingCoord; //delete inside if 
		return false;
	}
	
	delete[] kingCoord; //delete outside if 

	
	// Special En Passant move
	if (move.isEnPassant())
	{
	
		if (is_en_passant_valid(move))
		{
			return true;
		}
	
	}
	
	// Special Castling move
	if (move.isCastling())
	{
		if (is_castling_valid(move))
		{
			return true;
		}
	}
	
	// Classic move
	if(is_piece_correctly_moving(move))
	{

		if(not is_there_obstacle_on_way(move))
		{

			if(not is_there_obstacle_on_arrival(move))
			{

					return true;
			}
		}
	}

	return false;
}


bool Board::is_piece_correctly_moving(const Move move){
	// Get infos from move
	char departure_column=move.start()[0];
	char arrival_column=move.end()[0];
	int departure_row=move.start()[1] - '0';
	int arrival_row=move.end()[1] - '0';

	
	if (move.movingPiece().type()=='r' 
	 || move.movingPiece().type()=='R' 
	 || move.movingPiece().type()=='q' 
	 || move.movingPiece().type()=='Q')
	{
		//Rook/Queen must have a move along a column or a row	
		if (departure_column == arrival_column || departure_row == arrival_row){
			return true;
		}
	}
		
	if (move.movingPiece().type()=='b' 
	 || move.movingPiece().type()=='B' 
	 || move.movingPiece().type()=='q' 
	 || move.movingPiece().type()=='Q')
	{
		//Bishop/Queen must increase row and column the same way
		int gap_row = std::abs(arrival_row-departure_row);
		int gap_column = std::abs(arrival_column - departure_column);

		if (gap_row == gap_column){
			return true;
		}
	}
		
	if (move.movingPiece().type()=='k' || move.movingPiece().type()=='K'){
		//King can only change its row/column by 1
		
		int row_gap=std::abs(departure_row-arrival_row);
		char column_gap=std::abs(departure_column-arrival_column);
		
		if (row_gap>1){return false;}
		if (column_gap>1){return false;}
		
		return true;
	}
	
	if (move.movingPiece().type()=='p' || move.movingPiece().type()=='P'){
		//Pawn can only move 1 row depending on its color or 2 if it is on its starting place
		int row_gap=arrival_row-departure_row;
		int column_gap=arrival_column-departure_column;
		bool isMovingUp = row_gap>0;
		bool isOnStartingRow = false;
		
		//Check if pawn moves toward good direction
		bool isMovingGoodDirection = (move.movingPiece().isWhite() == isMovingUp); 

		//Check if on starting row
		if ( (move.movingPiece().isWhite() && departure_row==2) 
		 || (not move.movingPiece().isWhite() && departure_row==7) ){
		 
		 	isOnStartingRow = true;
		 } 


		if (isMovingGoodDirection){
			if (column_gap==0 && not move.isCapture()){

				if (std::abs(row_gap)==1){
					return true;
				}

				if (std::abs(row_gap)==2 && isOnStartingRow){
					return true;
				}
			}

			if (std::abs(column_gap)==1 && std::abs(row_gap)==1 && move.isCapture()){
				return true;
				
			}
		}

		
	}
	
	if (move.movingPiece().type()=='n' || move.movingPiece().type()=='N'){
		//Knight can only move on 8 squares easily seen with the FEN
		
		int startIndex = Board::coordtoIndex(move.start());
		int endIndex = Board::coordtoIndex(move.end());
		
		int FEN_gap=std::abs(startIndex-endIndex);
		
		if (FEN_gap==6 || FEN_gap==10 || FEN_gap==15 || FEN_gap==17){
			return true;
		}
	
	}
	
	return false;
}


int* Board::trajectory(const Move move){
	
	int* trajectory_squares = new int[8];
	
	for (int i=0 ; i<8 ; i++){trajectory_squares[i]=99;}
	
	// Get infos from move
	char start_col=move.start()[0];
	char end_col=move.end()[0];
	char start_row=move.start()[1];
	char end_row=move.end()[1];
	char coord_considered[2];
	
	
	// Rook/Queen case
	if ((end_row == start_row) || (end_col == start_col)) 
	{
	if (move.movingPiece().type()=='r' 
	 || move.movingPiece().type()=='R' 
	 || move.movingPiece().type()=='q' 
	 || move.movingPiece().type()=='Q'){
	 
	 	if (end_row == start_row) //Move along a row
	 	{	 	
	 		coord_considered[1]=start_row;
	 		int gap = std::abs(end_col-start_col);
	 		int direction = (end_col-start_col)/gap; //Positive toward right, negative toward left
	 		
	 		for (int i=1 ; i<gap ; i++)
	 		{
	 			coord_considered[0] = start_col + i * direction; //Check squares on the left or right depending on direction
	 			int index_considered = coordtoIndex(coord_considered);
	 			trajectory_squares[i-1] = index_considered;
	 		}
	 		trajectory_squares[gap]=99;
	 	}
	 	
	 	else if (end_col == start_col) //Move along a column
	 	{
	 		coord_considered[0] = start_col;
	 		int gap = std::abs(end_row-start_row);
	 		int direction = (end_row - start_row)/gap; //Positive toward up, negative toward down
	 		
	 		for (int i=1 ; i<gap ; i++)
	 		{
	 			coord_considered[1]=start_row + i*direction; //Check squares on the up or down depending on direction
	 			int index_considered = coordtoIndex(coord_considered);
	 			trajectory_squares[i-1] = index_considered;
	 		}
	 	

	 	}

	 	return trajectory_squares;
	 	
	 }
	 }
	 	
	 // Bishop/Queen case
	 if (move.movingPiece().type() == 'b' 
	  || move.movingPiece().type() == 'B' 
	  || move.movingPiece().type() == 'q' 
	  || move.movingPiece().type() == 'Q'){

	 	int gap = std::abs(end_row - start_row);
	 	int direction_row = (end_row - start_row)/gap;
	 	int direction_col = (end_col - start_col)/gap;
	 	
	 	for (int i=1 ; i<gap ; i++)
	 	{
	 		coord_considered[0] = start_col + i * direction_col;
	 		coord_considered[1] = start_row + i * direction_row;
	 		int index_considered=coordtoIndex(coord_considered);
	 		trajectory_squares[i-1] = index_considered;
	 	}
	 	trajectory_squares[gap]=99;	

	 	return trajectory_squares;
	 }
	 
	 // Pawn case
	 if (move.movingPiece().type()=='p' || move.movingPiece().type()=='P'){
	 
	 	int gap = std::abs(end_row - start_row);
	 	int direction = (end_row - start_row)/gap;
	 	
	 	if (gap==2)
	 	{
	 		coord_considered[0] = start_col;
	 		coord_considered[1] = start_row + direction;
	 		int index_considered=coordtoIndex(coord_considered);
	 		
	 		trajectory_squares[0] = index_considered;
	 	}
	 	trajectory_squares[gap]=99;
	 }

	 return trajectory_squares;
}

bool Board::is_there_obstacle_on_way(const Move move){
	//Return true if there is a piece able to block the move of the piece on its way.
	//This function does NOT check the case of a piece ON the arrival square, another function is in charge of this


	int* squares_visited = trajectory(move); //create
	int i = 0;

	
	while (squares_visited[i] != 99)
	{
		if (is_piece_on_square(squares_visited[i++]))
		{

			delete[] squares_visited; //delete inside if 
			return true;
		}
	}
	

	delete[] squares_visited; //delete outside if 

	return false;
}


bool Board::is_there_obstacle_on_arrival(const Move move){
	//Return true if a piece of the same color is on the arrival square
	
	char PieceOnArrival = pieces_[Board::coordtoIndex(move.end())].type();
	
	if (PieceOnArrival == '.'){return false;}
	
	bool isPieceOnArrivalWhite = pieces_[Board::coordtoIndex(move.end())].isWhite();

	
	if (isPieceOnArrivalWhite == move.movingPiece().isWhite()){
		return true;
	}
	
	return false;
	
}
// Game logic to do a castling, a  special movement non respecting rules of isLegal
bool Board::is_castling_valid(const Move move){
	

	std::cout<<"Les règles spéciales sont "<<specialRulesData_<<std::endl;
	if ( (strcmp(move.end(),"g1") == 0 && specialRulesData_[1]=='K') 
	  || (strcmp(move.end(),"c1") == 0 && specialRulesData_[2]=='Q')
	  || (strcmp(move.end(),"g8") == 0 && specialRulesData_[3]=='k')
	  || (strcmp(move.end(),"c8") == 0 && specialRulesData_[4]=='q') )
	  
	
		{

			int king_start_index = coordtoIndex(move.start());
			int king_end_index = coordtoIndex(move.end());
			
			
			int gap = std::abs(king_start_index - king_end_index);
			int direction = (king_end_index - king_start_index)/gap;
			
			//Check if king is check
			if (isCheck(move.movingPiece().isWhite(), move.start()))
			{
				return false;
			}
			
			// For each square crossed by the king during the castling
			for (int i = 1 ; i<=gap ; i++)
			{
				int king_new_index = king_start_index + i * direction;
				
				
				// Check if the square is empty
				if (is_piece_on_square(king_new_index))
				{
					return false;
				}
				
				// Check if the square is controled by an opponent
				
				char* king_new_coord = indextoCoord(king_new_index); //create
				Move move_king_castling(move.start(),king_new_coord,move.movingPiece(),false,false,false,false);
					
				Board Board_during_castling = withMove(move_king_castling);
				
				if (Board_during_castling.isCheck(move.movingPiece().isWhite(), king_new_coord))
				{

					delete[] king_new_coord; //delete inside if 

					return false;
				}
				
				delete[] king_new_coord; //delete outside if	
			}

			return true;
		}
	
	return false;
}

bool Board::is_en_passant_valid(const Move move){
	//To check if the en passant is correct, we can use the function is_piece_correctly_moving with the given move but with a isCapture true.

	Move en_passant_move(move.start(), move.end(), move.movingPiece(), true, false, false,true);
	return Board::is_piece_correctly_moving(en_passant_move);
}

// Game logic to check if there is a check on the king POV


bool Board::isCheck(const bool isKingWhite, const char* square_to_verify) {
		
		Piece* list_checking_piece = find_checking_pieces(isKingWhite, square_to_verify); //create
		
		if (list_checking_piece[0].type() != '.')
		{
			delete[] list_checking_piece; //delete inside if
			return true;
		}
	
	delete[] list_checking_piece; //delete outside if
	
	return false;
}


bool Board::isCheckmate(const bool isWhite){
	
	int king_index = find_king(isWhite);
	Piece king = pieces_[king_index];
	Piece* checking_piece_list = find_checking_pieces(isWhite, king.coord()); //create
	
/*
 Has to consider 3 things :
	1- if the squares accessible to the checked king is controlled by an ennemy piece
	2- if ALL the ally pieces cannot capture the checking piece by going on its square
	3- if ALL the ally pieces cannot go on the trajectory of the checking piece

NOTE : If there is more than 1 checking piece, moving the king is mandatory to avoid checkmate : only checking condition 1- is enough */

// 1- Can the king move ?

	for (int i = -1 ; i<2 ; i++)
	{
		for (int j = -1 ; j<2 ; j++)
		{
			char* king_new_coord = new char[2];
			king_new_coord[0] = king.coord()[0] + i;
			king_new_coord[1] = king.coord()[1] + j;
			
			if (isValidCoord(king.coord(),king_new_coord))
			{
				const char* temp_msg = create_msg(king.coord(),king_new_coord); //create
				char fictive_escaping_msg[4];
				strncpy( fictive_escaping_msg ,temp_msg , 4);
				Move move_king_escaping = create_move(fictive_escaping_msg);
				
				delete[] temp_msg; //delete
				
				if (isLegal(move_king_escaping))
				{
					return false;
				}				
			
			}
		}
	
	}
	
	
	//If there is more than 1 checking piece ? not being able to move the king means checkmate
	if (checking_piece_list[1].type() != '.')
	{
		delete[] checking_piece_list; //delete inside if
		std::cout<<"Echec à la découverte"<<std::endl;
		return true;
	}
	
	Piece checking_piece = checking_piece_list[0];
	delete[] checking_piece_list; //delete outside if;
	
// 2-Can an ally capture the checking piece ?

	for (int i = 0 ; i<64 ; i++)
	{
		Piece actual_piece = pieces_[i];
		
		if (	   actual_piece.type() != '.' 
			&& actual_piece.type() != 'k' 
			&& actual_piece.type() != 'K' 
			&& actual_piece.isWhite() == isWhite)
			
		{
		
			const char* temp_msg = create_msg(actual_piece.coord(),checking_piece.coord()); //create
			char fictive_attacking_msg[4];     		
        		strncpy( fictive_attacking_msg , temp_msg, 4);  			
        		Move fictive_attacking_move = create_move(fictive_attacking_msg);

			delete[] temp_msg; //delete
			
        		if (isLegal(fictive_attacking_move))
        		{
        			return false;
       			}	
		}
	
	}
	
	
	
// 3- Can an ally go on the trajectory of the checking piece ?
	
	const char* temp_msg = create_msg(checking_piece.coord(),king.coord()); //create
	char fictive_checking_msg[4];
	strncpy(fictive_checking_msg, temp_msg , 4);  				
	Move checking_move = create_move(fictive_checking_msg);
	
	delete[] temp_msg;
	int* attacking_trajectory = trajectory(checking_move); //create
	
	for (int j= 0 ; j<8 ; j++)
	{

		if (attacking_trajectory[j] != 99)
		{
			char* square_on_trajectory = indextoCoord(attacking_trajectory[j]);//create
			
			for (int i = 0 ; i<64 ; i++)
			{
				Piece actual_piece = pieces_[i];

				if (actual_piece.type() != '.' && actual_piece.isWhite() == isWhite)
				{
					
					const char* temp_msg_2 = create_msg(actual_piece.coord(),square_on_trajectory); //create
					char fictive_blocking_msg[4];
					strncpy( fictive_blocking_msg , temp_msg_2, 4);
					delete[] temp_msg_2; //delete
					delete[] square_on_trajectory; //delete inside if
					
					Move fictive_blocking_move = create_move(fictive_blocking_msg);	
					
					if (isLegal(fictive_blocking_move))
					{
						delete[] attacking_trajectory; //delete inside if
						return false;
					}	
				}
				
			}
			
			delete[] square_on_trajectory; //delete outside if
			
		}
	}
	
	delete[] attacking_trajectory; //delete outside if


// Finally, if there is no working option

	return true;
}

int Board::find_king(const bool isKingWhite){  // Return the index of the white or black king

	for (int i = 0 ; i<64 ; i++)
	{
		Piece verified_piece = pieces_[i];
		
		if (verified_piece.type() == 'k' || verified_piece.type() == 'K')
		{
			if (verified_piece.isWhite() == isKingWhite)
			{
				return i;
			}
		}

	}

	return 99;
}

Piece* Board::find_checking_pieces(const bool isKingWhite, const char* square_to_verify){

	Piece* checking_pieces = new Piece[2];
	
	int j = 0;
	for(int i=0; i<64; i++) 
	{

    		Piece piece = pieces_[i];
    		if (piece.isWhite() != isKingWhite && piece.type()!='.')
    		{
    			
        		
        		const char* temp_msg = create_msg(piece.coord(),square_to_verify); //create
				char fictive_msg[4];
				strncpy( fictive_msg , temp_msg, 4);
				
				delete[] temp_msg; //delete
        			
        		Move attacking_move = create_move(fictive_msg);
        		attacking_move.set_isCapture(true);

        		if (is_piece_correctly_moving(attacking_move) && not is_there_obstacle_on_way(attacking_move)) 
        		{
        			checking_pieces[j] = piece;
            		j++;
       			}	
    		}
	
	}
	
return checking_pieces;
	
}


void Board::print(){
	std::cout << "------------------" << std::endl;
	for (int i = 0; i<64;i++){
		std::cout << FEN_[i] << ' ';
		if ((i+1) % 8 == 0 && i != 0) {
			std::cout << std::endl;
		}
	}
	std::cout << "------------------" << std::endl;
}





