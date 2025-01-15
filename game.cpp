#include "game.h"
#include "board.h"
#include <iostream>

Game::Game() {
	board_ = Board();
	socketJ1_ = 0;
	socketJ2_ = 0;
	playCount_ = 0;
	end_result_ = 'o';
	isOver_ = false;
}

Game::Game(std::string FEN) {
	board_ = Board(FEN);
	socketJ1_ = 0;
	socketJ2_ = 0;
	playCount_ = 0;
	end_result_ = 'o';
	isOver_ = false;

}

Game::~Game() {

}

bool Game::play(std::string msg) {
	if (board_.play(msg)) {
		addToHistory(board_.FEN(), board_.specialRulesData());

		if (board_.end_game() != 'o')
		{
			isOver_ = true;
			end_result_ = board_.end_game();

			if (board_.end_game() == 'p') 
			{
				std::cout<< "Pat !"<<std::endl;
			}
			else
			{
				std::string victory_msg = board_.is_playing_player_white() ? "noirs !" : "blancs !";
				std::cout<<"Echec et mat ! Victoire des "<< victory_msg << std::endl;
			}
		}

		if (is_game_null(board_.FEN(), board_.specialRulesData()))
		{
			isOver_ = true;
			end_result_ = 'n';

			std::cout<<"Match nul !"<<std::endl;
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
	
