/* This file is part of the ChessAInt project 2015 */
#ifndef TRUNK_TESTS_UNIT_INCLUDE_CHESSBOARD_SUITE_H_
#define TRUNK_TESTS_UNIT_INCLUDE_CHESSBOARD_SUITE_H_

#include "CUnit/Basic.h"
#include "include/chessboard.h"

int init_suite_chessboard(void);

int clean_suite_chessboard(void);

void testInitAndFenChessboard(void);

void testPieceMoving(void);

void testMoveToArc(void);

void testLetterToNumberCoord(void);

void testLegalMove(void);



#endif /*TRUNK_TESTS_UNIT_INCLUDE_CHESSBOARD_SUITE_H_*/



