/* This file is part of the ChessAInt project 2015 */

#include "CUnit/Basic.h"
#include "include/graph.h"

/* The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite_graph(void) {
/*
 *   if (problem during initialisation)
 *     return -1; // this number can be used to explicit the problem
 */
  return 0;
}

/* The suite cleanup function.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite_graph(void) {
/*
 *   if (problem during cleaning)
 *     return -1; // this number can be used to explicit the problem
 */
  return 0;
}

void test_isInBoardSquare(void) {
  CU_ASSERT_TRUE(isInBoardSquare(0, 0));
  CU_ASSERT_TRUE(isInBoardSquare(7, 7));
  CU_ASSERT_TRUE(isInBoardSquare(7, 5));

  CU_ASSERT_FALSE(isInBoardSquare(0, 8));
  CU_ASSERT_FALSE(isInBoardSquare(8, 0));
  CU_ASSERT_FALSE(isInBoardSquare(-1, 0));
}

void test_bishopMoveGenerator(void) {
  Board testBoardB;
  Stack tmp;
  stack_init(&tmp);

  /* Say a board with only a white bishop on e4[<=>(4,3)");
   in our system], a white pawn on d5<=>(3,4)\n");
   and a black rook on f3<=>(5,2)**\n") */

  fenToBoard("8/8/8/3P4/4B3/5r2/8/8 w - - 0 1", &testBoardB);

  /* Enable to see the situation : printBoardAndData(testBoardB); */


  bishopMoveGenerator(&tmp, 4, 3, white, testBoardB);
  /* (4,3) -> (0,7) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4307);
  /* (4,3) -> (1,6) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4316);
  /* (4,3) -> (2,5) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4325);
  /* (4,3) -> (3,4) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4334);
  /* (4,3) -> (1,0) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4310);
  /* (4,3) -> (2,1) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4321);
  /* (4,3) -> (3,2) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4332);
  /* (4,3) -> (7,0) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4370);
  /* (4,3) -> (6,1) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4361);
  /* (4,3) -> (5,2) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4352);
  /* (4,3) -> (7,6) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4376);
  /* (4,3) -> (6,5) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4365);
  /* (4,3) -> (5,4) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4354);
}

void test_rookMoveGenerator(void) {
  Board testBoardR;
  Stack tmp;
  stack_init(&tmp);

  /* Say we have a black rook on e4<=>(4,3), a black pawn");
   on e5<=>(4,4) and a white rook on b4<=>(0,3)**\n"); */

  fenToBoard("8/8/8/4p3/1R2r3/8/8/8 b - - 0 1", &testBoardR);

  /* Enable to see the situation   printBoardAndData(testBoardR); */

  rookMoveGenerator(&tmp, 4, 3, black, testBoardR);

  /* (4,3) -> (0,3) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4303);
  /* (4,3) -> (1,3) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4313);
  /* (4,3) -> (2,3) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4323);
  /* (4,3) -> (3,3) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4333);
  /* (4,3) -> (7,3) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4373);
  /* (4,3) -> (6,3) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4363);
  /* (4,3) -> (5,3) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4353);
  /* (4,3) -> (4,0) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4340);
  /* (4,3) -> (4,1) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4341);
  /* (4,3) -> (4,2) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4342);
}

void test_queenMoveGenerator(void) {
  Board testBoardQ;
  Stack tmp;
  stack_init(&tmp);

  /* Say we have a white queen on e4<=>(4,3), a black knight");
   on f5<=>(5,4) and a white pawn on e2<=>(4,1)**"); */

  fenToBoard("8/8/8/5n2/4Q3/8/4P3/8 w - - 0 1", &testBoardQ);

  /* Enable to see the situation :
  printBoardAndData(testBoardQ);
  */

  queenMoveGenerator(&tmp, 4, 3, white, testBoardQ);

  /* (4,3) -> (0,3) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4303);
  /* (4,3) -> (1,3) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4313);
  /* (4,3) -> (2,3) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4323);
  /* (4,3) -> (3,3) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4333);
  /* (4,3) -> (5,3) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4353);
  /* (4,3) -> (4,0) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4340);
  /* (4,3) -> (4,1) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4341);
  /* (4,3) -> (4,2) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4342);
  /* (4,3) -> (0,7) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4307);
  /* (4,3) -> (1,6) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4316);
  /* (4,3) -> (2,5) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4325);
  /* (4,3) -> (3,4) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4334);
  /* (4,3) -> (1,0) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4310);
  /* (4,3) -> (2,1) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4321);
  /* (4,3) -> (3,2) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4332);
  /* (4,3) -> (7,0) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4370);
  /* (4,3) -> (6,1) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4361);
  /* (4,3) -> (5,2) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4352);
  /* (4,3) -> (7,6) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4376);
  /* (4,3) -> (6,5) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4365);
  /* (4,3) -> (5,4) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4354);
}

void test_knightMoveGenerator(void) {

  Board testBoardN;
  Stack tmp;
  stack_init(&tmp);

  /* Say we have a white knight on e4<=>(4,3), a black pawn 
     on f6<=>(5,5) and a white king on d2<=>(3,1) */

  fenToBoard("8/8/5p2/8/4N3/8/3K4/8 w - - 0 1", &testBoardN);

  /* Enable to see the situation : printBoardAndData(testBoardN); */

  knightMoveGenerator(&tmp, 4, 3, white, testBoardN);

  /* (4,3) -> (2,2) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4322);
  /* (4,3) -> (2,4) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4324);
  /* (4,3) -> (5,1) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4351);
  /* (4,3) -> (3,1) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4331);
  /* (4,3) -> (6,2) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4362);
  /* (4,3) -> (6,4) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4364);
  /* (4,3) -> (3,5) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4335);
  /* (4,3) -> (5,5) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4355);
}

void test_kingMoveGenerator(void) {
  Board testBoardK;
  Stack tmp;
  stack_init(&tmp);

  /* Say we have a black king on e4<=>(4,3), with black pawns 
     all around except in f5<=>(5,4) (empty) and in d3<=>(3,2) (white pawn) */

  fenToBoard("8/8/8/3pp3/3pkp2/3Ppp2/8/8 b - - 0 1", &testBoardK);

  /* Enable to see the situation : printBoardAndData(testBoardK); */

  kingMoveGenerator(&tmp, 4, 3, black, testBoardK);

  /* (4,3) -> (3,2) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4332);
  /* (4,3) -> (5,2) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4352);
  /* (4,3) -> (4,2) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4342);
  /* (4,3) -> (5,3) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4353);
}

void test_pawnMoveGenerator1(void) {
  Board testBoardP;
  Stack tmp;
  stack_init(&tmp);

  /* Say we have a white pawn on a2<=>(0,1) with a black knight on b3<=>(1,2) */

  fenToBoard("8/8/8/8/8/1n6/P7/8 w - - 0 1", &testBoardP);

  /* Enable to see the situation : printBoardAndData(testBoardP); */

  pawnMoveGenerator(&tmp, 0, 1, white, testBoardP);

  /* (0,1) -> (0,3) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 103);
  /* (0,1) -> (0,2) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 102);
}

void test_pawnMoveGenerator2(void) {
  Board testBoardP2;
  Stack tmp;
  stack_init(&tmp);

  /* Say we have a black pawn on e4<=>(4,3) with a white pawn
     on d4<=>(3,3) so that d2<=>(3,2) can be taken en passant */

  fenToBoard("8/8/8/8/3Pp3/8/8/8 b - d3 0 1", &testBoardP2);

  /* Enable to see the situation : printBoardAndData(testBoardP2); */

  pawnMoveGenerator(&tmp, 4, 3, black, testBoardP2);

  /* (4,3) -> (3,2) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4332);
  /* (4,3) -> (4,2) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4342);
}

void test_movesGenerator(void) {
  Graph testGraph;
  graph_init(&testGraph);
  
  /* We want all moves from the beginning position */
  initAGame(&(testGraph.root));
  initAGame(&(testGraph.current_node));

  movesGenerator(&testGraph);

  /* (0,0) -> (1,0) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 10);
  /* (0,0) -> (0,1) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 1);
  /* (1,0) -> (3,1) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 1031);
  /* (1,0) -> (0,2) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 1002);
  /* (1,0) -> (2,2) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 1022);
  /* (2,0) -> (1,1) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 2011);
  /* (2,0) -> (3,1) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 2031);
  /* (3,0) -> (2,1) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 3021);
  /* (3,0) -> (4,1) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 3041);
  /* (3,0) -> (2,0) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 3020);
  /* (3,0) -> (4,0) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 3040);
  /* (3,0) -> (3,1) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 3031);
  /* (4,0) -> (3,0) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 4030);
  /* (4,0) -> (5,0) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 4050);
  /* (4,0) -> (4,1) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 4041);
  /* (4,0) -> (3,1) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 4031);
  /* (4,0) -> (5,1) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 4051);
  /* (5,0) -> (4,1) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 5041);
  /* (5,0) -> (6,1) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 5061);
  /* (6,0) -> (4,1) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 6041);
  /* (6,0) -> (5,2) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 6052);
  /* (6,0) -> (7,2) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 6072);
  /* (7,0) -> (6,0) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 7060);
  /* (7,0) -> (7,1) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 7071);
  /* (0,1) -> (0,3) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 103);
  /* (0,1) -> (0,2) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 102);
  /* (1,1) -> (1,3) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 1113);
  /* (1,1) -> (1,2) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 1112);
  /* (2,1) -> (2,3) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 2123);
  /* (2,1) -> (2,2) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 2122);
  /* (3,1) -> (3,3) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 3133);
  /* (3,1) -> (3,2) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 3132);
  /* (4,1) -> (4,3) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 4143);
  /* (4,1) -> (4,2) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 4142);
  /* (5,1) -> (5,3) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 5153);
  /* (5,1) -> (5,2) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 5152);
  /* (6,1) -> (6,3) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 6163);
  /* (6,1) -> (6,2) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 6162);
  /* (7,1) -> (7,3) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 7173);
  /* (7,1) -> (7,2) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 7172);
}
