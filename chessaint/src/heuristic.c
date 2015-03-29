/*This file is part of the ChessAInt project 2015*/
/** 
 *  @file heuristic.c
 *  @brief heuristic functions
 *
 *  This file implements functions to compute the score of a position of
 *  the board at a given time, in order to quantify the advantage of one
 *  of the players and finally help the astar algorithm to choose the best
 *  move
 *
 */

#include "../include/heuristic.h"

/** 
 *  @fn int number_of_char(char *str, char chr)
 *  @brief Computes the number of char in a string
 *  @param[in] str The string in which to search
 *  @param[in] piece The char to search
 *  @return The number of character obtained
 *
 *  This function computes the number of char chr in the char *str.
 *
 */

int number_of_char(char *str, char chr) {
  char *ret = NULL;
  if ( (ret = strchr(str,chr)) == NULL)
    return 0;
  else 
    return number_of_char(ret+1, chr) + 1;
}

/** 
 *  @fn int heuristic_fen(char* fen)
 *  @brief Returns a score for a given board
 *  @param[in] fen The representation of the board
 *  @return [|-500;500|] The value of the computed score if working well
 *  @return 501 The char* is not a FEN
 *  @return 502 The FEN is not correct (Ex : 9 pawns)
 *
 *  Given a board, in a FEN string format, this function compute a score
 *  giving an idea of which player has an advantage this turn and tries to
 *  quantify it.
 *
 */

int heuristic_fen(char* fen) {
  char delim[2] = " ";
  char copy[strlen(fen)];
  char *board;
  strcpy(copy,fen);
  board = strtok(copy, delim);

  int i = 0;
  int score = 0;

  char* chrret = NULL;

  int turn = 1;
  if ( (chrret = strchr(fen,' ')) == NULL )
    return 501;
  else if (*(chrret+1) == 'b')
    turn = -1;
  else if (*(chrret+1) != 'w')
    return 501; 

  for (i = 0; i < strlen(board); i++) {
    switch (board[i]) {
    case 'k':
      score -= turn * 90;
      break;
    case 'K':
      score += turn * 90;
      break;
    case 'q':
      score -= turn * 50;
      break;
    case 'Q':
      score += turn * 50;
      break;
    case 'b':
      score -= turn * 30;
      break;
    case 'B':
      score += turn * 30;
      break;
    case 'n':
      score -= turn * 40;
      break;
    case 'N':
      score += turn * 40;
      break;
    case 'r':
      score -= turn * 30;
      break;
    case 'R':
      score += turn * 30;
      break;
    case 'p':
      score -= turn * 20;
      break;
    case 'P':
      score += turn * 20;
      break;
    }
  }      
  return score; 
}
