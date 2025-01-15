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

void Game::print(){
	std::string player = board_.is_playing_player_white() ? "blancs" : "noirs";
	std::cout<< "Coup " << playCount_<< " : Trait aux " << player << std::endl;
	board_.print();
	board_.valhalla_print();
}

bool Game::is_game_null(std::string FEN, std::string specialRules){

	int identical_count = 0;
	std::string actual_state = FEN + " " + specialRules;

	for (int i = 0 ; i< playCount_ ; i++)
	{
		std::cout << "actual : " << actual_state<< std::endl;
		//std::cout << "compare to FEN " << i << ": " << history_[i]<< std::endl;
		if (actual_state.compare(history_[i]) == 0)
		{
			identical_count++;
			std::cout<<"Identiques à  "<< history_[i] << "( identical_count = "<<identical_count<<" )" <<std::endl;
		}

		if (identical_count == 3) 
		{
			return true;
		}
	}

	return false;
}
	
