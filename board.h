#include "piece.cpp"
#include "move.cpp"

class Board{
public:
	char FEN[64];
	char specialRulesData[];
	Piece* pieces;
	
	Board();
	Board(char* FEN);
	~Board();
	
	char indexToCoord(const int &index);
	int coordToIndex(const char* &coord);
	Board playMove(const Move move);
	
	Piece* FENtoPieces(const char* FEN);
	char* PiecestoFEN(const Piece* pieces);
	
	bool isLegal(const Move move);
}; 
	
	
