/* This file is part of the ChessAInt project 2015 */

/**
 * @file
 * @todo handle error with a real stderr file
 * @todo create functions to open/close files
 * @todo parse uci strings
 */

#include "include/loopuci.h"

#include <time.h>

#include "include/uci.h"
#include "include/graph.h"
#include "include/concatenate.h"

/**
 * receive a uci string and act accordingly
 *
 * @return 0 if the gui stop
 * @return 1 otherwise
 */
int uciLoop(FILE* log, char* buffer) {
  char uciBuffer[5] = "zzzz";
  char* word = NULL;
  Graph graph;
  graph_init(&graph);

  receive(log, buffer);
  char* firstWord = getFirstWord(buffer);
  // strcmp second parameter
  // should end with \n if the word is the only one
  if (strcmp(firstWord, "uci\n") == 0) {
      send(log, "id name ChessAInt");
      send(log, "uciok");
  } else if (strcmp(firstWord, "isready\n") == 0) {
      send(log, "readyok");
  } else if (strcmp(firstWord, "ucinewgame\n") == 0) {
  } else if (strcmp(firstWord, "position") == 0) {
      word = getNextWord();  // "startpos"

      initAGame(&graph.root);

      word = getNextWord();  // "moves"

      word = getNextWord();  // the first move


      while (getLastCharacter(word) != '\n') {
        // updateBoard
        play_move(uciToMove(word), &graph.root);

        word = getNextWord();
      }

      rmUCILastCharacter(word, uciBuffer);
      // updateBoard
      play_move(uciToMove(word), &graph.root);

  } else if (strcmp(firstWord, "go") == 0) {
      // ignore all these parameters but assume they exist
      word = getNextWord();  // "wtime"
      word = getNextWord();  // number
      word = getNextWord();  // "btime"
      word = getNextWord();  // number
      word = getNextWord();  // "movestogo"
      word = getNextWord();  // number

      graph.current_node = graph.root;
      graph.current_node.activeColor = black;
      movesGenerator(&graph);

      srand(time(NULL));
      int rd = rand() % 10;

      int move = 0;
      for (int i = 0 ; i < rd + 1 ; ++i)
        move = stack_pop(&graph.current_moves);

      // todo : convert move from integer to "a3g6"-like string
      // printf("move o #%d#\n", move);
      int a = move / 1000;
      int b = (move / 100) % 10;
      int c = (move / 10) % 10;
      int d = move % 10;
      // printf("abcd #%d %d %d %d#\n", a, b, c, d);
      getUciString(a, b, c, d, uciBuffer);

      // printf("string o #%s#\n", uciBuffer);

      char bestmoveString[20];
      strcpy(bestmoveString, "bestmove ");
      strcat(bestmoveString, uciBuffer);

      // printf("string 2 o #%s#\n", bestmoveString);

      send(log, bestmoveString);

  } else if (strcmp(firstWord, "quit\n") == 0) {
      return 0;
  } else {}
      return 1;
}

