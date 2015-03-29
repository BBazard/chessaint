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
 *  @fn int is_mat(char *board, char player)
 *  @brief Check if there is mat
 *  @param[in] board The string representing the board
 *  @param[in] player The char representing the player
 *  @return 1 If king of the specified player is mat
 *  @return 0 Otherwise
 *  @bug THIS IS A FAKE FUNCTION TO COMPLIE WITH TEST
 *  @todo Create a true version of this function
 *
 *  This function check if the king of the player specified by parameter
 *  player is mat in the configuration displayed by parameter board
 *
 */

int is_mat(char *board, char player) {
  char* mat = "6rk/4pq2/3r4/8/8/8/8/B5KR";
  if (strcmp(mat, board) == 0 && player == 'b')
    return 1;
  else
    return 0;
}

/** 
 *  @fn int number_of_char(char *str, char chr)
 *  @brief Computes the number of char in a string
 *  @param[in] str The string in which to search
 *  @param[in] chr The char to search
 *  @return The number of character obtained
 *
 *  This function computes the number of char chr in the char *str.
 *
 */

int number_of_char(char *str, char chr) {
  char *ret = NULL;
  if ((ret = strchr(str, chr)) == NULL)
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
 *  @bug When trying to replace strtok by strtok_r, seg fault, strtok_r seems
 *  undefined (Wimplicit)
 *
 *  @todo Try to replace strtok by strtok_r, better for threading
 *  (source : cpplint)
 *
 *  @todo Add the capacity to halve the score of a piece if endangered by
 *  another (currently, test is failed)
 *
 */

int heuristic_fen(char* fen) {
  int i = 0;
  int score = 0;
  int turn = 1;

  char* chrret = NULL;
  char copy[strlen(fen)];
  char *board;

  /* Check the FEN contains at least a space and that the first space
     is followed by 'b' or 'w' */
  if ( (chrret = strchr(fen, ' ')) == NULL )
    return 501;
  else if (*(chrret+1) == 'b')
    turn = -1;
  else if (*(chrret+1) != 'w')
    return 501;

  /* Copy the original FEN and take only the first part,
     containing the board informations */
  strcpy(copy, fen);
  board = strtok(copy, " ");

  /* Check there is exactly 8 rows and never more pieces than possible */
  if (number_of_char(board, 'p') > 8 ||
      number_of_char(board, 'P') > 8 ||
      number_of_char(board, 'r') > 2 ||
      number_of_char(board, 'R') > 2 ||
      number_of_char(board, 'n') > 2 ||
      number_of_char(board, 'N') > 2 ||
      number_of_char(board, 'b') > 2 ||
      number_of_char(board, 'B') > 2 ||
      number_of_char(board, 'q') > 1 ||
      number_of_char(board, 'Q') > 1 ||
      number_of_char(board, 'k') > 1 ||
      number_of_char(board, 'K') > 1 ||
      number_of_char(board, '/') != 7)
    return 502;

  /* Returns 500 or -500 directly if one of the kings is mat */
  if (is_mat(board, 'w'))
    return turn * -500;
  else if (is_mat(board, 'b'))
    return turn * 500;

  /* Computes the score by adding the different values of each piece */
  for (i = 0; (unsigned) i < strlen(board); i++) {
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
