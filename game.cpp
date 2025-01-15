#include "game.h"
#include "board.h"
#include <iostream>

Game::Game() {
	board_ = Board();
	socketJ1_ = 0;
	socketJ2_ = 0;
	playCount_ = 0;
	end_result_ = 'o';
}

Game::Game(std::string FEN) {
	board_ = Board(FEN);
	socketJ1_ = 0;
	socketJ2_ = 0;
	playCount_ = 0;
	end_result_ = 'o';

}

Game::~Game() {

}

bool Game::play(std::string msg) {
	if (board_.play(msg)) {
		addToHistory(board_.FEN(), board_.specialRulesData());

		if (board_.end_game() != 'o')
		{
			set_isOver(true);
			set_end_result(board_.end_game());
		}

		if (is_game_null(board_.FEN(), board_.specialRulesData()))
		{
			set_isOver(true);
			set_end_result('n');
		}
		return true;
	}
	return false;
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
	
