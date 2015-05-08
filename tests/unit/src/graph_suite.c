/* This file is part of the ChessAInt project 2015 */

#include "CUnit/Basic.h"
#include "include/graph.h"

int init_suite_graph(void) {
  return 0;
}

int clean_suite_graph(void) {
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
  stack_alloc(&tmp);

  /* Say a board with only a white bishop on e4[<=>(4,3)");
   in our system], a white pawn on d5<=>(3,4)\n");
   and a black rook on f3<=>(5,2)**\n") */

  fenToBoard("8/8/8/3P4/4B3/5r2/8/8 w - - 0 1", &testBoardB);

  /* Enable to see the situation : */
  /* printBoardAndData(testBoardB); */


  bishopMoveGenerator(&tmp, 4, 3, white, testBoardB);

  /* (4,3) -> (1,0) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4310);
  /* (4,3) -> (2,1) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4321);
  /* (4,3) -> (3,2) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4332);
  /* (4,3) -> (5,2) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4352);
  /* (4,3) -> (7,6) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4376);
  /* (4,3) -> (6,5) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4365);
  /* (4,3) -> (5,4) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4354);

  stack_free(&tmp);
}

void test_rookMoveGenerator(void) {
  Board testBoardR;
  Stack tmp;
  stack_alloc(&tmp);

  /* Say we have a black rook on e4<=>(4,3), a black pawn");
   on e5<=>(4,4) and a white rook on b4<=>(0,3)**\n"); */

  fenToBoard("8/8/8/4p3/1R2r3/8/8/8 b - - 0 1", &testBoardR);

  /* Enable to see the situation :
 printBoardAndData(testBoardR);*/

  rookMoveGenerator(&tmp, 4, 3, black, testBoardR);

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

  stack_free(&tmp);
}

void test_queenMoveGenerator(void) {
  Board testBoardQ;
  Stack tmp;
  stack_alloc(&tmp);

  /* Say we have a white queen on e4<=>(4,3), a black knight");
   on f5<=>(5,4) and a white pawn on e2<=>(4,1)**"); */

  fenToBoard("8/8/8/5n2/4Q3/8/4P3/8 w - - 0 1", &testBoardQ);

  /* Enable to see the situation :
  printBoardAndData(testBoardQ); */


  queenMoveGenerator(&tmp, 4, 3, white, testBoardQ);

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
  /* (4,3) -> (4,2) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4342);
  /* (4,3) -> (4,7) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4347);
  /* (4,3) -> (4,6) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4346);
  /* (4,3) -> (4,5) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4345);
  /* (4,3) -> (4,4) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4344);
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
  /* (4,3) -> (5,4) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4354);

  stack_free(&tmp);
}

void test_knightMoveGenerator(void) {
  Board testBoardN;
  Stack tmp;
  stack_alloc(&tmp);

  /* Say we have a white knight on e4<=>(4,3), a black pawn
     on f6<=>(5,5) and a white king on d2<=>(3,1) */

  fenToBoard("8/8/5p2/8/4N3/8/3K4/8 w - - 0 1", &testBoardN);

  /* Enable to see the situation :
  printBoardAndData(testBoardN); */

  knightMoveGenerator(&tmp, 4, 3, white, testBoardN);

  /* (4,3) -> (2,2) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4322);
  /* (4,3) -> (2,4) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4324);
  /* (4,3) -> (5,1) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4351);
  /* (4,3) -> (6,2) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4362);
  /* (4,3) -> (6,4) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4364);
  /* (4,3) -> (3,5) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4335);
  /* (4,3) -> (5,5) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4355);

  stack_free(&tmp);
}

void test_kingMoveGenerator(void) {
  Board testBoardK;
  Stack tmp;
  stack_alloc(&tmp);

  bool threats[8][8];
  /* Say we have a black king on e4<=>(4,3), with black pawns
     all around except in f5<=>(5,4) (empty) and in d3<=>(3,2) (white pawn) */

  fenToBoard("8/8/8/3pp3/3pkp2/3Ppp2/8/8 b - - 0 1", &testBoardK);

  /* Enable to see the situation :
  printBoardAndData(testBoardK); */
  findThreats(&testBoardK, black, threats);
  kingMoveGenerator(&tmp, 4, 3, black, testBoardK, threats);

  /* (4,3) -> (3,2) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4332);
  /* (4,3) -> (5,4) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4354);

  stack_free(&tmp);
}

void test_pawnMoveGenerator1(void) {
  Board testBoardP;
  Stack tmp;
  stack_alloc(&tmp);

  /* Say we have a white pawn on a2<=>(0,1) with a black knight on b3<=>(1,2) */

  fenToBoard("8/8/8/8/8/1n6/P7/8 w - - 0 1", &testBoardP);

  /* Enable to see the situation : printBoardAndData(testBoardP); */

  pawnMoveGeneratorCapture(&tmp, 0, 1, white, testBoardP);
  pawnMoveGeneratorNoCapture(&tmp, 0, 1, white, testBoardP);
  /* (0,1) -> (0,3) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 103);
  /* (0,1) -> (0,2) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 102);
  /* (0,1) -> (1,2) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 112);

  stack_free(&tmp);
}

void test_pawnMoveGenerator2(void) {
  Board testBoardP2;
  Stack tmp;
  stack_alloc(&tmp);

  /* Say we have a black pawn on e4<=>(4,3) with a white pawn
     on d4<=>(3,3) so that d2<=>(3,2) can be taken en passant */

  fenToBoard("8/8/8/8/3Pp3/8/8/8 b - d3 0 1", &testBoardP2);

  /* Enable to see the situation :  printBoardAndData(testBoardP2); */

  pawnMoveGeneratorCapture(&tmp, 4, 3, black, testBoardP2);
  pawnMoveGeneratorNoCapture(&tmp, 4, 3, black, testBoardP2);
  /* (4,3) -> (4,2) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4342);
  /* (4,3) -> (3,2) */
  CU_ASSERT_EQUAL(stack_pop(&tmp), 4332);

  stack_free(&tmp);
}

