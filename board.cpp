#include "board.h"
#include "move.h"
#include <iostream>
#include <cstring>
#include <cctype>
#include <sstream>
#include <cassert>
#include <cmath>


// Board Constructor
Board::Board() {
	std::string startFEN = "rnbqkbnrpppppppp................................PPPPPPPPRNBQKBNR";
	std::string start_valhalla_FEN = "QRBN...............qrbn...............";
	FEN_ = startFEN;
	valhalla_FEN_ = start_valhalla_FEN;
	specialRulesData_ = "wKQkq";
	en_passant_index_= 99;
	pieces_ = FENtoPieces(FEN_);
	valhalla_pieces_ = valhallaFENtoPieces(valhalla_FEN_);
	end_game_ = 'o';
	
}


// Board Constructor with FEN parameter
Board::Board(std::string _FEN) {
	FEN_ = _FEN;
	pieces_ = FENtoPieces(FEN_);
	std::string start_valhalla_FEN = "QRBN...............qrbn...............";
	valhalla_FEN_ = start_valhalla_FEN;
	specialRulesData_ = "wKQkq";
	en_passant_index_= 99;
	valhalla_pieces_ = valhallaFENtoPieces(valhalla_FEN_);
	end_game_ = 'o';
}

Board::Board(std::string _FEN, std::string _Valhalla_FEN) {
	FEN_ = _FEN;
	pieces_ = FENtoPieces(FEN_);
	std::string start_valhalla_FEN = _Valhalla_FEN;
	valhalla_FEN_ = start_valhalla_FEN;
	specialRulesData_ = "wKQkq";
	en_passant_index_= 99;
	valhalla_pieces_ = valhallaFENtoPieces(valhalla_FEN_);
	end_game_ = 'o';
}

