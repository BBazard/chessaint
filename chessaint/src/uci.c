/* This file is part of the ChessAInt project 2015 */

/**
 * @file
 * @todo handle error with a real stderr file
 * @todo create functions to open/close files
 * @todo parse uci strings
 */

#include "include/uci.h"
#include <string.h>
#include <sys/types.h>

/**
 * Print an error message
 * and stop the engine
 *
 * @todo stop the engine
 * with uci "quit" or something
 */
void manageErrors(char *msg) {
  fprintf(stderr, "Error ! Details : %s", msg);
  exit(EXIT_FAILURE);
}

/**
 * Send uci string to the gui
 */
void send(FILE *log, char buffer[UCI_SIZE]) {
  printf("%s\n", buffer);
  if (log != NULL)
    // extra padding spaces to align display
    fprintf(log, "sent to gui       : %s\n", buffer);
}

/**
 * Receive uci string from the gui
 * and put it in the variable buffer
 */
void receive(FILE *log, char buffer[UCI_SIZE]) {
  if (!fgets(buffer, UCI_SIZE, stdin))
    manageErrors("can't read");
  if (log != NULL)
    fprintf(log, "received from gui : %s", buffer);
}

/**
 * return the first word of a string
 *
 * * if the string contains no whitespace, return the string
 * * if the string contains at least a whitespace,
 * return the first characters until the first whitespace excluded
 *
 * example :
 * "word" -> "word"
 * "long sentence" -> "long"
 * 
 * @see getNextWord
 */
char* getFirstWord(char* sentence) {
  return strtok(sentence, " ");
}

/**
 * apply getFirstWord on the last string
 * called by getFistWord minus the return value of getFirstWord
 * 
 * examples :
 * getFirstWord("very long sentence") -> "very"
 * getNextWord() : "long"
 *
 * @see getFirstWord
 */
char* getNextWord() {
  return strtok(NULL, " ");
}

char getLastCharacter(char* input) {
  char *bla = input + strlen(input) - 1;
  return *bla;
}

