/*Copyright 2015 Hugo GANGLOFF */
#include "CUnit/Basic.h"

#include "../../../chessaint/include/chessboard.h"
#include "../include/chessboard_suite.h"

/* The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 */


int init_suite_chessboard(void) {
  return 0;
}

/* The suite cleanup function.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite_chessboard(void) {
/* 
 *   if (problem during cleaning)
 *     return -1; // this number can be used to explicit the problem
 */
  return 0;
}

/* A test
 */
void testInitAndFenChessboard(void) {
  /* Trying our init board function */
  initBoardToStartPos(board);
  /*Just to show off */
  /*printf("\n\n");
  printBoard(board);
  printf("\n\n");*/

  /* Getting a board from a FEN string,*/
  /* here is the starting position fen string */
  fenToBoard(board2,
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
  /*Just to show off */
  /*printf("\n\n");
  printBoard(board2);
  printf("\n\n");*/

  /* Getting a board from another FEN string,*/
  /* here is the starting position + 1.e4 e5*/
  fenToBoard(board3,
    "rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 1");
  /*Just to show off */
  /*printf("\n\n");
  printBoard(board3);
  printf("\n\n");*/

  /* Pieces should be correctly placed */
  /*in a start position after the last call ; */
  /* just checking first and last cases */
  CU_ASSERT_EQUAL(board[0], 'r');
  CU_ASSERT_EQUAL(board[63], 'R');

  /*From the FEN string describing the starting position, */
  /*we should have pieces correctly placed */
  CU_ASSERT_EQUAL(board2[0], 'r');
  CU_ASSERT_EQUAL(board2[63], 'R');

  /*From start pos + 1.e4 e5, */
  /*we're checking the position of pawns that has moved */
  CU_ASSERT_EQUAL(board3[28], 'p');
  CU_ASSERT_EQUAL(board3[36], 'P');
}

/* Another test
 */

void testPieceMoving(void) {
  initBoardToStartPos(board);
  moveBoard("e2e4",board);

  CU_ASSERT_EQUAL(board[36],'P');
}


