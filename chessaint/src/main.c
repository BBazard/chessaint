/* This file is part of the ChessAInt project 2015 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "include/uci.h"
#include "include/loopuci.h"
#include "include/graph.h"

int main() {
  setbuf(stdout, NULL);

  char* logPath = "uciLogs.txt";

  FILE* log = NULL;
  log = fopen(logPath, "w");
  if (log == NULL)
    manageErrors("can't create log file");

  srand(time(NULL));

  char buffer[UCI_SIZE] = "";

  Graph graph;
  graph_alloc(&graph);

  while (uciLoop(log, buffer, &graph)) {}

  graph_free(&graph);
  fclose(log);

  return EXIT_SUCCESS;
}

