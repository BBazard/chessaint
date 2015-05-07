/* This file is part of the ChessAInt project 2015 */

#include "CUnit/Basic.h"

#include "include/astar.h"

#include "include/astar_suite.h"


int add_astar_suite(CU_pSuite pSuite_astar) {
  if (pSuite_astar != NULL) return 1;

  /* add a suite to the registry */
  pSuite_astar = CU_add_suite("Suite astar",
                              init_suite_astar,
                              clean_suite_astar);
  if (NULL == pSuite_astar) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add the tests to the suite */
  if (NULL == CU_add_test(pSuite_astar,
                           "Testing move_to_node function",
                          test_move_to_node)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

    if (NULL == CU_add_test(pSuite_astar,
                           "Testing next_gen function",
                            test_next_gen)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  return 0;
}

