/* This file is part of the ChessAInt project 2015 */
/**
 *  @file
 */

#ifndef CHESSAINT_INCLUDE_GRAPH_H_
#define CHESSAINT_INCLUDE_GRAPH_H_

#include "include/chessboard.h"
#include "include/llist.h"

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
 *
 *  @todo Add doxy doc for struct members 
 *
 */

struct Graph {
  Board root;
  Board current_node;
  Llist links;
  Stack current_moves;
};

void graph_init(Graph *graph);
void graph_free(Graph *graph);

void movesGenerator(Graph *graph);

void pawnMoveGeneratorCapture(Stack *moves, int squareX, int squareY,
                       Color activeColor, Board board);
void pawnMoveGeneratorNoCapture(Stack *moves, int squareX, int squareY,
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

void castlesMoveGenerator(int incX, int squareX, int squareY,
                          Stack *moves, Board board);

bool isInBoardSquare(int squareX, int squareY);

void play_move(int move, Board *board);

void update_board(Arc father, Graph *graph);

void copy_board(Board *src, Board *dest);

#endif /* CHESSAINT_INCLUDE_GRAPH_H_ */

