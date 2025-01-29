#include "game.h"
#include "board.h"
#include <iostream>

Game::Game() {
	board = Board();
	socketJ1_ = 0;
	socketJ2_ = 0;
	playCount_ = 0;
	end_result_ = 'o';
	isOver_ = false;
}

Game::Game(std::string FEN) {
	board = Board(FEN);
	socketJ1_ = 0;
	socketJ2_ = 0;
	playCount_ = 0;
	end_result_ = 'o';
	isOver_ = false;

}

Game::Game(std::string FEN, std::string valhalla_FEN) {
	board = Board(FEN,valhalla_FEN);
	socketJ1_ = 0;
	socketJ2_ = 0;
	playCount_ = 0;
	end_result_ = 'o';
	isOver_ = false;

}

Game::~Game() {

}

bool Game::play(std::string msg) {
	if (board.play(msg)) {
		addToHistory(board.FEN(), board.specialRulesData());

		if (board.end_game() != 'o')
		{
			isOver_ = true;
			end_result_ = board.end_game();

			if (board.end_game() == 'p') 
			{
				std::cout<< "Pat !"<<std::endl;
			}
			else
			{
				std::string victory_msg = board.is_playing_player_white() ? "noirs !" : "blancs !";
				std::cout<<"Echec et mat ! Victoire des "<< victory_msg << std::endl;
			}
		}

		if (is_game_null(board.FEN(), board.specialRulesData()))
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
	std::string player = board.is_playing_player_white() ? "blancs" : "noirs";
	std::cout<< "Coup " << playCount_<< " : Trait aux " << player << std::endl;
	board.print();
	board.valhalla_print();
}

bool Game::is_game_null(std::string FEN, std::string specialRules){

	int identical_count = 0;
	std::string actual_state = FEN + " " + specialRules;
	//std::cout << "actual : " << actual_state<< std::endl;
	for (int i = 0 ; i< playCount_ ; i++)
	{
		
		//std::cout << "compare to FEN " << i << ": " << history_[i]<< std::endl;
		if (actual_state.compare(history_[i]) == 0)
		{
			identical_count++;
			//std::cout<<"Identiques à  "<< history_[i] << "( identical_count = "<<identical_count<<" )" <<std::endl;
		}

		if (identical_count == 3) 
		{
			return true;
		}
	}

	return false;
}
	
