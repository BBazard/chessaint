/* This file is part of the ChessAInt project 2015 */
/**
 * @file
 */

#ifndef TRUNK_CHESSAINT_INCLUDE_UCI_H_
#define TRUNK_CHESSAINT_INCLUDE_UCI_H_

#include <stdio.h>

/**
 * The maximum number of characters of a uci string
 */
#define BUFFER_SIZE 256

void manageErrors(char *msg);

void send(FILE* log, char buffer[BUFFER_SIZE]);

void receive(FILE* log, char buffer[BUFFER_SIZE]);

#endif /*TRUNK_CHESSAINT_INCLUDE_UCI_H_*/
