/* This file is part of the ChessAInt project 2015 */

#include "CUnit/Basic.h"
#include "include/astar.h"

/* The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 */

int init_suite_astar(void) {
/*
 *   if (problem during initialisation)
 *     return -1; // this number can be used to explicit the problem
 */
  return 0;
}

/* The suite cleanup function.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite_astar(void) {
/*
 *   if (problem during cleaning)
 *     return -1; // this number can be used to explicit the problem
 */
  return 0;
}

void test_move_to_node(void) {
  int move = 703;
  Arc father;
  Arc son;
  Board
  arc_init(&father);
  arc_init(&son);
  update_board(
  father.score = heuristic(;
  /* Need to create a correct value for data (take care of opponents moves */
  mpz_set_str(father.data, "404154534142", 10);

  move_to_node(move, father, &son);

  /* CU_ASSERT_EQUAL(son.score, heuristic( */
  
}
