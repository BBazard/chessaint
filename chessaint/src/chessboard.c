
#include "../include/chessboard.h"

int color[64] = {
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,
	9,9,9,9,9,9,9,9,
	9,9,9,9,9,9,9,9,
	9,9,9,9,9,9,9,9,
	9,9,9,9,9,9,9,9,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1
}; /*WHITE BLACK or EMPTY*/

int piece[64] = {
	3,2,1,4,5,1,2,3,
	0,0,0,0,0,0,0,0,
	9,9,9,9,9,9,9,9,
	9,9,9,9,9,9,9,9,
	9,9,9,9,9,9,9,9,
	9,9,9,9,9,9,9,9,
	0,0,0,0,0,0,0,0,
	3,2,1,4,5,1,2,3
}; /*PAWN BISHOP KNIGHT ROOK QUEEN KING or EMPTY */

char pieceChar[12] = {
	'P', 'B', 'N', 'R', 'Q', 'K', 'p', 'b', 'n', 'r', 'q', 'k'
}; /* Pawn Bishop kNight Rook Queen King ; lower for black ; upper case for white */

void initBoardToStartPos(char *board) {
	int i;
	for(i=0;i<=63;++i) {
		switch (color[i]) {
			case WHITE:
				board[i]=pieceChar[piece[i]];
				break;
			case BLACK:
				board[i]=pieceChar[piece[i]+6]; /* add 6 to go to lower case */
				break;
			case EMPTY:
				board[i]=' ';
				break;
		}
	}
}

void printBoard(char *board) {
	int i;
	for(i=0;i<=63;i++) {
		printf("|%c", board[i] );

		if((i+1)%8==0) {
			printf("|\n");
		}
	}
}
