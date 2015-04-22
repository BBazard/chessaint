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
#include "include/uci.h"

/* the suite to test */
#include "../include/uci_suite.h"


/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int add_uci_suite(CU_pSuite pSuite_uci) {
  if (pSuite_uci != NULL) return 1;

  /* add a suite to the registry */
  pSuite_uci = CU_add_suite("Suite uci",
                              init_suite_uci,
                              clean_suite_uci);
  if (NULL == pSuite_uci) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add the tests to the suite */
  if (NULL == CU_add_test(pSuite_uci,
                           "Testing classic case",
                           test_basic_case)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_uci,
                           "Testing with many whitespaces",
                           test_whitespaces)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_uci,
                           "Testing uci into move conversion",
                           test_uciToMove)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_uci,
                           "Testing rmLastCharacter",
                           test_rmUCILastCharacter)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  return 0;
}

