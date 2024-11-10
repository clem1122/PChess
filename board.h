#pragma once
#include "piece.h"
#include "move.h"
#include <string>

class Board{

private:

	std::string FEN_; //The 64 squares and the pieces above each of them
	std::string specialRulesData_; //To whom is the turn (w/b) ; Possible castling (KQkq, - when not possible anymore) ; Index of the En Passant square
	int en_passant_index_;
	Piece* pieces_;

public:

	
	Board();
	Board(std::string FEN);
	~Board();
	
	//Functions to get variables
	
	std::string FEN() {return FEN_;};
	std::string specialRulesData() {return specialRulesData_;};
	int en_passant_index() {return en_passant_index_;};
	Piece* pieces() {return pieces_;};
	bool is_playing_player_white() {return specialRulesData_[0] == 'w' ? true : false;};
	
	//Utility translation functions
	std::string indextoCoord(const int &index);
	int coordtoIndex(std::string coord);
	Board withMove(const Move move);
	
	Piece* FENtoPieces(std::string _FEN);
	std::string PiecestoFEN(const Piece* _pieces);
	
	//Functions to create the object move
	Move create_move(std::string msg);
	std::string create_msg(std::string departure_coord, std::string arrival_coord);
	bool isValidCoord(std::string _start, std::string _end);
	bool is_piece_capturing(std::string start, std::string end, Piece piece);
	bool is_piece_castling(std::string start, std::string end, Piece piece);
	bool is_piece_taking_en_passant(std::string coord_end, Piece piece);
	bool is_piece_promotioning(std::string coord_end, Piece piece);
	
	//Functions to check the legality of a move
	bool isLegal(const Move move);
	bool is_piece_on_square(int index_arrival);
	bool is_white_on_square(int index_arrival);
	bool is_piece_correctly_moving(const Move move);
	bool is_there_obstacle_on_way(const Move move);
	bool is_there_obstacle_on_arrival(const Move move);
	bool is_castling_valid(const Move move);
	bool is_en_passant_valid(const Move move);
	bool isCheck(const bool isWhite, std::string square_to_verify);
	bool isCheckmate(bool isWhite);
	int  find_king(const bool isKingWhite);
	int* trajectory(const Move move);
	Piece* find_checking_pieces(const bool isKingWhite, std::string square_to_verify);
	
	//Functions to play move and change rules in consequence
	void playMove(Move move);
	void change_special_rules_after_move(Move move);
	void change_turn();
	void change_en_passant_square(bool has_a_pawn_moved, bool is_pawn_white, std::string end_coord);
	void block_castling(const Move move, bool isQueenTower);
	

	void print();
}; 
	
	
