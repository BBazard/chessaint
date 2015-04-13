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
 * CUnit error code on faixlure.
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
                           "Test isInBoardSquare function",
                          test_isInBoardSquare)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_graph,
                           "Test the bishop move function",
                          test_bishopMoveGenerator)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_graph,
                           "Test the rook move function",
                          test_rookMoveGenerator)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_graph,
                           "Test the queen move function",
                          test_queenMoveGenerator)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_graph,
                           "Test the knight move function",
                          test_knightMoveGenerator)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_graph,
                           "Test the king move function",
                          test_kingMoveGenerator)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_graph,
                           "Test 1 of the pawn move function",
                          test_pawnMoveGenerator1)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_graph,
                           "Test 2 of the pawn move function",
                          test_pawnMoveGenerator2)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_graph,
                           "Test of the move generator function",
                          test_movesGenerator)) {
    CU_cleanup_registry();
    return CU_get_error();
  }


  return 0;
}
