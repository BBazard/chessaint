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
#include "include/identifier.h"

/* the suite to test */
#include "../include/identifier_suite.h"


/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int add_identifier_suite(CU_pSuite pSuite_identifier) {
  if (pSuite_identifier != NULL) return 1;

  /* add a suite to the registry */
  pSuite_identifier = CU_add_suite("Suite identifier",
                              init_suite_identifier,
                              clean_suite_identifier);
  if (NULL == pSuite_identifier) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add the tests to the suite */
  if (NULL == CU_add_test(pSuite_identifier,
                           "Testing path_init",
                           test_path_init)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_identifier,
                           "Testing identifier_print",
                           test_identifier_print)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_identifier,
                           "Testing identifier_path",
                           test_identifier_path)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  return 0;
}
