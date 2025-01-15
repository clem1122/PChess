#include "game.h"
#include "board.h"
#include <iostream>

Game::Game() {
	board_ = Board();
	socketJ1_ = 0;
	socketJ2_ = 0;
	playCount_ = 0;
}

Game::Game(std::string FEN) {
	board_ = Board(FEN);
	socketJ1_ = 0;
	socketJ2_ = 0;
	playCount_ = 0;

}

Game::~Game() {

}

bool Game::play(std::string msg) {
	if (board_.play(msg)){
		addToHistory(board_.FEN(), board_.specialRulesData());
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