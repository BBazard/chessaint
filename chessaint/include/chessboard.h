/** 
 *  @file chessboard.h
 *  @brief chessboard header
 *
 *  This files regroups prototypes and some data for the chessboard
 *
 */

#ifndef TRUNK_CHESSAINT_INCLUDE_CHESSBOARD_H_
#define TRUNK_CHESSAINT_INCLUDE_CHESSBOARD_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h> 
#include <stdbool.h>

#include "../include/graph.h"


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

char boardChar[NBCASES]; /* K, Q, R, B, N, P and space for empty cases */
                         /*Dynamic table with char representation*/
int boardPiece[NBCASES]; /* Dynamic table with piece representation */
int boardColor[NBCASES]; /*Dynamic table with color representation */

void initBoardToStartPos(char *board, int *piece, int *color); /* Prepare a new board */

void printBoard(char *board, int *piece, int *color); /* Print the board in a given state */

void fenToBoard(char *board, char *fenString);
/* Get the board corresponding to a given FEN string has */
/*in the UCI command "position [fen|startpos] moves ..." */

void humanVHuman(); /*Basic HumanVHuman game, this function must grow*/

void moveBoard(char *move, char *board, int *piece, int *color); /*Only plays a move */

bool isAWhiteLegalMove(char *move);

bool isABlackLegalMove(char *move);

Arc getArcFromMove(char *move, char whoPlayed, int nbMoves);

int lettersCoordToNumberCoord(char *square);

#endif /*TRUNK_CHESSAINT_INCLUDE_CHESSBOARD_H_*/
