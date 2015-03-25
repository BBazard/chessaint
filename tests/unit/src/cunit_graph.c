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
#include "include/graph.h"

/* the suite to test */
#include "../include/graph_suite.h"


/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int add_graph_suite(CU_pSuite pSuite_graph) {
  if (pSuite_graph != NULL) return 1;

  /* add a suite to the registry */
  pSuite_graph = CU_add_suite("Suite graph",
                              init_suite_graph,
                              clean_suite_graph);
  if (NULL == pSuite_graph) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add the tests to the suite */
  if (NULL == CU_add_test(pSuite_graph,
                           "Test of the equal function between arcs",
                           test_arc_equal)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_graph,
                           "Test of the adding function in a linked list",
                           test_llist_add)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  return 0;
}
