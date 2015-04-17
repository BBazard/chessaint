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

struct uciRegex {
  regex_t bla;
};

void manageErrors(char *msg);

void regcompWrapper(regex_t *compiled, char *pattern);

int regexecWrapper(const regex_t *compiled, const char *string,
                   regmatch_t *matchptr);

void send(FILE* log, char buffer[UCI_SIZE]);

void receive(FILE* log, char buffer[UCI_SIZE]);

void initialiseRegexes(struct uciRegex *regexes);
void freeRegexes(struct uciRegex *regexes);

int isQuit(FILE *log, char toCompare[UCI_SIZE]);

#endif /*TRUNK_CHESSAINT_INCLUDE_UCI_H_*/

