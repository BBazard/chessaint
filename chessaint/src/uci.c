/* This file is part of the ChessAInt project 2015 */

/**
 * @file
 * @todo handle error with a real stderr file
 * @todo create functions to open/close files
 * @todo parse uci strings
 */

#include "include/uci.h"

#include <stdlib.h>
#include <string.h>

/**
 * Print an error message
 * and stop the engine
 * 
 * @todo stop the engine
 * with uci "quit" or something
 */
void manageErrors(char *msg) {
  fprintf(stderr, "%s", msg);
  exit(EXIT_FAILURE);
}

/**
 * Send uci string to the gui
 */
void send(FILE* log, char buffer[BUFFER_SIZE]) {
  printf("%s\n", buffer);
  // extra padding spaces to align display
  fprintf(log, "sent to gui       : %s\n", buffer);
}

/**
 * Receive uci string from the gui
 * and put it in the variable buffer
 */
void receive(FILE* log, char buffer[BUFFER_SIZE]) {
  if (!fgets(buffer, BUFFER_SIZE, stdin))
    manageErrors("can't read");

  fprintf(log, "received from gui : %s", buffer);
}

