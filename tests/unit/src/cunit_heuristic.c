/* This file is part of the ChessAInt project 2015 */

/*
 *  Simple example of a CUnit unit test.
 *
 *  compile with -lcunit :
 *  gcc -o fileA.tests cunit_fileA.c fileA_suite.c fileA.c -lcunit
 *
 *  the complete list of the CU_* can be found at
 *  http://cunit.sourceforge.net/doc/writing_tests.html#assertions
 */

/* use the basic interface */
#include "CUnit/Basic.h"
/* #include "CUnit/MyMem.h" */

/* the file to test */
#include "include/heuristic.h"

/* the suite to test */
#include "../include/heuristic_suite.h"


/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int add_heuristic_suite(CU_pSuite pSuite_heuristic) {
  if (pSuite_heuristic != NULL) return 1;

  /* add a suite to the registry */
  pSuite_heuristic = CU_add_suite("Suite heuristic",
                              init_suite_heuristic,
                              clean_suite_heuristic);
  if (NULL == pSuite_heuristic) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add the tests to the suite */
  if (NULL == CU_add_test(pSuite_heuristic,
                           "Testing the is_mat function",
                           test_is_mat)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add the tests to the suite */
  if (NULL == CU_add_test(pSuite_heuristic,
                           "Testing the number_of_char function",
                           test_number_of_char)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_heuristic,
                           "Testing the heuristic_fen function",
                           test_heuristic_fen)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  return 0;
}
