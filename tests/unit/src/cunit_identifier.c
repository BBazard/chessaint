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
                           "Testing stack_exchange",
                           test_stack_exchange)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_identifier,
                           "Testing stack_init",
                           test_stack_init)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_identifier,
                           "Testing stack_pop",
                           test_stack_pop)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_identifier,
                           "Testing stack_push",
                           test_stack_push)) {
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
                           "Testing identifier_is_leaf",
                           test_identifier_is_leaf)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_identifier,
                           "Testing identifier_is_white",
                           test_identifier_is_white)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_identifier,
                           "Testing identifier_is_passant",
                           test_identifier_is_passant)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_identifier,
                           "Testing identifier_get_cast",
                           test_identifier_get_cast)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_identifier,
                           "Testing identifier_get_halfmove",
                           test_identifier_get_halfmove)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_identifier,
                           "Testing identifier_get_fullmove",
                           test_identifier_get_fullmove)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  return 0;
}
