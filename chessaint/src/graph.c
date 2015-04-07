/* This file is part of the ChessAInt project 2015 */
/** 
 *  @file graph.c
 *  @brief graph structure basic functions
 *
 *  This file implements functions to add or remove Arc from a linked list,
 *  totally suppress a list and print an Arc or a list
 *
 */

#include "include/graph.h"

#include <assert.h>
#include <string.h>



/**
 *  @fn void movesGenerator(Graph graph)
 *  @brief gives all moves from a graph
 *  @param[in, out] TO BE DETERMINED 
 *  
 *  @note  Need to add the en passant kill
 *
 *  @note  "pieceMoveGenerator" will return moves that will be checked using 
 *          start and stop positions
 */

void movesGenerator(Graph graph) {
  int i = 0;
  int squareId;

  for (i = 0 ; i <= 63 ; ++i) {
    if (graph.root.square[i].color == graph.root.activeColor) {
      squareId = squareNumberTo77Sytem(i);
      switch (graph.root.square[i].piece) {
        case pawn:
          /* Need to add the en passant square in parameters when
          the large number structures that helds this data will be ok */
          pawnMoveGenerator(squareId, graph.root.activeColor);
          break;
        case bishop:
          bishopMoveGenerator(squareId);
          break;
        case knight:
          break;
        case rook:
          break;
        case queen:
          break;
        case king:
          break;
      }
    }
  }
}

/**
 *  @fn void pawnMoveGenerator(int squareId, Color activeColor)
 *  @brief gives all moves for a pawn sitting on a given square
 *  @param[in] the int squareId : identifier of the square in 7x7 system
 *   and the color of the pawn to move 
 *  
 *  This function gives all possible move for a colored pawn ON THE BOARD.
 *  Another function will then check if those moves are possibly in this game
 *  So...
 *  @note  this function will soon return the moves 
 *  (just waiting for the stack structure)
 *  @note  Need enPassant handling and promotion handling
 */


void pawnMoveGenerator(int squareId, Color activeColor) {
  int move[5] = {0, 0, 0, 0, 0};
  /* later move[5] for en passant */
  move[5] = 0;

  if (activeColor == white) {

    if (squareId % 10 == 1) 
      move[1] = twoSquaresUp; /* 2 squares up (from row 2 only) */
    else
      move[1] = noMove; /* else move doesnt exist */

    move[2] = oneSquareUp; /* 1 squares up */

    if (squareId < lastColumn)
      move[3] = oneSquareUpAndLeft; /* 1 square up on the left (killing an opponents piece) 
                (on all columns except last) */
    else
      move[3] = noMove;

    if (squareId > firstColumn)
      move[4] = oneSquareUpAndRight; /* 1 square up on the right (also killing) 
                  (on all colums except first) */
    else
      move[4] = noMove;

  } else {

    if (squareId % 10 == 6)
      move[1] = twoSquaresDown;
    else
      move[1] = noMove;

    move[2] = oneSquareDown;

    if (squareId < lastColumn)
      move[3] = oneSquareDownAndLeft; /* 1 square down on the left (killing an opponents piece) 
                (on all columns except last) */
    else
      move[3] = noMove;

    if (squareId > firstColumn)
      move[4] = oneSquareDownAndRight;
    else
      move[4] = noMove;
  }

  for (int i = 0 ; i < 5 ; i++) {
    if (move[i] != noMove) {
      printf("%d -> %d  \n", squareId, squareId + move[i]);
    }
  }
}

/**
 *  @fn void bishopMoveGenerator(int squareId, Color activeColor)
 *  @brief gives all moves for a bishop sitting on a given square
 *  @param[in] squareId and the color of the bishop to move 
 *  
 *  This function gives all possible move for a colored pawn ON THE BOARD.
 *  Another function will then check if those moves are possibly in this game
 *  So...
 *  @note  this function will soon return the moves 
 *  (just waiting for the stack structure)
 */

void bishopMoveGenerator(int squareId) {

}