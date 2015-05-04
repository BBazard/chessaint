/* This file is part of the ChessAInt project 2015 */
/**
 *  @file
 *
 *  Astar computation algorithm header
 *
 */

#ifndef CHESSAINT_INCLUDE_ASTAR_H_
#define CHESSAINT_INCLUDE_ASTAR_H_

#include "./heuristic.h"

void move_to_node(int move, Arc father, Arc *current);
void next_gen(Graph *graph);

int get_halfMoveClock(Board board);
int get_castles(Board board);

#endif /* CHESSAINT_INCLUDE_ASTAR_H_ */
