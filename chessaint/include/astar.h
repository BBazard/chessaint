/*This file is part of the ChessAInt project 2015*/
#ifndef TRUNK_CHESSAINT_INCLUDE_ASTAR_H_
#define TRUNK_CHESSAINT_INCLUDE_ASTAR_H_

#include <stdlib.h>
#include <stdio.h>

#include "./heuristic.h"

void move_to_node(int move, Arc father, Arc *current);
void next_gen(Graph *graph);

#endif /*TRUNK_CHESSAINT_INCLUDE_ASTAR_H_*/
