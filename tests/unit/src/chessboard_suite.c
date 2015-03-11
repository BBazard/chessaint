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
  initBoardToStartPos(boardChar, boardPiece, boardColor);
  /* Pieces should be correctly placed */
  /*in a start position after the last call ; */
  /* just checking first and last cases */
  CU_ASSERT_EQUAL(boardChar[0], 'r');
  CU_ASSERT_EQUAL(boardChar[63], 'R');

  /* Getting a board from a FEN string,*/
  /* here is the starting position fen string */
  fenToBoard(boardChar,
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
  /* Pieces should be correctly placed */
  /*in a start position after the last call ; */
  /* just checking first and last cases */
  CU_ASSERT_EQUAL(boardChar[0], 'r');
  CU_ASSERT_EQUAL(boardChar[63], 'R');



}

/* Another test
 */

void testPieceMoving(void) {
  initBoardToStartPos(boardChar,boardPiece,boardColor);
  moveBoard("e2e4",boardChar,boardPiece,boardColor);

  CU_ASSERT_EQUAL(boardChar[36],'P');
}

void testMoveToArc(void) {
  /*Testing the simplest move and attributes*/
  Arc firstMove;
  firstMove = getArcFromMove("e2e4",'b',1);
  CU_ASSERT_STRING_EQUAL(firstMove.from, "e2");
  CU_ASSERT_STRING_EQUAL(firstMove.to, "e4");
  CU_ASSERT_EQUAL(firstMove.activeColor,'b');
}

void testLetterToNumberCoord(void) {
  int tableSlot1, tableSlot2;
  tableSlot1 = lettersCoordToNumberCoord("a8");
  tableSlot2 = lettersCoordToNumberCoord("h1");
  CU_ASSERT_EQUAL(tableSlot1,0);
  CU_ASSERT_EQUAL(tableSlot2,63);
}

void testLegalMove(void) {
  initBoardToStartPos(boardChar,boardPiece,boardColor);
  /*With a clean board, next assertions must be true */
  CU_ASSERT_TRUE(isAWhiteLegalMove("f2f4"));
  CU_ASSERT_TRUE(isABlackLegalMove("e7e5"));
  /*With a clean board, next assertions must be false */
  CU_ASSERT_FALSE(isAWhiteLegalMove("e4e5"));
}

