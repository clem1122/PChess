#include "board.h"


// Board Constructor
Board::Board() {
    // Implement default constructor logic here
}

// Board Constructor with FEN parameter
Board::Board(char[] FEN) {
    // Implement constructor with FEN logic here
}

// Board Destructor
Board::~Board() {
    // Implement destructor logic here
}

// Utility function to convert index to coordinate
char Board::indexToCoord(const int &index) {
    // Implement indexToCoord logic here
}

// Utility function to convert coordinate to index
int Board::coordToIndex(const char* &coord) {
    // Implement coordToIndex logic here
}

// Utility function to play a move
Board Board::playMove(const Move move) {
    // Implement createMove logic here
}

// Utility function to convert FEN string to pieces
Piece[] Board::FENtoPieces(const char* FEN) {
    // Implement FENtoPieces logic here
}

// Utility function to convert pieces to FEN string
char[] Board::PiecestoFEN(const Piece* pieces) {
    // Implement PiecestoFEN logic here
}

// Game logic function to check if a move is legal
bool Board::isLegal(const Move move) {
    // Implement isLegal logic here
}
