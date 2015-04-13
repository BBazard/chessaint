/* This file is part of the ChessAInt project 2015 */

#include "include/uci.h"

#include <stdlib.h>
#include <stdio.h>

int main() {
  setbuf(stdout, NULL);

  char* logPath = "uciLogs.txt";

  FILE* log = NULL;
  log = fopen(logPath, "w");
  if (log == NULL)
    manageErrors("can't create log file");

  char buffer[BUFFER_SIZE];

  receive(log, buffer); /* "uci" */
  /* optional */
  send(log,                "id name ChessAInt");
  send(log,                "uciok");
  receive(log, buffer); /* "isready" */
  send(log,                "readyok");
  receive(log, buffer); /* "ucinewgame" */
  receive(log, buffer); /* "position <fen> moves <lan>" */
  /* gui wait for at least an option */
  send(log,                "option quelconque");
  receive(log, buffer); /* "go <params>" */
  send(log,                "bestmove f7f6");
  receive(log, buffer); /* "quit"        */

  fclose(log);

  return EXIT_SUCCESS;
}

