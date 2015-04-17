/* This file is part of the ChessAInt project 2015 */

#include <stdlib.h>
#include <stdio.h>

#include "include/uci.h"

int main() {
  setbuf(stdout, NULL);

  char* logPath = "uciLogs.txt";

  FILE* log = NULL;
  log = fopen(logPath, "w");
  if (log == NULL)
    manageErrors("can't create log file");

  struct uciRegex regexes;
  initialiseRegexes(&regexes);

  char buffer[UCI_SIZE];

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

  freeRegexes(&regexes);
  fclose(log);

  return EXIT_SUCCESS;
}