Board::Board(std::string _FEN, int en_passant_index) {
	FEN_ = _FEN;
	pieces_ = FENtoPieces(FEN_);
	std::string start_valhalla_FEN = "QRBN...............qrbn...............";
	valhalla_FEN_ = start_valhalla_FEN;
	specialRulesData_ = "wKQkq";
	en_passant_index_= en_passant_index;
	valhalla_pieces_ = valhallaFENtoPieces(valhalla_FEN_);
	end_game_ = 'o';
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

void Board::change_en_passant_square(bool has_a_pawn_moved, bool is_pawn_white, std::string end_coord){
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
std::string Board::indextoCoord(const int &index) {
    std::string coord(2, ' ');
    std::string ref = "abcdefgh";
    int row = 8 - (index / 8);
    char column = ref[index % 8];
    
    coord[0] = column;
    coord[1] = '0' + row; // conversion in char
    return coord;
}

// Utility function to convert coordinate to index
int Board::coordtoIndex(std::string coord) {
    char column = coord[0]; //"a4" -> "a"
    int row = coord[1] - '0'; //"a4" -> 4
    int columnNb = 0;
    std::string ref = "abcdefgh";
    for(int i = 0; i < 8; i++){
    	if (column == ref[i]){
    		columnNb = i; // a = 0, h = 7
    		break; 
    	}
    }
    int index = (8-row) * 8 + columnNb;
    return index;
}


// Utility function to convert FEN string to pieces
Piece* Board::FENtoPieces(std::string _FEN) {
	Piece *p = new Piece[64]; 
	for(int i = 0; i < 64; i++) {
		if(_FEN[i] != '.') {
			std::string temp_coord = Board::indextoCoord(i);
			p[i] = Piece(_FEN[i], temp_coord, (bool)std::isupper(_FEN[i]));
			
		}
	}
    return p;
}

// Utility function to convert pieces to FEN string
std::string Board::PiecestoFEN(const Piece* _pieces) {
	std::string newFEN(64, ' ');
	for(int i = 0; i < 64; i++) {
			newFEN[i] = _pieces[i].type();
	}
    return newFEN;
}

// Utility function to check some infos on the board
bool Board::is_piece_on_square(int index_arrival){
	return (FEN_[index_arrival] != '.');
}

Piece Board::piece_on_square(std::string coord){
	if (coord[0] == 'v' || coord[0] == 'V'){
		return valhalla_pieces_[valhalla_coord_to_index(coord)];
	}
	return pieces_[coordtoIndex(coord)];
}

bool Board::is_white_on_square(int index_arrival){

	if (is_piece_on_square(index_arrival) && isupper(FEN_[index_arrival])){
		return true;
	}
	
	return false;
}

// Utility function to arbitrary change the board

void Board::modify_piece(std::string coord, char piece_type){
	if (coord[0] == 'v' || coord[0] == 'V')
	{
		int index = valhalla_coord_to_index(coord);
		valhalla_FEN_[index] = piece_type;
	}

	else
	{
		int index = coordtoIndex(coord);
		FEN_[index] = piece_type;
	}
	
}
// Utility function around move
std::string Board::create_msg(std::string departure_coord, std::string arrival_coord){

	std::string fictive_msg = departure_coord + arrival_coord;
	if(fictive_msg.length() != 4) {
		std::cout << "Error create_msg : msg:<" << fictive_msg << ">" <<std::endl;
	}
	return fictive_msg;
}

Move Board::create_move(std::string msg){
	//Create move
	if(msg.length() != 4) {
		std::cout << "Erreur create_move : msg:" << msg <<std::endl;
		return Move();
	}
	std::string start = msg.substr(0, 2) ;
	std::string end = msg.substr(2, 2);	

	if (isValidCoord(start, end)) 
	{
		int startIndex = coordtoIndex(start);
		Piece piece = pieces_[startIndex];

		bool _is_capturing = Board::is_piece_capturing(start, end, piece);
		bool _is_castling = Board::is_piece_castling(start, end, piece);
		bool _is_en_passant = Board::is_piece_taking_en_passant(end, piece);
		bool _is_promoting = Board::is_piece_promoting(end, piece);

		return Move(start, end, piece, _is_capturing, _is_promoting, _is_castling, _is_en_passant);
	} 
	
	else
	{
		//std::cout << "Illegal Move : "<<start<<" "<<end<<" is a bad move" << std::endl;
		return Move();
	}

		
}

// Utilisty function to play a move
void Board::playMove(Move move, char promotion_piece) {

	// Create the new board
	Board newBoard = withMove(move, promotion_piece);

	std::string opponent_king_coord = indextoCoord(newBoard.find_king(not is_playing_player_white())); //Create
	//std::cout << "Opponent king is on square " << opponent_king_coord <<std::endl;
	
	// Is there check or checkmate
	if (newBoard.isCheck(not is_playing_player_white(),opponent_king_coord))
	{
		std::cout<<"Echec"<<std::endl;
		
		if (newBoard.isCheckmate(not is_playing_player_white()))
		{
			//std::cout<<"Echec et mat !"<<std::endl;
			end_game_ = is_playing_player_white() ? 'b' : 'w';
		}
	}

	if(newBoard.isPat(not is_playing_player_white())){
		//std::cout << "Pat !" << std::endl;
		end_game_ = 'p';
	}
	
	//Send pieces to 
	send_to_valhalla (move);
	valhalla_pieces_ = valhallaFENtoPieces(valhalla_FEN_);

	// Change special rules
	Board::change_special_rules_after_move(move);
	
	// Change actual FEN and array of pieces
	FEN_ = newBoard.FEN_;
	pieces_ = newBoard.pieces_;
	

}

// Utility function to manage things that happened thanks to a specific move
Board Board::withMove(const Move move, char promotion_piece) {
	int startIndex = Board::coordtoIndex(move.start());
	int endIndex = Board::coordtoIndex(move.end());
	
	std::string newFEN = FEN_;
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

	// Promotion
	if (move.isPromotion())
	{
		if (promotion_piece != '.')
		{
			newFEN[endIndex] = promotion_piece;
		}
	}
	
	// Create new board
	Board *newBoard = new Board(newFEN);
	
	
    return *newBoard;
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
			if (move.start() == "a1"|| move.start() == "a8")
			{
				Board::block_castling(move,true);
			}
			
			if (move.start() == "h1" || move.start() == "h8")
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
bool Board::isValidCoord(std::string _start, std::string _end) {
    if (_start.length() != 2 || _end.length() != 2) {
    	std::cout << "Erreur: isValidCoord"<< std::endl;
    	std::cout << "str1:<" << _start.length() << "> str2:<" << _end << ">" << std::endl;
        return false;
    }
	char departure_column =_start[0];
	char arrival_column =_end[0];
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

bool Board::is_piece_capturing(std::string start, std::string end, Piece piece){
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

bool Board::is_piece_castling(std::string start, std::string end, Piece piece){
	//Check if a move correspond to a castling
    if (piece.type() == 'K')
    {
        if ((start == "e1" && end == "c1") || (start == "e1" && end == "g1"))
        {
            //std::cout << "Roque valide" << std::endl;
            return true;
        }
    }

    if (piece.type() == 'k')
    {
        if ((start == "e8" && end == "c8") || (start == "e8" && end == "g8"))
        {
            return true;
        }
    }

    return false;
}


bool Board::is_piece_taking_en_passant(std::string coord_end, Piece piece){
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

bool Board::is_piece_promoting(std::string coord_end, Piece piece){

	int final_row = piece.isWhite() ? 8 : 1;
	return (piece.type() == 'p' || piece.type() == 'P') && (coord_end[1] - '0' == final_row);	

	
}
//Functions to check if a move is legal
bool Board::isLegal(const Move move) {


	Board board_after_move = withMove(move); 
	
	// If at the end of the move, the king is checked, the move is mandatory illegal
	
	int kingIndex = board_after_move.find_king(move.movingPiece().isWhite());	
	if (kingIndex == 99){
		std::cout << "Error with move <" << move.start() << move.end() << ">" << std::endl;
	}
	std::string kingCoord = indextoCoord(kingIndex);
	
	//Whatever happens, if at the end of the move, player is checked, the move is illegal
	if(board_after_move.isCheck(move.movingPiece().isWhite(), kingCoord)) 
	{
		return false;
	}


	
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
		
		int gap_row = std::abs(arrival_row-departure_row);
		int gap_column = std::abs(arrival_column - departure_column);

		if ((gap_row == 2 && gap_column == 1) || (gap_row == 1 && gap_column == 2)){
			return true;
		}
	
	}
	
	return false;
}


int* Board::trajectory(const Move move){
	
	int* trajectory_squares = new int[8];
	
	for (int i=0 ; i<8 ; i++){trajectory_squares[i]=99;}
	
	// Get infos from move
	char start_col = move.start()[0];
	char end_col = move.end()[0];
	char start_row = move.start()[1];
	char end_row = move.end()[1];
	std::string coord_considered(2, ' ');
	
	
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

	//std::cout << "+1" << std::endl;
	int* squares_visited = trajectory(move); //create
	int i = 0;

	
	while (squares_visited[i] != 99)
	{
		if (is_piece_on_square(squares_visited[i++]))
		{

			//std::cout << "-1" << std::endl;
			delete[] squares_visited; //delete inside if 
			return true;
		}
	}
	
	//std::cout << "-1*" << std::endl;
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
	

	if ((move.end() == "g1" && specialRulesData_[1] == 'K') 
		|| (move.end() == "c1" && specialRulesData_[2] == 'Q') 
		|| (move.end() == "g8" && specialRulesData_[3] == 'k') 
		|| (move.end() == "c8" && specialRulesData_[4] == 'q'))

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
				
				std::string king_new_coord = indextoCoord(king_new_index); //create
				Move move_king_castling(move.start(),king_new_coord,move.movingPiece(),false,false,false,false);
					
				Board Board_during_castling = withMove(move_king_castling);
		
				if (Board_during_castling.isCheck(move.movingPiece().isWhite(), king_new_coord))
				{

					

					return false;
				}
				
				
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


bool Board::isCheck(const bool isKingWhite, std::string square_to_verify) {
		
		
		Piece* list_checking_piece = find_checking_pieces(isKingWhite, square_to_verify); //create
		//std::cout << "+2" << std::endl;

		
		if (list_checking_piece[0].type() != '.')
		{
			//std::cout << "King checked by " << list_checking_piece[0].type() << std::endl;
			//std::cout << "-2" << std::endl;
			delete[] list_checking_piece; //delete inside if
			return true;
		}
	
	//std::cout << "-2*" << std::endl;
	delete[] list_checking_piece; //delete outside if
	
	return false;
}


bool Board::isCheckmate(const bool isWhite){
	int king_index = find_king(isWhite);
	Piece king = pieces_[king_index];
	//std::cout << "+3" << std::endl;
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
			std::string king_new_coord(2, ' ');
			king_new_coord[0] = king.coord()[0] + i;
			king_new_coord[1] = king.coord()[1] + j;
			
			if (isValidCoord(king.coord(),king_new_coord))
			{
				std::string fictive_escaping_msg = create_msg(king.coord(),king_new_coord); //create
				Move move_king_escaping = create_move(fictive_escaping_msg);
				
				
				
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
		//std::cout << "-3" << std::endl;
		delete[] checking_piece_list; //delete inside if
		std::cout<<"Echec à la découverte"<<std::endl;
		return true;
	}
	
	Piece checking_piece = checking_piece_list[0];
	//std::cout << "-3*" << std::endl;
	delete[] checking_piece_list; //delete outside if;
	
// 2-Can an ally capture the checking piece ?

	for (int i = 0 ; i<64 ; i++)
	{
		Piece actual_piece = pieces_[i];
		
		if (   actual_piece.type() != '.' 
			&& actual_piece.type() != 'k' 
			&& actual_piece.type() != 'K' 
			&& actual_piece.isWhite() == isWhite)
			
		{
		
			std::string fictive_attacking_msg = create_msg(actual_piece.coord(),checking_piece.coord()); //create	
			Move fictive_attacking_move = create_move(fictive_attacking_msg);

    		if (isLegal(fictive_attacking_move))
    		{
    			return false;
   			}	
		}
	
	}
	
	
	
// 3- Can an ally go on the trajectory of the checking piece ?
	
	std::string fictive_checking_msg = create_msg(checking_piece.coord(),king.coord()); //create  
	Move checking_move = create_move(fictive_checking_msg);
	
	//std::cout << "+4" << std::endl;
	int* attacking_trajectory = trajectory(checking_move); //create
	
	for (int j= 0 ; j<8 ; j++)
	{

		if (attacking_trajectory[j] != 99)
		{
			std::string square_on_trajectory = indextoCoord(attacking_trajectory[j]);//create
			
			for (int i = 0 ; i<64 ; i++)
			{
				Piece actual_piece = pieces_[i];

				if (actual_piece.type() != '.' && actual_piece.isWhite() == isWhite)
				{
					
					std::string fictive_blocking_msg = create_msg(actual_piece.coord(),square_on_trajectory); //create
					Move fictive_blocking_move = create_move(fictive_blocking_msg);	
					
					if (isLegal(fictive_blocking_move))
					{
						delete[] attacking_trajectory; //delete inside if
						return false;
					}	
				}
			}
		}
	}
	delete[] attacking_trajectory; //delete outside if
	// Finally, if there is no working option

	return true;
}

bool Board::isPat(bool isWhite){
	
	int king_index = find_king(isWhite);	
	if(isCheck(isWhite, indextoCoord(king_index))){return false;}

	for (size_t i = 0; i < 64; i++)
	{
		Piece piece = pieces_[i];
		if (piece.type() != '.' && piece.isWhite() == isWhite) {
			for (size_t j = 0; j < 64; j++)
			{
				if(indextoCoord(j) == piece.coord() 
				   || piece_on_square(indextoCoord(j)).type() == 'k' 
				   || piece_on_square(indextoCoord(j)).type() == 'K') {continue;}

				//std::cout << "start : " << piece.coord() << " end : " << indextoCoord(j) << std::endl;
				Move move = create_move(create_msg(piece.coord(), indextoCoord(j)));
				if(isLegal(move)){return false;}
			}
		}
	}
	return true;	
}

int Board::find_king(const bool isKingWhite){  // Return the index of the white or black king

	for (int i = 0 ; i < 64 ; i++)
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
	std::cout << "Erreur find_king : King not found" <<std::endl;
	return 99;
}

Piece* Board::find_checking_pieces(const bool isKingWhite, std::string square_to_verify){

	Piece* checking_pieces = new Piece[16];
	
	int j = 0;
	for(int i=0; i<64; i++) 
	{
    		Piece piece = pieces_[i];
    		if (piece.isWhite() != isKingWhite && piece.type()!='.')
    		{
        		std::string fictive_msg = create_msg(piece.coord(),square_to_verify); //create
        		Move attacking_move = create_move(fictive_msg);
        		attacking_move.set_isCapture(true);

        		if (is_piece_correctly_moving(attacking_move) && not is_there_obstacle_on_way(attacking_move)) 
        		{
					//std::cout << "suspect : " << j  << " type : " << piece.type() << std::endl;
        			checking_pieces[j] = piece;
            		j++;
       			}	
    		}
	
	}
	
return checking_pieces;
	
}

bool Board::play(std::string m){
	Move move;
	char promotion_piece = '.';

	if (m.length() != 4 && m.length() !=5) {
		std::cout << "Not a length of 4 or 5 characters" << std::endl;
        return false;
    }

	std::string start = m.substr(0, 2) ;
	std::string end = m.substr(2, 2);	

	if (!isValidCoord(start, end)) 
	{
		std::cout << "Error play : " << start << end << " are not valid coordinates" << std::endl;
		return false;
	}

	if (m.length() == 5) 
	{
		if (std::string("pbnrq").find(m[4]) == std::string::npos)
		{
			std::cout << "Error play : " << promotion_piece << " is not a correct promotion (alway use the lower case)" << std::endl;
			return false;
		}

		promotion_piece = (end[1] == '8') ? toupper(m[4]) : tolower(m[4]);
		std::string reduced_m = m.substr(0,4);
		move = create_move(reduced_m);
	}
	else 
	{
		move = create_move(m);
		if (move.isPromotion() && promotion_piece == '.')
		{
			std::cout << "Error play : " << promotion_piece << " is not a correct promotion : indicate the piece after coordinates (ex : b7b8Q)" << std::endl;
			return false;
		}
	}

	if (move.movingPiece().isWhite() != (specialRulesData()[0] == 'w')){
		std::cout << "Error play : Wrong player" << std::endl;
		return false;
	}
	if(!isLegal(move)){
		std::cout << "Error play : Illegal move" << std::endl;
		return false;
	}

	if (move.isPromotion())
	{
		playMove(move, promotion_piece);
	}

	else {playMove(move);}
	print();
	valhalla_print();
	return true;
}


// Valhalla functions

void Board::valhalla_print(){
std::cout<<std::endl;
	std::cout << "------ Valhalla -----" << std::endl;
	std::cout << std::endl;
	
	std::cout << "White losses" << std::endl;
	for (int i=0 ; i<19 ; i++)
	{
	std::cout<<valhalla_FEN_[i];
	}
	std::cout<<std::endl;
	
	std::cout << "Black losses" << std::endl;
	for (size_t j=19 ; j<valhalla_FEN_.length() ; j++)
	{
	std::cout<<valhalla_FEN_[j];
	}
	std::cout<<std::endl;
	std::cout<<std::endl;

	std::cout << "------------------" << std::endl;
}


Piece* Board::valhallaFENtoPieces(std::string _FEN) {
	Piece *p = new Piece[valhalla_FEN_.length()]; 
	for(size_t i = 0; i < valhalla_FEN_.length(); i++) {
		if(_FEN[i] != '.') {
			std::string temp_coord = Board::indextoCoord(i);
			p[i] = Piece(_FEN[i], temp_coord, (bool)std::isupper(_FEN[i]));
			
		}
	}
    return p;
}


std::string Board::valhalla_index_to_coord(const int &index){
	std::string coord(2, ' ');
	std::string ref = "Vv";

	char v_type = ref[index/19];
	char place_number = to_base(index - 19*(index/19) + 1 ,20)[0];
	
	coord[0] = v_type;
	coord[1] = place_number;
	return coord;
}

int Board::valhalla_coord_to_index(std::string v_coord){
	char v_type = v_coord[0];
	int index = from_base(std::string(1,v_coord[1]), 20);
	index--;
	int add = (bool)std::isupper(v_type) ? 0 : 19;
	
	index += add;
	
	return index;

}
void Board::send_to_valhalla (Move move){
	//Take a move, and look which pieces must go to valhalla
	int endIndex = Board::coordtoIndex(move.end());

	// En passant : We must send the captured pawn to Valhalla
	if (move.isEnPassant())
	{
		int captured_pawn_index = 0;

		if (move.movingPiece().isWhite()){captured_pawn_index = en_passant_index_ + 8;}
		if (not move.movingPiece().isWhite()){captured_pawn_index = en_passant_index_ - 8;}
		
		Piece captured_pawn= pieces_[captured_pawn_index];
		go_to_valhalla(captured_pawn);
	}
	
	
	// Capture : we must send the killed piece to Valhalla
	if (move.isCapture()  && not move.isEnPassant())
	{
		Piece killed_piece = pieces_[endIndex];
		go_to_valhalla(killed_piece);
	}
	
	
	// Promotion : we must replace the pawn (and sending it to Valhalla)
	if (move.isPromotion())
	{	
		Piece replaced_pawn = move.movingPiece();
		go_to_valhalla(replaced_pawn);
	}
	

}
void Board::go_to_valhalla(Piece killed_piece){
	//Take a piece and this piece goes to valhalla
	
	bool is_piece_white = killed_piece.isWhite() ;
	int start_index = (is_piece_white ? 0 : 19);
	int free_index = start_index;
	
	for (int j=0 ; j<19 ; j++)
	{
		if (valhalla_FEN_[j+start_index] == '.')
		{
			free_index += j;
			break;
		}
	}
	
	
	valhalla_FEN_[free_index] = killed_piece.type();
}

std::string Board::threatSquares(bool isWhite){
	std::string threats(64, '.');
	for (int i = 0; i < 64; i++)
	{
		Piece p = pieces_[i];
		if (p.type() != '.' && p.type() !='k' && p.type() != 'K' && p.isWhite() == isWhite)
		{
			for (int j = 0; j < 64; j++)
			{
				Piece p2 = pieces_[j];
				if (p2.type() != '.' && p2.isWhite() != isWhite)
				{
					//std::cout << "Can " << p2.type() << " capture " << p.type() << std::endl;
					std::string m = p2.coord() + p.coord();
					//std::cout << "Is " << m << "legal ?" << std::endl;; 
					Move move = create_move(m);
					if (isLegal(move))
					{
						//std::cout << "YES" << std::endl;
						int square = coordtoIndex(p.coord());
						threats[square] = '1';
					}
				}
			}
		}
	}
	return threats;
}

std::string Board::playableSquares(bool isWhite) {
	std::string playable(64, '.');
	for (int i = 0; i < 64; i++)
	{
		Piece p = pieces_[i];
		//std::cout << p.type() <<std::endl;
		if (p.type() != '.' && p.type() !='k' && p.type() != 'K' && p.isWhite() == isWhite)
		{
			for (int j = 0; j < 64; j++)
			{
				if (pieces_[j].type() == 'k' || pieces_[j].type() == 'K' || coordtoIndex(p.coord()) == j){continue;}
				
				std::string m = p.coord() + indextoCoord(j);
				Move move = create_move(m);
				//std::cout << "mOVE<" << m << ">" << std::endl;
				if(isLegal(move)){
					playable[j] = '1';
				}
			}
			
		}
	}
	return playable;
}

std::string Board::controlledSquares(bool isWhite) {
	return playableSquares(!isWhite);	
}

std::string Board::protectedPieces(bool isWhite) {
	std::string protectedPieces(64, '.');
	for (int i = 0; i < 64; i++)
	{
		Piece p = pieces_[i];
		if (p.type() != '.' && p.type() !='k' && p.type() != 'K' && p.isWhite() == isWhite)
		{
			std::string FENwithEnemy = FEN_;
			FENwithEnemy[i] = isWhite ? 'p' : 'P';
			Board boardWithEnemyPiece = Board(FENwithEnemy);
			//boardWithEnemyPiece.print();
			//std::cout << boardWithEnemyPiece.FEN() <<std::endl;
			//std::cout << boardWithEnemyPiece.threatSquares(!isWhite) << std::endl;
			if (boardWithEnemyPiece.threatSquares(!isWhite)[i] == '1') {
				protectedPieces[i] = '1'; 

			}

		}
	}
	return protectedPieces;
}

std::string Board::to_base(int number,int base) {
    if (base < 2 || base > 36) {
        throw std::invalid_argument("Base must be in the range [2, 36]");
    }

    const char* digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string result;

    do {
        result = digits[number % base] + result;
        number /= base;
    } while (number > 0);

    return result;
}

int Board::from_base(const std::string& number, int base) {
    int decimal_value = 0;
    int power = 0;

    // Parcours du nombre de droite à gauche (du chiffre de poids faible au plus élevé)
    for (int i = number.length() - 1; i >= 0; --i) {
        char c = number[i];
		int value = 0;
        if (c >= '0' && c <= '9') {
        	value = c - '0';  // Pour les chiffres
    	} else if (c >= 'A' && c <= 'Z') {
        	value =  c - 'A' + 10;  // Pour les lettres A-Z
    	} else if (c >= 'a' && c <= 'z') {
        	value = c - 'a' + 10;  // Pour les lettres a-z (si nécessaire)
    	}
        
        if (value < 0 || value >= base) {
            std::cerr << "Invalid character in number: " << c << std::endl;
            return -1; // Erreur si un caractère ne correspond pas à la base
        }

        decimal_value += value * std::pow(base, power);
        power++;
    }

    return decimal_value;
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