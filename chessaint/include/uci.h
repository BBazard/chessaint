/* This file is part of the ChessAInt project 2015 */
/**
 * @file
 */
#ifndef TRUNK_CHESSAINT_INCLUDE_UCI_H_
#define TRUNK_CHESSAINT_INCLUDE_UCI_H_

#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

/**
 * The maximum number of characters of a uci string
 */
#define UCI_SIZE 256

/**
 * The size of errors buffer
 */
#define MSG_SIZE 256

void manageErrors(char *msg);

void send(FILE* log, char buffer[UCI_SIZE]);

void receive(FILE* log, char buffer[UCI_SIZE]);

char* getFirstWord(char* sentence);

char* getNextWord();

char getLastCharacter(char* input);

#endif /*TRUNK_CHESSAINT_INCLUDE_UCI_H_*/

