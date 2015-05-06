/* This file is part of the ChessAInt project 2015 */

#include "CUnit/Basic.h"
#include "include/astar.h"

int init_suite_astar(void) {
  return 0;
}

int clean_suite_astar(void) {
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
  update_board(father, &graph.current_node);
  father.score = heuristic(graph.current_node);

  mpz_set_str(test.data, "4041545341420703000001", 10);
  update_board(test, &graph.current_node);
  test.score = heuristic(graph.current_node);

  move_to_node(move, father, &son);

  CU_ASSERT_EQUAL(son.score, test.score);

  arc_free(&father);
  arc_free(&son);
  arc_free(&test);

  graph_free(&graph);
}

