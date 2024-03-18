class Move{
public:
	char start[2];
	char end[2];
	
	Piece movingPiece;
	
	bool isCapture;
	bool isPromotion;
	bool isCastling;
	bool isEnPassant;
	
	Move(const char* start, const char* end);
	
};
