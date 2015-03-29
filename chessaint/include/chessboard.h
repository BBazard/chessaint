/*This file is part of the ChessAInt project 2015*/

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

#include "include/graph.h"

#define NBSQUARES 64

typedef struct Coord Coord;
struct Coord {
  char column;
  int line;
};

typedef enum Castling Castling;
enum Castling {
  K,
  Q,
  k,
  q,
  no
};


typedef enum Color Color;
enum Color {
  white,
  black,
  neuter
};

typedef enum Piece Piece;
enum Piece {
  pawn,
  bishop,
  knight,
  rook,
  queen,
  king,
  empty
};


typedef struct square Square;
struct square {
  Color color;
  Piece piece;
};


typedef struct board Board;
struct board {
  Square square[NBSQUARES];
  /* Next fields contain everything necessary to play
  according to FEN notation */
  Color activeColor;
  Castling availableCastlings[4];
  Coord enPassant;
  int pliesSinceLastCaptureOrLastPawnMovement;
  int nbMovesTotal;
};

Color colorToInit[NBSQUARES];
Piece piecesToInit[NBSQUARES];


Board myGame;

void initAGame(Board *game);

char **moveGenerator(Board game);
char **pawnMoveGenerator(Board game);
char **bishopMoveGenerator(Board game);
char **knightMoveGenerator(Board game);
char **rookMoveGenerator(Board game);
char **queenMoveGenerator(Board game);
char **kingMoveGenerator(Board game);

char **areTheseLegalMoves(char **listOfRawMoves, Board game);

void fenToBoard(char *fen, Board *game);

void printBoardAndData(Board game);





#endif /*TRUNK_CHESSAINT_INCLUDE_CHESSBOARD_H_*/

