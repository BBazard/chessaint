/*This file is part of the ChessAInt project 2015*/
/** 
 *  @file heuristic.h
 *  @brief heuristic function header
 *
 *  This file contains the prototypes of the functions developped
 *  in heuristic.c file
 *
 */

#ifndef TRUNK_CHESSAINT_INCLUDE_HEURISTIC_H_
#define TRUNK_CHESSAINT_INCLUDE_HEURISTIC_H_

#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

Color is_mate(Board board);
int heuristic(Board* board);

#endif /*TRUNK_CHESSAINT_INCLUDE_HEURISTIC_H_*/
