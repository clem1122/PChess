#pragma once
#include "board.h"
#include <array>


class Game{

private :

	int socketJ1_;
	int socketJ2_;
	char* nameJ1_;
	char* nameJ2_;
	bool isOver_;
	char end_result_;
	std::array<std::string, 200> history_;
	int playCount_;
	Board board_;
	
public:

	Game();
	Game(std::string FEN);
	~Game();
	bool play(std::string msg);
	
	// Functions to set variables
	
	void set_socketJ1(int _socketJ1) {socketJ1_ = _socketJ1;};
	void set_socketJ2(int _socketJ2) {socketJ2_ = _socketJ2;};
	void set_nameJ1(char* _nameJ1) {nameJ1_ = _nameJ1;};
	void set_nameJ2(char* _nameJ2) {nameJ2_ = _nameJ2;};
	void set_isOver(bool _isOver) {isOver_ = _isOver;};
	void set_end_result(char _end_result) {end_result_ = _end_result;};
	void addToHistory(std::string FEN, std::string specialRules);
	void addPlayCount(){playCount_++;};
	
	// Functions to get variables
	
	int socketJ1() {return socketJ1_;};
	int socketJ2() {return socketJ2_;};
	char* nameJ1() {return nameJ1_;};
	char* nameJ2() {return nameJ2_;};
	bool isOver() {return isOver_;};
	char end_result() {return end_result_;};
	std::array<std::string, 200> history(){ return history_;};
	int playCount(){return playCount_;};
	Board board(){return board_;}

	// print
	void printHistory();

	// Manage end game
	bool is_game_null(std::string FEN, std::string specialRules);

};

