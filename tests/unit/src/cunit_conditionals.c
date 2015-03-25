/* This file is part of the ChessAInt project 2015 */
#include <stdlib.h>

#include "CUnit/Basic.h"

#include "include/conditionals.h"

#include "include/conditionals_suite.h"

int add_conditionals_suite(CU_pSuite pSuite_conditionals) {
  if (pSuite_conditionals != NULL)
    return EXIT_FAILURE;

  /* add a suite to the registry */
  pSuite_conditionals = CU_add_suite("Suite conditionals",
                                   init_suite_conditionals,
                                   clean_suite_conditionals);
  if (NULL == pSuite_conditionals) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add the tests to the suites */


  return EXIT_SUCCESS;
}
