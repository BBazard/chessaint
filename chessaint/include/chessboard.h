

#ifndef CHESSBOARD_H_
#define CHESSBOARD_H_

#include <stdio.h>
#include <stdlib.h>


#define WHITE 1
#define BLACK 2

#define EMPTY 9 

#define PAWN 0
#define BISHOP 1
#define KNIGHT 2
#define ROOK 3
#define QUEEN 4
#define KING 5

int color[64];

int piece[64];

char pieceChar[12];

char board[64]; /* K, Q, R, B, N, P and space for empty cases */

void initBoardToStartPos(char *board); /* Prepare a new board */

void printBoard(char *board); /* Print the board in a given state */

#endif