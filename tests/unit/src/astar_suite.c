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
  Arc test;
  Graph graph;


  graph_init(&graph);
  initAGame(&graph.root);
  graph.current_node = graph.root;

  arc_init(&father);
  arc_init(&son);
  arc_init(&test);

  /* Need to create a correct value for data (taking care of opponents moves) */

  mpz_set_str(father.data, "404154534142100000", 10);
  update_board(father, &graph);
  father.score = heuristic(graph.current_node);

  mpz_set_str(test.data, "4041545341420703000001", 10);
  update_board(test, &graph);
  test.score = heuristic(graph.current_node);

  move_to_node(move, father, &son);

  CU_ASSERT_EQUAL(son.score, test.score)
}