void test_castlesMoveGenerator(void) {
/*  Board testBoardCastles;
  Stack tmp;
  stack_alloc(&tmp);

   In this situation, all castles might be okay, but still
   a kight on b2 disturb the white castle on queen side*/

  /*fenToBoard("8/8/8/8/8/8/8/RN2K2R w KQkq - 0 1", &testBoardCastles);

   Enable to see the situation :*/
  /* printBoardAndData(testBoardCastles); */

  /* Let castleMoveGenerator be called by kingMoveGenerator (more accurate)
  kingMoveGenerator(&tmp, 4, 0, white, testBoardCastles);

  stack_free(&tmp);*/
}

void test_movesGenerator(void) {
  Graph testGraph;
  graph_alloc(&testGraph);

  /* We want all moves from the beginning position */
  initAGame(&(testGraph.root));
  initAGame(&(testGraph.current_node));

  movesGenerator(&testGraph);
  /* printBoardAndData(testGraph.current_node);  */

  /* (7,1) -> (7,3) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 7173);
  /* (7,1) -> (7,2) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 7172);
  /* (6,1) -> (6,3) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 6163);
  /* (6,1) -> (6,2) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 6162);
  /* (5,1) -> (5,3) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 5153);
  /* (5,1) -> (5,2) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 5152);
  /* (4,1) -> (4,3) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 4143);
  /* (4,1) -> (7,2) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 4142);
  /* (3,1) -> (3,3) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 3133);
  /* (3,1) -> (3,2) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 3132);
  /* (2,1) -> (2,3) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 2123);
  /* (2,1) -> (2,2) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 2122);
  /* (1,1) -> (1,3) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 1113);
  /* (1,1) -> (1,2) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 1112);
  /* (0,1) -> (0,3) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 103);
  /* (0,1) -> (0,2) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 102);
  /* (6,0) -> (5,2) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 6052);
  /* (6,0) -> (7,2) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 6072);
  /* (1,0) -> (0,2) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 1002);
  /* (1,0) -> (2,2) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 1022);

  graph_free(&testGraph);
}

void test_play_move(void) {
  Board before;
  Board after;

  int i, j;

  initAGame(&before);
  initAGame(&after);
  after.square[4][3] = after.square[4][1];
  after.square[4][1].piece = empty;
  after.square[4][1].color = neutral;
  play_move(4143, &before);

  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      CU_ASSERT_EQUAL(before.square[i][j].piece, after.square[i][j].piece);
}

void test_update_board(void) {
  Graph graph;
  Arc father;
  graph_alloc(&graph);
  arc_alloc(&father);

  stack_push(&graph.current_moves, 4143);
  stack_push(&graph.current_moves, 4344);
  stack_push(&graph.current_moves, 4445);
  stack_to_identifier(father.data, graph.current_moves, 0);

  initAGame(&(graph.root));
  initAGame(&(graph.current_node));

  CU_ASSERT_EQUAL(graph.current_node.square[4][1].piece, pawn);
  CU_ASSERT_EQUAL(graph.current_node.square[4][3].piece, empty);
  CU_ASSERT_EQUAL(graph.current_node.square[4][4].piece, empty);
  CU_ASSERT_EQUAL(graph.current_node.square[4][5].piece, empty);

  update_board(father, &graph.current_node);

  CU_ASSERT_EQUAL(graph.current_node.square[4][5].piece, pawn);

  graph_free(&graph);
  arc_free(&father);
}

void test_findThreats(void) {
  Board testBoard;
  bool threats[8][8];

  /* Juste print the board and the threats to see this complicated situation
   * it's been done so that the only move for the white king is f1 <->(5,0)
   */
  fenToBoard("q6n/7k/8/8/7b/3p5/8/1r2K3 w KQkq - 0 1", &testBoard);
  findThreats(&testBoard, testBoard.activeColor, threats);
  printBoardAndData(testBoard);
  printThreatBoard(threats);

  CU_ASSERT_TRUE(threats[4][0]);
  CU_ASSERT_TRUE(threats[5][1]);
  CU_ASSERT_TRUE(threats[6][2]);

  CU_ASSERT_TRUE(threats[0][6]);
  CU_ASSERT_TRUE(threats[1][7]);
  CU_ASSERT_TRUE(threats[1][6]);


  CU_ASSERT_TRUE(threats[0][0]);
  CU_ASSERT_TRUE(threats[1][1]);
  CU_ASSERT_TRUE(threats[3][0]);

  CU_ASSERT_TRUE(threats[5][6]);
  CU_ASSERT_TRUE(threats[6][5]);

  CU_ASSERT_TRUE(threats[7][7]);
  CU_ASSERT_TRUE(threats[6][7]);
  CU_ASSERT_TRUE(threats[6][6]);
  CU_ASSERT_TRUE(threats[6][5]);
  CU_ASSERT_TRUE(threats[7][5]);

  CU_ASSERT_TRUE(threats[2][1]);
  CU_ASSERT_TRUE(threats[4][1]);
}

