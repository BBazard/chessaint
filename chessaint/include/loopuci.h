/* This file is part of the ChessAInt project 2015 */
/**
 *  @file
 */
#ifndef CHESSAINT_INCLUDE_LOOPUCI_H_
#define CHESSAINT_INCLUDE_LOOPUCI_H_

#include <stdio.h>
#include <stdlib.h>

#include "include/graph.h"

int pickBestMove(Stack *current_moves);

int uciLoop(FILE* log, char* buffer, Graph *graph);

#endif /* CHESSAINT_INCLUDE_LOOPUCI_H_ */

