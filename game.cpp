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