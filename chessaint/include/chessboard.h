/* This file is part of the ChessAInt project 2015 */
/**
 *  @file
 */

#ifndef CHESSAINT_INCLUDE_CHESSBOARD_H_
#define CHESSAINT_INCLUDE_CHESSBOARD_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

/**
 *  Number of square in a board
 *
 */
#define SQUARES_NB 64x
/**
 *  Number of rows and columns
 *
 */
#define ROWCOL_NB 8

/**
 *  @struct Coord
 *  @brief Represents a point on the board
 *  with (7,7) the system
 *
 *  use for enpassant
 *
 */
struct Coord {
  int column; /**< x coordinates */
  int line;   /**< y coordinates */
};

/**
 *  @param Coord Define struct Coord as type
 */
typedef struct Coord Coord;

/**
 *  @enum Color
 *  @brief Colors of pieces
 *
 * To describe the state of a square for example
 */
enum Color {
  white,  /**< white player's possession */
  black,  /**< black player's possession */
  neutral /**< For empty squares */
};

/**
 *  @param Color Define struct Color as type
 */
typedef enum Color Color;

/**
 *  @enum Piece
 *  @brief Pieces types
 *
 *  @todo comments could be aligned
 *
 *  List all pieces
 */
enum Piece {
  pawn,   /**< pawn   - pion (fr) */
  bishop, /**< bishop - fou (fr) */
  knight, /**< knight - cavalier (fr) */
  rook,   /**< rook   - tour (fr) */
  queen,  /**< queen  - dame (fr) */
  king,   /**< king   - roi (fr) */
  empty   /**< for empty squares */
};

/**
 *  @param Piece Define struct Piece as type
 */
typedef enum Piece Piece;

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
 *  @param Square Define struct Square as type
 */
typedef struct Square Square;

/**
 *  @struct Board
 *  @brief Represents board + game data
 *
 *  All data required to play a game from a position is stored in a  board
 *  according to FEN strings data (same fields translated in our structures)
 *  When you got a board you know everything : the player to play, from
 *  which position, with which castles available...
 */
struct Board {
  Square square[ROWCOL_NB][ROWCOL_NB]; /**< A board = 64 squares : 8x8 */

  Color activeColor; /**< Next to play from this position */
  Coord enPassant; /**< Which square can be taken en passant */
  int halfMoveClock; /**< useful to think about draws */
  int fullMoveNb; /**<Total moves, starting to 1 (convention) */
  int availableCastlings[4]; /**< What are the available castles      \n*/
                             /**< [0] : white king side castle        \n*/
                             /**< [1] : white queen side castle       \n*/
                             /**< [2] : black king side castle        \n*/
                             /**< [3] : black queen side castle       \n*/
                             /**< values : 1 for true and 0 for false   */
};

/**
 *  @param Board Define struct Board as type
 */
typedef struct Board Board;

void initAGame(Board *game);

void fenToBoard(char *fen, Board *game);

void printBoardAndData(Board game);

Piece charToPiece(char c);

Color getOtherColor(Color color);

bool isInBoardSquare(int squareX, int squareY);

void findAllPinnings(Board *board, Color activeColor, bool pinned[8][8]);
void findLinePinnings(Board *board, Color enemyColor, bool pinned[8][8],
                      int X, int Y, int incX, int incY);
void findRookPinnings(Board *board, Color enemyColor,
                      bool pinned[8][8], int X, int Y);
void findBishopPinnings(Board *board, Color enemyColor,
                        bool pinned[8][8], int X, int Y);

#endif /* CHESSAINT_INCLUDE_CHESSBOARD_H_ */

