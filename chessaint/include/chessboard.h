/* Copyright 2015 Hugo GANGLOFF */
/** 
 *  @file chessboard.h
 *  @brief chessboard header
 *  @author HGangloff
 *  @version 1.0
 *  @date 6 March 2015
 *
 *  This files regroups prototypes and some data for the chessboard
 *
 */

#ifndef TRUNK_CHESSAINT_INCLUDE_CHESSBOARD_H_
#define TRUNK_CHESSAINT_INCLUDE_CHESSBOARD_H_

#include <stdio.h>
#include <stdlib.h>


#define WHITE 1
#define BLACK 2

#define NBCASES 64

#define EMPTY 9

#define PAWN 0
#define BISHOP 1
#define KNIGHT 2
#define ROOK 3
#define QUEEN 4
#define KING 5

int color[NBCASES];

int piece[NBCASES];

char pieceChar[12];

char board[NBCASES]; /* K, Q, R, B, N, P and space for empty cases */
char board2[NBCASES];
char board3[NBCASES];

void initBoardToStartPos(char *board); /* Prepare a new board */

void printBoard(char *board); /* Print the board in a given state */

void fenToBoard(char *board, char *fenString);
/* Get the board corresponding to a given FEN string has */
/*in the UCI command "position [fen|startpos] moves ..." */
#endif /*TRUNK_CHESSAINT_INCLUDE_CHESSBOARD_H_*/
