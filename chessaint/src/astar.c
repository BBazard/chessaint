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
 *  the arc MUST be initialized before
 *  @param[in] oldboard the board at the father state
 *
 *  This function computes the new value of score and data of a
 *  son arc.
 *
 */

void move_to_node(int move, Arc father, Arc *current, Board oldboard) {
  Stack tmp;
  stack_alloc(&tmp);
  Board newboard = oldboard;
  int father_stat = identifier_to_stack(*(father.data), &tmp);

  stack_push(&tmp, move);

  father_stat = (father_stat + 100000) % 200000 + 1;
  stack_to_identifier(current->data, tmp, father_stat);

  play_move(move, &newboard);
  current->score = heuristic(newboard);
  stack_free(&tmp);
}

/**
 *  @fn void next_gen(Graph *graph)
 *  @brief Expand next generation of moves
 *  @param[in,out] graph the graph needed to computation
 *
 *  This function choose the father with the best current score and
 *  then computes all the possible moves from this position.
 *  Computed moves are then added to the llist
 *
 *  @bug if a father stay the "best" node to choose ie the top node
 *  of the list, this algorithm will create the same node every time
 *  @note father needs no init AND MUST NOT BE FREED
 *  @note father score is put to -501 when processed to avoid previously
 *  spotted buggy situation (like putting it in a closed set for astar)
 *  @todo perhaps find a better way to correct previous note
 *
 */

void next_gen(Graph *graph) {
  Arc father;
  father = (graph->links)->value;
  llist_suppr(&(graph->links));
  father.score = -501;
  llist_add(father, &(graph->links));

  Arc son;
  arc_alloc(&son);

  int move = 0;

  graph->current_node = graph->root;
  update_board(father, &(graph->current_node));

  movesGenerator(graph);
  move = stack_pop(&(graph->current_moves));
  while (move != -1) {
    move_to_node(move, father, &son, graph->current_node);
    llist_add(son, &(graph->links));
    move = stack_pop(&(graph->current_moves));
  }

  arc_free(&son);
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
