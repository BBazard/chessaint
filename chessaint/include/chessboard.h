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


#define SQUARES_NB 64
/*Number of rowws and columns = 8*/
#define ROWCOL_NB 8



/**
 *  @typedef Coord
 *  @brief Definition of the Coord type
 *
 *  Defines struct Coord as the Coord type
 *
 */
typedef struct Coord Coord;

/**
 *  @struct Coord
 *  @brief Represents a point on the board
 *  with (7,7) the system
 *
 */
struct Coord {
  int column; /**< x coordinates */
  int line; /**< y coordinates */
};

typedef enum Color Color;

/**
 *  @enum Color
 *  @brief Colors of pieces
 *
 * To describe the state of a square for exemple
 */
enum Color {
  white, /**< white player's possession */
  black, /**< black player's possession */
  neutral /**< For empty squares */
};


typedef enum Piece Piece;

/**
 *  @enum Piece
 *  @brief Pieces types
 *
 *  @todo comments could be aligned
 *
 *  List all pieces
 */
enum Piece {
  pawn, /**< pawn - pion (fr) */
  bishop, /**< bishop - fou (fr) */
  knight, /**< knight - cavalier (fr) */
  rook, /**< rook - tour (fr) */
  queen, /**< queen - dame (fr) */
  king, /**< king - roi (fr) */
  empty /**< for empty squares */
};

 /**
 *  @typedef Square
 *  @brief Definition of the Square type
 *
 *  Defines struct Square as the Square type
 *
 */
typedef struct Square Square;


/**
 *  @struct Square
 *  @brief Represents a square on the board
 *
 */

struct Square {
  Color color; /**< The color of the owner of the case, can be neutral */
  Piece piece; /**< The piece which is in the square, can be empty */
};

 /**
 *  @typedef Board
 *  @brief Definition of the Board type
 *
 *  Defines struct Board as the Board type
 *
 */
typedef struct Board Board;

/**
 *  @struct Board
 *  @brief Represents board + game data
 *
 *  All data required to play a game from a position is stored in a  board
 *  according to FEN strings data (same fields tranlated in our structures)
 *  When you got a board you know everything : the player to play, from
 *  which position, with which castles available...
 */
struct Board {
  Square square[ROWCOL_NB][ROWCOL_NB]; /**< A board = 64 squares : 8x8 */

  Color activeColor; /**< Next to play from this position */
  /**
   * @bug numeric value 4
   */
  char availableCastlings[4]; /**< What are the available castles can be
                                  no, no, no, no */
  Coord enPassant; /**< Which square can be taken en passant */
  int halfMoveClock; /**< useful to think about draws */
  int fullMoveNb; /**<Total moves, starting to 1 (convention) */
};

/* lines first, columns then */
Color colorToInit[ROWCOL_NB][ROWCOL_NB];
Piece piecesToInit[ROWCOL_NB][ROWCOL_NB];


Board myGame;

void initAGame(Board *game);

void fenToBoard(char *fen, Board *game);

void printBoardAndData(Board game);





#endif /*TRUNK_CHESSAINT_INCLUDE_CHESSBOARD_H_*/

