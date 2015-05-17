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
  Node father;
  Node son;
  Node test;
  Graph graph;

  graph_alloc(&graph);
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

  node_alloc(&father);
  node_alloc(&son);
  node_alloc(&test);

  /* Need to create a correct value for data (taking care of opponents moves) */

  Stack stack;
  stack_alloc(&stack);
  stack_push(&stack, 4041);
  stack_push(&stack, 5453);
  stack_push(&stack, 4142);
  stack_push(&stack, 703);
  stack_to_identifier(test.data, stack, 100001);

  graph.current_node = graph.root;
  update_board(test, &graph.current_node);
  test.score = heuristic(graph.current_node);
  stack_free(&stack);

  /* printBoardAndData(graph.current_node); */

  graph.current_node = graph.root;

  stack_alloc(&stack);
  stack_push(&stack, 4041);
  stack_push(&stack, 5453);
  stack_push(&stack, 4142);
  stack_to_identifier(father.data, stack, 000000);
  stack_free(&stack);

  graph.current_node = graph.root;
  update_board(father, &graph.current_node);
  father.score = heuristic(graph.current_node);

  /* printBoardAndData(graph.current_node); */

  move_to_node(move, father, &son, graph.current_node);

  CU_ASSERT_EQUAL(son.score, test.score);

  node_free(&father);
  node_free(&son);
  node_free(&test);

  graph_free(&graph);
}

void test_next_gen(void) {
  Graph graph;
  graph_alloc(&graph);

  Node node;
  node_alloc(&node);

  Stack stack;
  stack_alloc(&stack);
  stack_push(&stack, 2);
  stack_push(&stack, 7775);
  stack_to_identifier(node.data, stack, 100002);

  /* llist_add(node, &(graph.links)); */

  /* graph is ready to be tested */
  for (int i = 0; i < 4; i++) {
    /* printf("\n\n\n"); */

    next_gen(&graph, -1);

    /* Element *tmp = graph.links; */
    /* int i = 1; */

    /* while (tmp != NULL) { */
    /*   printf("#n = %d\n", i++); */
    /*   node_print(tmp->value); */
    /*   tmp = tmp->next; */
    /* } */
  }
  CU_ASSERT_TRUE(0);
  stack_free(&stack);
  node_free(&node);
  graph_free(&graph);
}

void test_astar(void) {
  Graph graph;
  graph_alloc(&graph);

  play_move(4143, &(graph.root));

  int bestmove;
  int ret = -1;
  int stop = 0;

  ret = astar(&graph, 500, -1, 5, 150, &stop, &bestmove, NULL);
  /* works with max_nodes = 150, 
     seems that while condition always true */
  printf("## %d->%d ##", ret, bestmove);

  graph_free(&graph);
}

