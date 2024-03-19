#include "board.h"


// Board Constructor
Board::Board() {
   
}

// Board Constructor with FEN parameter
Board::Board(const char* _FEN) {
    // Implement constructor with FEN logic here
}

// Board Destructor
Board::~Board() {
    // Implement destructor logic here
}

// Utility function to convert index to coordinate
char Board::indexToCoord(const int &index) {
    return ' ';
}

// Utility function to convert coordinate to index
int Board::coordToIndex(const char* &coord) {
    return 0;
}

// Utility function to play a move
Board Board::playMove(const Move move) {
    return Board();
}

// Utility function to convert FEN string to pieces
Piece* Board::FENtoPieces(const char* _FEN) {
    return nullptr;
}

// Utility function to convert pieces to FEN string
char* Board::PiecestoFEN(const Piece* _pieces) {
    return nullptr;
}

// Game logic function to check if a move is legal
bool Board::isLegal(const Move move) {
    return true;
}




