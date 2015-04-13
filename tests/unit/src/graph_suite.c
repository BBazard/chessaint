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
  printf("\n---------------------------------\n");
  Board testBoardB;
  printf("\n**Say a board with only a white bishop on e4[<=>(4,3)");
  printf(" in our system], a white pawn on d5<=>(3,4)\n");
  printf(" and a black rook on f3<=>(5,2)**\n");
  fenToBoard("8/8/8/3P4/4B3/5r2/8/8 w - - 0 1", &testBoardB);
  /* Enable to see the situation :
  printBoardAndData(testBoardB);
  */
  printf("The moves of the bishop are :\n");

  bishopMoveGenerator(4, 3, white, testBoardB);
}

void test_rookMoveGenerator(void) {
  printf("\n---------------------------------\n");
  Board testBoardR;
  printf("\n**Say we have a black rook on e4<=>(4,3), a black pawn");
  printf(" on e5<=>(4,4) and a white rook on b4<=>(0,3)**\n");
  fenToBoard("8/8/8/4p3/1R2r3/8/8/8 b - - 0 1", &testBoardR);
  /* Enable to see the situation :
  printBoardAndData(testBoardR);
  */
  printf("The moves of the rook are :\n");

  rookMoveGenerator(4, 3, black, testBoardR);
}

void test_queenMoveGenerator(void) {
  printf("\n---------------------------------\n");
  Board testBoardQ;
  printf("\n**Say we have a white queen on e4<=>(4,3), a black knight");
  printf(" on f5<=>(5,4) and a white pawn on e2<=>(4,1)**");
  fenToBoard("8/8/8/5n2/4Q3/8/4P3/8 w - - 0 1", &testBoardQ);
  /* Enable to see the situation :
  printBoardAndData(testBoardQ);
  */
  printf("The moves of the queen are :\n");

  queenMoveGenerator(4, 3, white, testBoardQ);
}

void test_knightMoveGenerator(void) {
  printf("\n---------------------------------\n");
  Board testBoardN;
  printf("\n**Say we have a white knight on e4<=>(4,3), a black pawn ");
  printf("on f6<=>(5,5) and a white king on d2<=>(3,1)**");
  fenToBoard("8/8/5p2/8/4N3/8/3K4/8 w - - 0 1", &testBoardN);
  /* Enable to see the situation :
  printBoardAndData(testBoardN);
  */
  printf("The moves of the knight are :\n");

  knightMoveGenerator(4, 3, white, testBoardN);
}
void test_kingMoveGenerator(void) {
  printf("\n---------------------------------\n");
  Board testBoardK;
  printf("\n**Say we have a black king on e4<=>(4,3), with black");
  printf("pawns all around except in f5<=>(5,4) (empty) and");
  printf("in d3<=>(3,2) (white pawn)**");
  fenToBoard("8/8/8/3pp3/3pkp2/3Ppp2/8/8 b - - 0 1", &testBoardK);
  /* Enable to see the situation :
  printBoardAndData(testBoardK);
  */
  printf("The moves of the king are :\n");

  kingMoveGenerator(4, 3, black, testBoardK);
}

void test_pawnMoveGenerator1(void) {
  printf("\n---------------------------------\n");
  Board testBoardP;
  printf("\n**Say we have a white pawn on a2<=>(0,1) with a black knight");
  printf("on b3<=>(1,2)**");
  fenToBoard("8/8/8/8/8/1n6/P7/8 w - - 0 1", &testBoardP);
  /* Enable to see the situation :
  printBoardAndData(testBoardP);
  */
  printf("The moves of the pawn are :\n");

  pawnMoveGenerator(0, 1, white, testBoardP);
}

void test_pawnMoveGenerator2(void) {
  printf("\n---------------------------------\n");
  Board testBoardP2;
  printf("\n**Say we have a black pawn on e4<=>(4,3) with a white pawn");
  printf("on d4<=>(3,3) so that d2<=>(3,2) can be taken en passant**");
  fenToBoard("8/8/8/8/3Pp3/8/8/8 b - d3 0 1", &testBoardP2);
  /* Enable to see the situation :
  printBoardAndData(testBoardP2);
  */
  printf("The moves of the pawn are :\n");

  pawnMoveGenerator(4, 3, black, testBoardP2);
}

void test_movesGenerator(void) {
  Graph testGraph;
  Board testRoot, testCurrentNode;
  Llist testLinks = NULL;
  printf("\n ---------------------------------\n");
  printf("\n**We want all moves from the beginning position :**");
  initAGame(&testRoot);
  initAGame(&testCurrentNode);
  testGraph.root = testRoot;
  testGraph.current_node = testCurrentNode;
  testGraph.links = testLinks;
  printBoardAndData(testRoot);
  movesGenerator(testGraph);
}

