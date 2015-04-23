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

#include "include/heuristic.h"

/**
 *  @fn Color is_mate(Board board)
 *  @brief Check if there is mat
 *  @param[in] board The board
 *  @return white/black If the specified king is mate
 *  @return neutral If no king is mate
 *
 *  @bug function not working until kingMoveGenerator is not taking
 *  chess position into account
 *
 *  This function check if there is a mate in the 
 *  configuration displayed by the board
 *
 */

Color is_mate(Board board) {
  Stack white_king_moves;
  Stack black_king_moves;
  stack_init(&white_king_moves);
  stack_init(&black_king_moves);
  
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      if (board.square[i][j].piece == king) {
        if (board.square[i][j].color == white)
          kingMoveGenerator(&white_king_moves, i, j, white, board);
        else
          kingMoveGenerator(&black_king_moves, i, j, black, board);
      }
    }
  }
  if (stack_pop(&white_king_moves) == -1)
    return white;
  else if (stack_pop(&black_king_moves) == -1)
    return black;
  else
    return neutral;
}

/**
 *  @fn int heuristic(Board* board)
 *  @brief Returns a score for a given board
 *  @param[in] board The representation of the board
 *  @return [|-500;500|] The value of the computed score if working well
 *  
 *  Given a board, this function compute a score
 *  giving an idea of which player has an advantage this turn and tries to
 *  quantify it.
 *
 *  @todo Add the capacity to halve the score of a piece if endangered by
 *  another (currently, test is failed)
 *
 */

int heuristic(Board* board) {
  int i, j;
  int score = 0;
  int scoreindex[ROWCOL_NB][ROWCOL_NB];
  
  /* Returns 500 or -500 directly if one of the kings is mat */
  if (is_mate(*board) != neutral) {
    if (is_mate(*board) == board->activeColor)
      return -500;
    else
      return 500;
  }
  
  /* Computes the score for each square of the board */
  for (i = 0; i < 8; ++i) {
    for (j = 0; j < 8; ++j) {
      switch (board->square[i][j].piece) {
      case empty:
        scoreindex[i][j] = 0;
        break;
      case pawn:
        scoreindex[i][j] = 10;
        break;
      case rook:
        scoreindex[i][j] = 50;
        break;
      case knight:
        scoreindex[i][j] = 30;
        break;
      case bishop:
        scoreindex[i][j] = 30;
        break;
      case queen:
        scoreindex[i][j] = 70;
        break;
      case king:
        scoreindex[i][j] = 130;
        break;
      }
      if (board->activeColor != board->square[i][j].color)
        scoreindex[i][j] *= -1;
    }
  }

  /* Sums all the scores to obtain the score of the board */
  for (i = 0; i < 8; ++i)
    for (j = 0; j < 8; ++j)
      score += scoreindex[i][j];

  return score;
}
