/* Copyright 2015 Hugo GANGLOFF */

#ifndef TRUNK_TESTS_UNIT_INCLUDE_CHESSBOARD_SUITE_H_
#define TRUNK_TESTS_UNIT_INCLUDE_CHESSBOARD_SUITE_H_

#include "CUnit/Basic.h"

#include "../../../chessaint/include/chessboard.h"

int init_suite_chessboard(void);

int clean_suite_chessboard(void);

void testInitAndFenChessboard(void);

void testPieceMoving(void);

/*void testErrorValues(void); */

#endif /*TRUNK_TESTS_UNIT_INCLUDE_CHESSBOARD_SUITE_H_*/


