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


/**
 * @comment should be SQUARES_NB
 */
#define NBSQUARES 64

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
 *
 *  Will soon disappear
 */
struct Coord {
  char column; /**< x coordinates*/
  int line; /**< y coordinates*/
};



typedef enum Castling Castling;

/** 
 *  @enum Castling
 *  @brief What are the availble castles ?
 *
 */
enum Castling {
  K, /**< white castle on king's side */
  Q, /**< white castle on queen's side */
  k, /**< black castle on king's side */
  q, /**< black castle on queen's side */
  no /**<no castle available */
};


typedef enum Color Color;

/** 
 *  @enum Color
 *  @brief Colors of pieces 
 *
 * To describe the state of a square for exemple
 */
enum Color {
  white, /**< white player's possession*/
  black, /**< black player's possession*/
  neutral /**< For empty squares */
};


typedef enum Piece Piece;

/** 
 *  @enum Piece
 *  @brief Pieces types
 *
 *  @comment comments could be aligned
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
  Color color; /**< The color of the owner of the case, can be neutral*/
  Piece piece; /**< The piece which is in the square, can be empty*/
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
  Square square[NBSQUARES]; /**< A board = 64 squares*/

  Color activeColor; /**< Next to play from this position*/
  /**
   * @bug numeric value 4
   */
  Castling availableCastlings[4]; /**< What are the available castles can be 
                                  no,no,no,no*/
  Coord enPassant; /**< Which square can be taken en passant*/
  /**
   * @todo rename
   * @note "halfmoveClock" according to wikipedia fen page
   */
  int pliesSinceLastCaptureOrLastPawnMovement; /**< useful to think about draws
                                              a ply = a white/black move only*/
  /**
   * @comment "fullMoveNb" according to wikipedia fen page
   * @note in any case "nb" is supposed to be last
   */
  int nbMovesTotal; /**<Total moves, starting to 1 (convention)*/
};

Color colorToInit[NBSQUARES];
Piece piecesToInit[NBSQUARES];


Board myGame;

void initAGame(Board *game);



/*
char **pawnMoveGenerator(Board game);
char **bishopMoveGenerator(Board game);
char **knightMoveGenerator(Board game);
char **rookMoveGenerator(Board game);
char **queenMoveGenerator(Board game);
char **kingMoveGenerator(Board game); */

/*

char **areTheseLegalMoves(char **listOfRawMoves, Board game); */

void fenToBoard(char *fen, Board *game);

void printBoardAndData(Board game);





#endif /*TRUNK_CHESSAINT_INCLUDE_CHESSBOARD_H_*/

