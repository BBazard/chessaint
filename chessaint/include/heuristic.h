/* This file is part of the ChessAInt project 2015 */
/** 
 *  @file
 */

#ifndef CHESSAINT_INCLUDE_HEURISTIC_H_
#define CHESSAINT_INCLUDE_HEURISTIC_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "include/graph.h"

Color is_mate(Board board);

void update_threat(int index[][ROWCOL_NB], Color threat, Board board);

void update_protection(int threat[][ROWCOL_NB], int index[][ROWCOL_NB],
                       Color protection, Board board);

int heuristic(Board board);

#endif /* CHESSAINT_INCLUDE_HEURISTIC_H_ */

