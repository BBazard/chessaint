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
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
        graph.root.square[i][j].piece = empty;
        graph.root.square[i][j].color = neutral;
    }
  }
  graph.root.square[0][7].piece = rook;
  graph.root.square[0][7].color = black;
  graph.root.square[5][4].piece = pawn;
  graph.root.square[5][4].color = black;
  graph.root.square[4][0].piece = pawn;
  graph.root.square[4][0].color = white;
  graph.root.square[7][0].piece = rook;
  graph.root.square[7][0].color = white;

  graph.current_node = graph.root;

  /* printBoardAndData(graph.current_node); */

  arc_init(&father);
  arc_init(&son);
  arc_init(&test);

  /* Need to create a correct value for data (taking care of opponents moves) */

  Stack stack;
  stack_init(&stack);
  stack_push(&stack, 4041);
  stack_push(&stack, 5453);
  stack_push(&stack, 4142);
  stack_push(&stack, 703);
  stack_to_identifier(&(test.data), stack, 100001);

  graph.current_node = graph.root;
  update_board(test, &graph.current_node);
  test.score = heuristic(graph.current_node);
  stack_free(&stack);
  
  /* printBoardAndData(graph.current_node); */
  
  graph.current_node = graph.root;

  stack_init(&stack);
  stack_push(&stack, 4041);
  stack_push(&stack, 5453);
  stack_push(&stack, 4142);
  stack_to_identifier(&(father.data), stack, 000000);
  
  graph.current_node = graph.root;
  update_board(father, &graph.current_node);
  father.score = heuristic(graph.current_node);

  /* printBoardAndData(graph.current_node); */

  move_to_node(move, father, &son, graph.current_node);

  printf("\n##%d;%d##\n", son.score, test.score);
  CU_ASSERT_EQUAL(son.score, test.score);

  arc_free(&father);
  arc_free(&son);
  arc_free(&test);

  graph_free(&graph);
}

