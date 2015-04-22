/*  This file is part of the ChessAInt project 2015 */

/*
 *  The complete list of the CU_* can be found at
 *  http://cunit.sourceforge.net/doc/writing_tests.html#assertions
 */

#include "CUnit/Basic.h"

int add_chessboard_suite(CU_pSuite pSuite_chessboard);
int add_llist_suite(CU_pSuite pSuite_llist);
int add_heuristic_suite(CU_pSuite pSuite_heuristic);
int add_identifier_suite(CU_pSuite pSuite_identifier);
int add_graph_suite(CU_pSuite pSuite_graph);
int add_uci_suite(CU_pSuite pSuite_uci);

int main() {
  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* create all the suites */
  CU_pSuite pSuite_chessboard = NULL;
  CU_pSuite pSuite_llist = NULL;
  CU_pSuite pSuite_heuristic = NULL;
  CU_pSuite pSuite_identifier = NULL;
  CU_pSuite pSuite_graph = NULL;
  CU_pSuite pSuite_uci = NULL;

  /* add the suites to the registry */
  add_chessboard_suite(pSuite_chessboard);
  add_llist_suite(pSuite_llist);
  add_heuristic_suite(pSuite_heuristic);
  add_identifier_suite(pSuite_identifier);
  add_graph_suite(pSuite_graph);
  add_uci_suite(pSuite_uci);

  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}

