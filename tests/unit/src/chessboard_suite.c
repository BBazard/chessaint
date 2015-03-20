/* This file is part of the ChessAInt project 2015 */

#ifndef TRUNK_TESTS_UNIT_INCLUDE_CHESSBOARD_SUITE_H_
#define TRUNK_TESTS_UNIT_INCLUDE_CHESSBOARD_SUITE_H_

#include "include/chessboard_suite.h"
#include "CUnit/Basic.h"
#include "include/chessboard.h"

int init_suite_chessboard(void) {
  /*Assuming rook is on e4*/
  int rookLegalMoves[NBCASES] = {
  0, 0, 0, 0, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0,
  1, 1, 1, 1, 0, 1, 1, 1,
  0, 0, 0, 0, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0
};
  return 0;
}

int clean_suite_chessboard(void) {
  return 0;
}

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

void testPieceMoving(void) {
  initBoardToStartPos(boardChar, boardPiece, boardColor);
  moveBoard("e2e4", boardChar, boardPiece, boardColor);

  CU_ASSERT_EQUAL(boardChar[36], 'P');
}

void testMoveToArc(void) {
  /*Testing the simplest move and attributes*/
  Arc firstMove;
  firstMove = getArcFromMove("e2e4", 'b', 1);
  CU_ASSERT_STRING_EQUAL(firstMove.from, "e2");
  CU_ASSERT_STRING_EQUAL(firstMove.to, "e4");
  CU_ASSERT_EQUAL(firstMove.activeColor, 'b');
}

void testLetterToNumberCoord(void) {
  int tableSlot1, tableSlot2;
  tableSlot1 = lettersCoordToNumberCoord("a8");
  tableSlot2 = lettersCoordToNumberCoord("h1");
  CU_ASSERT_EQUAL(tableSlot1, 0);
  CU_ASSERT_EQUAL(tableSlot2, 63);
}

void testLegalMove(void) {
  initBoardToStartPos(boardChar, boardPiece, boardColor);
  /*PAWN*/
  CU_ASSERT_TRUE(isAWhiteLegalMove("e2e4"));
  CU_ASSERT_TRUE(isABlackLegalMove("e7e5"));
  CU_ASSERT_FALSE(isAWhiteLegalMove("e4e5"));
  CU_ASSERT_FALSE(isAWhiteLegalMove("e2e5"));
  CU_ASSERT_FALSE(isABlackLegalMove("e7e4"));
  CU_ASSERT_TRUE(isAPawnLegalMove("e2e4", 'w'));
  CU_ASSERT_FALSE(isAPawnLegalMove("e2e5", 'w'));
  CU_ASSERT_FALSE(isAPawnLegalMove("e1e2", 'w'));
  CU_ASSERT_FALSE(isAPawnLegalMove("e2f3", 'w'));
  CU_ASSERT_FALSE(isAPawnLegalMove("e2d3", 'w'));
  CU_ASSERT_FALSE(isAPawnLegalMove("a2b3", 'w'));
  CU_ASSERT_TRUE(isAPawnLegalMove("e7e5", 'b'));
  CU_ASSERT_FALSE(isAPawnLegalMove("e7e4", 'b'));
  CU_ASSERT_FALSE(isAPawnLegalMove("e7f6", 'b'));
  CU_ASSERT_FALSE(isAPawnLegalMove("e7d6", 'b'));
  /*BISHOPS*/
  CU_ASSERT_FALSE(isABishopLegalMove("f1d3", 'w'));
  CU_ASSERT_FALSE(isABishopLegalMove("c1c5", 'w'));
  CU_ASSERT_FALSE(isABishopLegalMove("f1h3", 'w'));
  /*ROOKS*/
  CU_ASSERT_FALSE(isARookLegalMove("a1a4", 'w'));
  /*Let's make some moves and agin these function */
  moveBoard("a2a4", boardChar, boardPiece, boardColor);
  moveBoard("b7b5", boardChar, boardPiece, boardColor);
  moveBoard("e2e4", boardChar, boardPiece, boardColor);
  moveBoard("d7d5", boardChar, boardPiece, boardColor);
  /*PAWN*/
  CU_ASSERT_TRUE(isAPawnLegalMove("a4b5", 'w'));
  CU_ASSERT_FALSE(isAPawnLegalMove("a2a4", 'w'));
  CU_ASSERT_TRUE(isAPawnLegalMove("e4d5", 'w'));
  /*BISHOPS*/
  CU_ASSERT_TRUE(isABishopLegalMove("f1e2", 'w'));
  CU_ASSERT_FALSE(isABishopLegalMove("f1g2", 'w'));
  CU_ASSERT_FALSE(isABishopLegalMove("f8h5", 'b'));
  CU_ASSERT_FALSE(isABishopLegalMove("f8h6", 'b'));
  CU_ASSERT_TRUE(isABishopLegalMove("c8d7", 'w'));
}

#endif /* TRUNK_TESTS_UNIT_INCLUDE_CHESSBOARD_SUITE_H_ */

