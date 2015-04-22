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
#include "include/concatenate.h"

/* the suite to test */
#include "../include/concatenate_suite.h"


/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int add_concatenate_suite(CU_pSuite pSuite_concatenate) {
  if (pSuite_concatenate != NULL) return 1;

  /* add a suite to the registry */
  pSuite_concatenate = CU_add_suite("Suite concatenate",
                              init_suite_concatenate,
                              clean_suite_concatenate);
  if (NULL == pSuite_concatenate) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add the tests to the suite */
  if (NULL == CU_add_test(pSuite_concatenate,
                           "Testing the concatenate function",
                           test_concatenate)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  return 0;
}
