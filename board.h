#pragma once
#include "piece.h"
#include "move.h"
#include <string>

class Board{

private:

	std::string FEN_; //The 64 squares and the pieces above each of them
	std::string valhalla_FEN_; //The 32 places where we put dead pieces 
	std::string specialRulesData_; //To whom is the turn (w/b) ; Possible castling (KQkq, - when not possible anymore) ; Index of the En Passant square
	int en_passant_index_;
	Piece* pieces_;
	Piece* valhalla_pieces_;
	char end_game_;

public:

	
	Board();
	Board(std::string FEN);
	Board(std::string FEN, std::string Valhalla_FEN);
	Board(std::string FEN, int en_passant_index);
	~Board();
	
	//Functions to get variables
	
	std::string FEN() {return FEN_;};
	std::string valhalla_FEN() {return valhalla_FEN_;};
	std::string specialRulesData() {return specialRulesData_;};
	int en_passant_index() {return en_passant_index_;};
	std::string en_passant_coord() {return (en_passant_index_ == 99) ? "-" : indextoCoord(en_passant_index_);};
	Piece* pieces() {return pieces_;};
	Piece* valhalla_pieces() {return valhalla_pieces_;};
	bool is_playing_player_white() {return specialRulesData_[0] == 'w' ? true : false;};
	char end_game() {return end_game_;};

	
	//Utility translation functions
	std::string indextoCoord(const int &index);
	int coordtoIndex(std::string coord);
	Board withMove(const Move move, char promotion_piece = '.');
	std::string to_base(int number, int base);
	int from_base(const std::string& number, int base);

	Piece* FENtoPieces(std::string _FEN);
	std::string PiecestoFEN(const Piece* _pieces);
	void modify_piece(std::string coord, char piece_type);
	
	//Functions to create the object move
	Move create_move(std::string msg);
	std::string create_msg(std::string departure_coord, std::string arrival_coord);
	bool isValidCoord(std::string _start, std::string _end);
	bool is_piece_capturing(std::string start, std::string end, Piece piece);
	bool is_piece_castling(std::string start, std::string end, Piece piece);
	bool is_piece_taking_en_passant(std::string coord_end, Piece piece);
	bool is_piece_promoting(std::string coord_end, Piece piece);
	
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
	bool isPat(bool isWhite);
	int  find_king(const bool isKingWhite);
	int* trajectory(const Move move);
	Piece* find_checking_pieces(const bool isKingWhite, std::string square_to_verify);
	Piece piece_on_square(std::string square_arrival);
	
	//Functions to play move and change rules in consequence
	void playMove(Move move, char promotion_piece = '.');
	void change_special_rules_after_move(Move move);
	void change_turn();
	void change_en_passant_square(bool has_a_pawn_moved, bool is_pawn_white, std::string end_coord);
	void block_castling(const Move move, bool isQueenTower);
	bool play(std::string move);
	
	// Valhalla functions
	Piece* valhallaFENtoPieces(std::string _FEN);
	std::string valhalla_index_to_coord(const int &index);
	int valhalla_coord_to_index(std::string v_cord);
	void send_to_valhalla (Move move);
	void go_to_valhalla(Piece killed_piece);
	void valhalla_print();

	//Interface functions
	std::string threatSquares(bool isWhite);
	std::string playableSquares(bool isWhite);
	std::string controlledSquares(bool isWhite);

	void print();
}; 
	
	
