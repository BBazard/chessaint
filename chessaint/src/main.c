/* This file is part of the ChessAInt project 2015 */

#include <stdlib.h>
#include <stdio.h>

#include "include/uci.h"
#include "include/loopuci.h"

int main() {
  setbuf(stdout, NULL);

  char* logPath = "uciLogs.txt";

  FILE* log = NULL;
  log = fopen(logPath, "w");
  if (log == NULL)
    manageErrors("can't create log file");

  char buffer[UCI_SIZE] = "";

  while (uciLoop(log, buffer)) {}

  fclose(log);

  return EXIT_SUCCESS;
}

