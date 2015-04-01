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
#include "include/llist.h"

/* the suite to test */
#include "../include/llist_suite.h"


/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int add_llist_suite(CU_pSuite pSuite_llist) {
  if (pSuite_llist != NULL) return 1;

  /* add a suite to the registry */
  pSuite_llist = CU_add_suite("Suite llist",
                              init_suite_llist,
                              clean_suite_llist);
  if (NULL == pSuite_llist) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add the tests to the suite */
  if (NULL == CU_add_test(pSuite_llist,
                           "Test of the equal function between arcs",
                           test_arc_equal)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_llist,
                           "Test of the adding function in a linked list",
                           test_llist_add)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_llist,
                           "Test of the deleting function in a linked list",
                           test_llist_suppr)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_llist,
                           "Test of the freeing function in a linked list",
                           test_llist_free)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  return 0;
}
