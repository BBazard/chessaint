/* This file is part of the ChessAInt project 2015 */
/**
 *  @file
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
 *  @brief Check if there is mate
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
  stack_alloc(&white_king_moves);
  stack_alloc(&black_king_moves);

  bool threatsForBlackKing[8][8];
  bool threatsForWhiteKing[8][8];

  findThreats(&board, black, threatsForBlackKing);
  findThreats(&board, white, threatsForWhiteKing);

  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      if (board.square[i][j].piece == king) {
        if (board.square[i][j].color == white)
          kingMoveGenerator(&white_king_moves, i, j, white, board,
              threatsForWhiteKing);
        else
          kingMoveGenerator(&black_king_moves, i, j, black, board,
              threatsForBlackKing);
      }
    }
  }
  if (stack_pop(&white_king_moves) == -1) {
    stack_free(&white_king_moves);
    stack_free(&black_king_moves);
    return white;
  } else if (stack_pop(&black_king_moves) == -1) {
    stack_free(&white_king_moves);
    stack_free(&black_king_moves);
    return black;
  } else {
    stack_free(&white_king_moves);
    stack_free(&black_king_moves);
    return neutral;
  }
}

/**
 *  @fn void update_threat(int index[][ROWCOL_NB], Color threat, Board board)
 *  @brief Gives the threatened places of all board
 *  @param[out] index Matrix of ints
 *  @param[in] threat The player threatening
 *  @param[in] board The current positions of pieces
 *
 *  This functions given a board and a player gives a state of what the given
 *  player threatens on the board.
 *  The result is stored as a double array of ints, the number means the
 *  number of pieces threatening the place
 *
 */

void update_threat(int index[][ROWCOL_NB], Color threat, Board board) {
  Graph graph;
  int poped;
  int p1, p2, p3, p4;
  graph_alloc(&graph);
  graph.current_node = board;
  graph.current_node.activeColor = threat;

  for (int i = 0; i < ROWCOL_NB; ++i)
    for (int j = 0; j < ROWCOL_NB; ++j)
      index[i][j] = 0;

  // todo initialise these values
  board.enPassant.line = 1234;
  board.enPassant.column = 132;

  movesGenerator(&graph);

  while ((poped = stack_pop(&(graph.current_moves))) != -1) {
    stack_expand(&p1, &p2, &p3, &p4, poped);
    if (board.square[p3][p4].color == (threat + 1) % 2)
      index[p3][p4] += 1;
  }
  graph_free(&graph);
}

void update_protection(int threat[][ROWCOL_NB], int index[][ROWCOL_NB],
                       Color protection, Board board) {
  Graph graph;
  int poped;
  int p1, p2, p3, p4;
  graph_alloc(&graph);
  graph.current_node = board;
  graph.current_node.activeColor = protection;

  for (int i = 0; i < ROWCOL_NB; ++i) {
    for (int j = 0; j < ROWCOL_NB; ++j) {
      Color *color = &(graph.current_node.square[i][j].color);
      if (*color == protection && threat[i][j] > 0) {
        index[i][j] = 0;
        *color = (protection + 1) % 2;
      } else {
        index[i][j] = -1;
      }
    }
  }

  movesGenerator(&graph);

  while ((poped = stack_pop(&(graph.current_moves))) != -1) {
    stack_expand(&p1, &p2, &p3, &p4, poped);
    if (index[p3][p4] >= 0)
      index[p3][p4] += 1;
  }
  graph_free(&graph);
}
/** @fn int heuristic(Board board)
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

#define check_mate 0

int heuristic(Board board) {
  float score = 0;
  float scoreindex[ROWCOL_NB][ROWCOL_NB];
  int white_thrIdx[ROWCOL_NB][ROWCOL_NB];
  int black_thrIdx[ROWCOL_NB][ROWCOL_NB];
  int white_proIdx[ROWCOL_NB][ROWCOL_NB];
  int black_proIdx[ROWCOL_NB][ROWCOL_NB];

  /* Returns 500 or -500 directly if one of the kings is mate */
  if (is_mate(board) != neutral && check_mate) {
    if (is_mate(board) == board.activeColor)
      return -500;
    else
      return 500;
  }

  /* Divides by 2 if a piece is threatened */
  update_threat(white_thrIdx, white, board);
  update_threat(black_thrIdx, black, board);
  update_protection(black_thrIdx, white_proIdx, white, board);
  update_protection(white_thrIdx, black_proIdx, black, board);

  /* Computes the score for each square of the board */
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      switch (board.square[i][j].piece) {
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
      /* Scores depends on the player */
      if (board.activeColor != board.square[i][j].color)
        scoreindex[i][j] *= -1;

      /* Manage threats */
      if (board.square[i][j].color == white && black_thrIdx[i][j] > 0)
        scoreindex[i][j] /= black_thrIdx[i][j]+1;
      if (board.square[i][j].color == black && white_thrIdx[i][j] > 0)
        scoreindex[i][j] /= white_thrIdx[i][j]+1;

      /* Manage protections */
      if (board.square[i][j].color == white && white_proIdx[i][j] > 0)
        scoreindex[i][j] *= white_proIdx[i][j]+1;
      if (board.square[i][j].color == black && black_proIdx[i][j] > 0)
        scoreindex[i][j] *= black_proIdx[i][j]+1;
    }
  }

  /* Sums all the scores to obtain the score of the board */
  for (int i = 0; i < 8; ++i)
    for (int j = 0; j < 8; ++j)
      score += scoreindex[i][j];

  return score;
}

