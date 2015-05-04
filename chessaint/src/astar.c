/* This file is part of the ChessAInt project 2015 */
/**
 *  @file
 *
 *  This file implements basic features of computation system (astar)
 *
 */

#include "include/astar.h"

/**
 *  @fn void move_to_node(int move, Arc father, Arc *current)
 *  @brief Create a node from a move (int) and it's father's data
 *  @param[in] move The move to convert
 *  @param[in] father The father of the arc to be
 *  @param[out] current The pointer in which to save created arc
 *
 *  This function computes the new value of score and data of a
 *  son arc.
 *
 */

void move_to_node(int move, Arc father, Arc *current) {
}

/**
 *  @fn int get_halfMoveClock(Board board)
 *  @brief return the number halfMoveClock from a board structure
 *  @param[in] board
 *  @param[out] the number halfMoveClock
 */
int get_halfMoveClock(Board board) {
  return board.halfMoveClock;
}

/**
 *  @fn int get_castles(Board board)
 *  @brief return an integer telling about the cuurent availble castles
 *
 *  @param[in] board the board in which we check castles
 *  @param[out] the formatted int
 *
 *  The int returned is formatted this way : 
 *  K*2^3 + Q*2^2 + k*2 + q with K,k,Q,q between 0 or 1
 *  if castle is available or not
 *
 *  @note : if it's 0100, the int returned is 100
 */
int get_castles(Board board) {
  char ans[4];
  for (int i = 0 ; i < 4 ; ++i) {
    if (board.availableCastlings[i] == 1)
      ans[i] = '1';
    else
      ans[i] = '0';
  }
  return atoi(ans);
}
