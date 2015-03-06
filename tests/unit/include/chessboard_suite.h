/* Copyright 2015 <Copyright Owner> */

#ifndef CHESSBOARD_SUITE_H_
#define CHESSBOARD_SUITE_H_

#include "CUnit/Basic.h"

#include "../../../chessaint/include/chessboard.h"

int init_suite_chessboard(void);

int clean_suite_chessboard(void);

void testNormalValues(void);

/*void testErrorValues(void); */

#endif 
