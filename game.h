#pragma once
#include "board.h"

class Game{

private :

	int socketJ1_;
	int socketJ2_;
	char* nameJ1_;
	char* nameJ2_;
	bool isOver_;
	
public:

	Board board;
	Game();
	~Game();
	
	// Functions to set variables
	
	void set_socketJ1(int _socketJ1) {socketJ1_ = _socketJ1;};
	void set_socketJ2(int _socketJ2) {socketJ2_ = _socketJ2;};
	void set_nameJ1(char* _nameJ1) {nameJ1_ = _nameJ1;};
	void set_nameJ2(char* _nameJ2) {nameJ2_ = _nameJ2;};
	void set_isOver(bool _isOver) {isOver_ = _isOver;};
	
	// Functions to get variables
	
	int socketJ1() {return socketJ1_;};
	int socketJ2() {return socketJ2_;};
	char* nameJ1() {return nameJ1_;};
	char* nameJ2() {return nameJ2_;};
	bool isOver() {return isOver_;};
};

//172.23.230.84
