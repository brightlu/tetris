typedef struct Piece {
	int xpos;
	int ypos;
	int type;
} piece;


piece *move_piece_down(piece *pi);
piece *move_piece_right(piece *pi);
piece *move_piece_left(piece *pi);
