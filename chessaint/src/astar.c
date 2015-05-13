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
  arc_alloc(&father);

  Arc son;
  arc_alloc(&son);

  Stack s;
  stack_alloc(&s);

  int move = 0;

  graph->current_node = graph->root;

  if (graph->links != NULL) {
    arc_copy((graph->links)->value, &father);
    llist_suppr(&(graph->links));

    father.score = -501;
    /* llist_add(father, &(graph->links)); /\* Add father to links *\/ */

    update_board(father, &(graph->current_node));
  }

  /* printf("##father##"); /\* to delete *\/ */
  /* arc_print(father); /\* to delete *\/ */

  /* printBoardAndData(graph->current_node); /\* to delete *\/ */

  movesGenerator(graph);
  move = stack_pop(&(graph->current_moves));

  /* printf("##move : %d##", move); /\* to delete *\/ */

  while (move != -1) {
    move_to_node(move, father, &son, graph->current_node);
    llist_add(son, &(graph->links));
    move = stack_pop(&(graph->current_moves));
  }
  /* llist_shorten(&(graph->links), 2); /\* to delete *\/ */
  arc_free(&father);
  arc_free(&son);
}

/**
 *  @fn int astar(Graph *graph, int query_score, int depth, int max_time,
 *  int max_nodes, int *stop, int *bestmove)
 *  @brief Computation of the whole graph
 *  @param[in,out] graph The graph used for computation
 *  @param[in] [-500, 500] query_score Quit astar if as score above this is found (500 = no limit)
 *  @param[in] depth The maximal depth allowed (-1 = no limit)
 *  @param[in] max_nodes The number of nodes allowed (-1 = no limit but not recommended)
 *  @param[in] stop {0,1} Stop computation if changed to 0
 *  @param[out] bestmove The current best move
 *  @return 1 If found a score better than query_score
 *  @return 2 If time limit was reached
 *  @return 4 If maximal depth was reached
 *  @return 8 If maximal number of nodes was reached
 *  @return 16 If it was asked to stop
 *  @return 32 If exited anormally
 *  @return sum of previous for multiple flags
 *
 *  Compute from the start to the end (choosen with one or several parameters)
 *  the best move possible.
 *
 *  @note Know that maximal number of nodes being x, the true max number of node could reach 1,1x
 *  take that in account when assigning it.
 *  @note Previous note not implemented yet, the true number won't excess x+1
 *
 *  @todo test is bestmove is the best
 *  @todo use depth parameter to check max depth possibilites
 *
 */

int astar(Graph *graph, int query_score, int depth, int max_time,
          int max_nodes, int *stop, int *bestmove) {
  time_t start_time = time(NULL);
  int ret = 0;
  int current_score = -501;
  *bestmove = -1;
  Llist tmp;

  int current_time = 0; /* to delete */

  while ( (current_score < query_score) && !(*stop)
          && (time(NULL) - start_time < max_time) ) {
    current_time = time(NULL) - start_time;
    printf("## %d ####\n", current_time); /* to delete */
    next_gen(graph);

    /* Get bestmove for this generation */
    tmp = graph->links;

    while (identifier_is_white(*(tmp->value.data)) == graph->root.activeColor) {
      tmp = tmp->next;
      if (tmp == NULL)
        return 32;
    }
    /* Have to test if it is the best in test_astar function */ /* to delete */
    arc_extract(tmp->value, bestmove, &current_score);

    /* Shorten list if needed */

    if (llist_shorten(&graph->links, max_nodes))
      ret = 8;
  }
  if (current_score >= query_score)
    ret = 1;
  if ((time(NULL) - start_time >= max_time))
    ret += 2;
  if (*stop)
    ret += 16;
  printf("list %d\n", llist_length(graph->links)); /* to delete */
  arc_print(graph->links->value); /* to delete */
  printf("%d", stack_length(*(graph->links->value.data))); /* to delete */
  return ret;
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

