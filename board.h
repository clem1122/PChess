#pragma once
#include "piece.h"
#include "move.h"

class Board{

private:

	char FEN_[64]; //The 64 squares and the pieces above each of them
	char specialRulesData_[6]; //To whom is the turn (w/b) ; Possible castling (KQkq, - when not possible anymore) ; Index of the En Passant square
	int en_passant_index_;
	Piece* pieces_;

public:

	
	Board();
	Board(const char* FEN);
	~Board();
	
	//Functions to get variables
	
	char* FEN() {return FEN_;};
	char* specialRulesData() {return specialRulesData_;};
	int en_passant_index() {return en_passant_index_;};
	Piece* pieces() {return pieces_;};
	bool is_playing_player_white() {return specialRulesData_[0] == 'w' ? true : false;};
	
	//Utility translation functions
	char* indextoCoord(const int &index);
	int coordtoIndex(const char* coord);
	Board withMove(const Move move);
	
	Piece* FENtoPieces(const char* _FEN);
	char* PiecestoFEN(const Piece* _pieces);
	
	//Functions to create the object move
	Move create_move(const char* msg);
	bool isValidCoord(const char* _start, const char* _end);
	bool is_piece_capturing(const char* start, const char* end, Piece piece);
	bool is_piece_castling(const char* start, const char* end, Piece piece);
	bool is_piece_taking_en_passant(const char* coord_end, Piece piece);
	bool is_piece_promotioning(const char* coord_end, Piece piece);
	
	//Functions to check the legality of a move
	int* trajectory(const Move move);
	bool isLegal(const Move move);
	bool is_piece_on_square(int index_arrival);
	bool is_white_on_square(int index_arrival);
	bool is_piece_correctly_moving(const Move move);
	bool is_there_obstacle_on_way(const Move move);
	bool is_there_obstacle_on_arrival(const Move move);
	bool is_castling_valid(const Move move);
	bool is_en_passant_valid(const Move move);
	bool isCheck(const bool isWhite, const char* square_to_verify);
	bool isCheckmate(bool isWhite);
	int  find_king(const bool isKingWhite);
	Piece* find_checking_pieces(const bool isKingWhite, const char* square_to_verify);
	
	//Functions to play move and change rules in consequence
	void playMove(Move move);
	void change_special_rules_after_move(Move move);
	void change_turn();
	void change_en_passant_square(bool has_a_pawn_moved, bool is_pawn_white, const char* end_coord);
	void block_castling(const Move move, bool isQueenTower);
	

	void print();
}; 
	
	
