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
  Stack current_moves;
};

void graph_init(Graph *graph);

void movesGenerator(Graph *graph);
void pawnMoveGenerator(Stack *moves, int squareX, int squareY,
                       Color activeColor, Board board);
void bishopMoveGenerator(Stack *moves, int squareX, int squareY,
                         Color activeColor, Board board);
void rookMoveGenerator(Stack *moves, int squareX, int squareY,
                       Color activeColor, Board board);
void bishopAndRook4DirectionsGen(int incX, int incY, Stack *moves, int squareX,
                          int squareY, Color activeColor, Board board);
void queenMoveGenerator(Stack *moves, int squareX, int squareY,
                        Color activeColor, Board board);
void knightMoveGenerator(Stack *moves, int squareX, int squareY,
                         Color activeColor, Board board);
void kingMoveGenerator(Stack *moves, int squareX, int squareY,
                       Color activeColor, Board board);
void knightAndKing4DirectionsGen(int incX, int incY, Stack *moves, int squareX,
                          int squareY, Color activeColor, Board board);

bool isInBoardSquare(int squareX, int squareY);

void play_move(int move, Board *board);
void update_board(Arc father, Graph *graph);

#endif /* TRUNK_CHESSAINT_INCLUDE_GRAPH_H_ */
