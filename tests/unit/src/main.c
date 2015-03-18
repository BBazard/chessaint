/*  This file is part of the ChessAInt project 2015 */

/*
 *  The complete list of the CU_* can be found at
 *  http://cunit.sourceforge.net/doc/writing_tests.html#assertions
 */

#include "CUnit/Basic.h"

int add_chessboard_suite(CU_pSuite pSuite_chessboard);

int main() {
  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* create all the suites */
  CU_pSuite pSuite_chessboard = NULL;

  /* add the suites to the registry */
  add_chessboard_suite(pSuite_chessboard);

  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
