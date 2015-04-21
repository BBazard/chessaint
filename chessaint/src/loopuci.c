/* This file is part of the ChessAInt project 2015 */

/**
 * @file
 * @todo handle error with a real stderr file
 * @todo create functions to open/close files
 * @todo parse uci strings
 */

#include "include/loopuci.h"

#include "include/uci.h"
#include "include/graph.h"

/**
 * receive a uci string and act accordingly
 *
 * @return 0 if the gui stop
 * @return 1 otherwise
 */
int uciLoop(FILE* log, char* buffer) {
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
        // updateBoard(&graph.root, word);
        word = getNextWord();
      }
        // todo : remove the '\n'
        // then : updateBoard(&graph.root, word);

  } else if (strcmp(firstWord, "go") == 0) {
      // ignore all these parameters but assume they exist
      word = getNextWord();  // "wtime"
      word = getNextWord();  // number
      word = getNextWord();  // "btime"
      word = getNextWord();  // number
      word = getNextWord();  // "movestogo"
      word = getNextWord();  // number

      movesGenerator(&graph);

      // todo : use stack_pop(&graph.current_moves)) to play a move

      // hack to change the move each turn
      static int count = 0;
      ++count;
      if (count % 8 == 1)
        send(log, "bestmove a7a6");
      else if (count % 8 == 2)
        send(log, "bestmove b7b6");
      else if (count % 8 == 3)
        send(log, "bestmove c7c6");
      else if (count % 8 == 4)
        send(log, "bestmove d7d6");
      else if (count % 8 == 5)
        send(log, "bestmove e7e6");
      else if (count % 8 == 6)
        send(log, "bestmove f7f6");
      else if (count % 8 == 7)
        send(log, "bestmove g7g6");
      else
        send(log, "bestmove h7h6");

  } else if (strcmp(firstWord, "quit\n") == 0) {
      return 0;
  } else {}
      return 1;
}

