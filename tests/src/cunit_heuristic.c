/* This file is part of the ChessAInt project 2015 */

#include "CUnit/Basic.h"

#include "include/heuristic.h"

#include "include/heuristic_suite.h"

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
                           "Testing the is_mate function",
                           test_is_mate)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_heuristic,
                           "Testing the update_threat function",
                           test_update_threat)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

    if (NULL == CU_add_test(pSuite_heuristic,
                           "Testing the update_protection function",
                           test_update_protection)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_heuristic,
                           "Testing the heuristic function",
                           test_heuristic)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  return 0;
}