void test_findAllPinnings(void) {
  Board board;
  Color activeColor;
  bool pinned[8][8];

  fenToBoard("8/8/5Q2/8/5b2/8/5k2/8 w - - 0 1", &board);
  activeColor = black;

  findAllPinnings(&board, activeColor, pinned);

  /*
  printBoardAndData(board);
  printf("\n");
  for (int j = 7 ; j >= 0 ; --j) {
    for (int i = 0 ; i < 8 ; ++i) {
      printf("%d ", pinned[i][j]);
    }
    printf("\n");
  }
  */


  for (int j = 0 ; j < 8 ; ++j)
    for (int i = 0 ; i < 8 ; ++i) {
      if (i == 5 && j == 3) {
        CU_ASSERT_EQUAL(pinned[i][j], true);
      } else {
        CU_ASSERT_EQUAL(pinned[i][j], false);
      }
    }
}

void test_legalMoves(void) {
  Graph testGraph;
  graph_alloc(&testGraph);

  fenToBoard("q6n/7k/8/8/7b/2pp5/8/1r2K3 w KQkq - 0 1", &(testGraph.root));
  fenToBoard("q6n/7k/8/8/7b/2pp5/8/1r2K3 w KQkq - 0 1",
             &(testGraph.current_node));
  movesGenerator(&testGraph);
  printBoardAndData(testGraph.current_node);

  /* (4,0) -> (5,0) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 4050);
  /* Juste print the board and the threats to see this complicated situation
   * it's been done so that the only move for the white king is f1 <->(5,0)
   */
}
void test_legalMoves2(void) {
  Graph testGraph;
  graph_alloc(&testGraph);

  fenToBoard("3rr3/8/8/8/8/8/P7/4K3 w KQkq - 0 1", &(testGraph.root));
  fenToBoard("3rr3/8/8/8/8/8/P7/4K3 w KQkq - 0 1", &(testGraph.current_node));
  movesGenerator(&testGraph);
  printBoardAndData(testGraph.current_node);
}
void test_legalMoves3(void) {
  Graph testGraph;
  graph_alloc(&testGraph);

  fenToBoard("rnbqk1nr/ppppp1b1/5pQp/8/4PP2/8/PPPP2PP/RNB1KBNR b KQkq - 0 1",
             &(testGraph.root));
  fenToBoard("rnbqk1nr/ppppp1b1/5pQp/8/4PP2/8/PPPP2PP/RNB1KBNR b KQkq - 0 1",
             &(testGraph.current_node));
  movesGenerator(&testGraph);
  printBoardAndData(testGraph.current_node);
  /* (4,7) -> (5,7) */
  CU_ASSERT_EQUAL(stack_pop(&(testGraph.current_moves)), 4757);
}
