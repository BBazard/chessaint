/* This file is part of the ChessAInt project 2015 */
/**
 *  @file
 *
 *  Astar computation algorithm header
 *
 */

#ifndef CHESSAINT_INCLUDE_ASTAR_H_
#define CHESSAINT_INCLUDE_ASTAR_H_

#include "include/heuristic.h"

void move_to_node(int move, Arc father, Arc *current, Board oldboard);
int next_gen(Graph *graph, int depth);
int astar(Graph *graph, int query_score, int depth, int max_time,
          int max_nodes, int *stop, int *bestmove);

int get_halfMoveClock(Board board);
int get_castles(Board board);

#endif /* CHESSAINT_INCLUDE_ASTAR_H_ */

