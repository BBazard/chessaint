/* This file is part of the ChessAInt project 2015 */
/**
 *  @file
 */

#ifndef CHESSAINT_INCLUDE_GRAPH_H_
#define CHESSAINT_INCLUDE_GRAPH_H_

#include "include/chessboard.h"
#include "include/llist.h"

/**
 *  @struct Graph
 *  @brief Represents a graph for astar computation
 *
 *  Stores the graph data
 *
 */
struct Graph {
  Board root;           /**< The board after the player has played */
  Board current_node;   /**< The board is for the astar */
  Stack current_moves;  /**< The moves playable for a given node */
  Llist links;          /**< The list of all the nodes of the graph */
                        /**< (score sorted) */
};

/**
 *  @param Graph Define struct Graph as type
 */
typedef struct Graph Graph;

void graph_alloc(Graph *graph);
void graph_free(Graph *graph);

void play_move(int move, Board *board);


void movesGenerator(Graph *graph);

void pawnMoveGeneratorCapture(Stack *moves, int squareX, int squareY,
                              Color activeColor, Board board);

void pawnMoveGeneratorNoCapture(Stack *moves, int squareX, int squareY,
                                Color activeColor, Board board);

void bishopMoveGenerator(Stack *moves, int squareX, int squareY,
                         Color activeColor, Board board);

void rookMoveGenerator(Stack *moves, int squareX, int squareY,
                       Color activeColor, Board board);

void bishopAndRook4DirectionsGen(int incX, int incY, Stack *moves,
                                 int squareX, int squareY,
                                 Color activeColor, Board board);

void queenMoveGenerator(Stack *moves, int squareX, int squareY,
                        Color activeColor, Board board);

void knightMoveGenerator(Stack *moves, int squareX, int squareY,
                         Color activeColor, Board board);

void kingMoveGenerator(Stack *moves, int squareX, int squareY,
                       Color activeColor, Board board, bool threats[8][8]);

void knightAndKing4DirectionsGen(int incX, int incY, Stack *moves,
                                 int squareX, int squareY,
                                 Color activeColor, Board board);

void castlesMoveGenerator(int incX, int squareX, int squareY,
                          Stack *moves, Board board);

void update_board(Node father, Board *board);

void findThreats(Board *board, Color color1, Color color2,
                      bool threats[8][8]);

  void bishopThreatGenerator(int squareX, int squareY, Board board,
                            bool threats[8][8]);

  void rookThreatGenerator(int squareX, int squareY, Board board,
                          bool threats[8][8]);

  void queenThreatGenerator(int squareX, int squareY, Board board,
                          bool threats[8][8]);

  void knightThreatGenerator(int squareX, int squareY, bool threats[8][8]);

  void kingThreatGenerator(int squareX, int squareY, bool threats[8][8]);

  void pawnThreatGenerator(int squareX, int squareY,
                     Color activeColor, bool threats[8][8]);

  void lineThreatGenerator(int incX, int incY, int squareX,
                                 int squareY, Board board, bool threats[8][8]);

  void squareThreatGenerator(int incX, int incY, int squareX, int squareY,
                                 bool threats[8][8]);

  void printThreatBoard(bool threats[8][8]);

void stopThreat(Stack *stack, Board board, bool pinned[8][8],
              bool threats[8][8], int threatenedX, int threatenedY);

  void stopThreatMoveGenerator(Board board, Stack *moves,
                                bool pinned[8][8]);

  void playMoveToCheckThreat(int move, Board *board);

bool isThreatened(int X, int Y, bool threats[8][8]);

bool isSurrounded(int X, int Y, Board board, bool threats[8][8]);

void checkSurroundings(int X, int Y, Board board, bool threats[8][8],
                      bool *answer);
#endif /* CHESSAINT_INCLUDE_GRAPH_H_ */

