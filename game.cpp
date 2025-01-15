#include "game.h"
#include "board.h"
#include <iostream>

Game::Game() {
	board = Board();
	socketJ1_ = 0;
	socketJ2_ = 0;
	playCount_ = 0;
}

Game::Game(std::string FEN) {
	board = Board(FEN);
	socketJ1_ = 0;
	socketJ2_ = 0;
	playCount_ = 0;

}

Game::~Game() {

}

void Game::play(std::string msg) {
	board.play(msg);
	addToHistory(board.FEN(), board.specialRulesData());

	if (board.end_game() != 'o')
	{
		set_isOver(true);
		set_end_result(board.end_game());
	}

	if (is_game_null(board.FEN(), board.specialRulesData()))
	{
		set_isOver(true);
		set_end_result('n');
	}
}

void Game::addToHistory(std::string FEN, std::string specialRules) {
	history_[playCount_] = FEN + " " + specialRules;
	playCount_++;
}

void Game::printHistory(){
	for (int i = 0; i < playCount_; i++)
	{
		std::cout << "Coup " << i << " : " << history_[i] << std::endl;
	}
}

bool Game::is_game_null(std::string FEN, std::string specialRules){

	int identical_count = 0;
	std::string actual_state = FEN + " " + specialRules;

	for (int i = 0 ; i< playCount_ ; i++)
	{
		if (actual_state.compare(history_[i]))
		{
			identical_count++;
		}

		if (identical_count == 3) 
		{
			return true;
		}
	}

	return false;
}
	
