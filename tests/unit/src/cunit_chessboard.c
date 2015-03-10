/* Copyright 2015 Hugo GANGLOFF */

/*
 *  Simple example of a CUnit unit test.
 *
 *  compile with -lcunit :
 *  gcc -o chessboard.tests src/cunit_chessboard.c src/chessboard_suite.c ../../chessaint/src/chessboard.c -lcunit
 *
 *  the complete list of the CU_* can be found at
 *  http://cunit.sourceforge.net/doc/writing_tests.html#assertions
 */

/* use the basic interface */
#include "CUnit/Basic.h"

/* the file to test */
#include "../../../chessaint/include/chessboard.h"

/* the suite to test */
#include "../include/chessboard_suite.h"

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main() {
  CU_pSuite pSuite = NULL;

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* add a suite to the registry */
  pSuite = CU_add_suite("Suite chessboard",
    init_suite_chessboard, clean_suite_chessboard);
  if (NULL == pSuite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add the tests to the suite */
  /* all the functions in chessboard_suite.h must be added */
  if ((NULL == CU_add_test(pSuite,
          "Checking initialization and FEN reading for chessboard",
          testInitAndFenChessboard))) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  
  if ((NULL == CU_add_test(pSuite,
          "Checking if a move given by human is correctly played on board",
          testPieceMoving))) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
