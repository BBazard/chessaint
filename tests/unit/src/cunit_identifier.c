/* This file is part of the ChessAInt project 2015 */

#include "CUnit/Basic.h"

#include "include/identifier.h"

#include "include/identifier_suite.h"

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
                           "Testing stack_contract",
                           test_stack_contract)) {
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

  /* if (NULL == CU_add_test(pSuite_identifier, */
  /*                          "Testing identifier_print", */
  /*                          test_identifier_print)) { */
  /*   CU_cleanup_registry(); */
  /*   return CU_get_error(); */
  /* } */

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

  if (NULL == CU_add_test(pSuite_identifier,
                           "Testing identifier_to_stack",
                           test_identifier_to_stack)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  return 0;
}

