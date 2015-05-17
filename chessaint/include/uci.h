/* This file is part of the ChessAInt project 2015 */
/**
 *  @file
 */

#ifndef CHESSAINT_INCLUDE_UCI_H_
#define CHESSAINT_INCLUDE_UCI_H_

#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

/**
 * The maximum number of characters of a uci string
 * 
 * The worst case is "position startpos moves h2h3...g2g3..."\n
 * That is to say about (25 + 5 * maxMovesNb) characters\n
 * Let's fix maxMovesNb 200 (100 black moves and 100 white moves)
 * 
 * @todo set UCI_SIZE dynamically thanks to graph.fullMoveNb
 */
#define UCI_SIZE 1024

void manageErrors(char *msg);

void send(FILE* log, char buffer[UCI_SIZE]);

void receive(FILE* log, char buffer[UCI_SIZE]);

char* getFirstWord(char* sentence);

char* getNextWord();

char getLastCharacter(char* input);

int uciToMove(char* input);

void rmUCILastCharacter(char* input, char output[5]);

void getUciString(int a, int b, int c, int d, char str[5]);

#endif /* CHESSAINT_INCLUDE_UCI_H_ */

