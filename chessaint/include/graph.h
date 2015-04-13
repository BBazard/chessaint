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

void pawnMoveGenerator(int squareX, int squareY, Color activeColor,
                        Board board); 
void bishopMoveGenerator(int squareX, int squareY, Color activeColor,
                        Board board);
void rookMoveGenerator(int squareX, int squareY, Color activeColor,
                        Board board);
void queenMoveGenerator(int squareX, int squareY, Color activeColor,
                        Board board);
void knightMoveGenerator(int squareX, int squareY, Color activeColor,
                        Board board);
void kingMoveGenerator(int squareX, int squareY, Color activeColor,
                        Board board);

bool isInBoardSquare(int squareX, int squareY);

#endif // TRUNK_CHESSAINT_INCLUDE_GRAPH_H_
