/* This file is part of the ChessAInt project 2015 */
/** 
 *  @file graph.h
 *  @brief graph structure header
 *
 *  This file implements enumerations and structures for the graph item and 
 *  the prototype of the functions developped in graph.c file
 *
 */

#ifndef TRUNK_CHESSAINT_INCLUDE_GRAPH_H_
#define TRUNK_CHESSAINT_INCLUDE_GRAPH_H_


#include "./chessboard.h"
#include "./llist.h"

typedef enum  LimitTests LimitTests;
/** 
 *  @enum limitTests
 *  @brief To test things with the limits of the board
 *  
 */
enum LimitTests {
  lastColumn = 68,
  firstColumn = 9
};



typedef enum PawnMove PawnMove;
/** 
 *  @enum pawnMove
 *  @brief all possible pawn moves
 *
 *  Useful in pawnMoveGenerator for code comprehension
 */
enum PawnMove {
  noMove = 0,
  twoSquaresUp = 2,
  oneSquareUp = 1,
  oneSquareUpAndLeft = 11,
  oneSquareUpAndRight = -9,
  twoSquaresDown = -2,
  oneSquareDown = -1,
  oneSquareDownAndLeft = 9,
  oneSquareDownAndRight = -11
};



/** 
 *  @typedef Graph
 *  @brief Definition of the Graph type
 *
 *  Defines struct Graph as the Graph type
 *
 */

typedef struct Graph Graph;

/** 
 *  @struct Graph
 *  @brief Represents a graph for astar computation
 *
 *  Stores the graph data
 */

struct Graph {
  Board root;
  Board current_node;
  Llist links;
};

void movesGenerator(Graph graph);
void pawnMoveGenerator(int squareId, Color activeColor);
void bishopMoveGenerator(int squareId);

#endif /*TRUNK_CHESSAINT_INCLUDE_GRAPH_H_*/
