/* This file is part of the ChessAInt project 2015 */
#include <stdlib.h>

#include "CUnit/Basic.h"

#include "include/chessboard.h"

#include "../include/chessboard_suite.h"

int add_chessboard_suite(CU_pSuite pSuite_chessboard) {
  if (pSuite_chessboard != NULL)
    return EXIT_FAILURE;

  /* add a suite to the registry */
  pSuite_chessboard = CU_add_suite("Suite chessboard",
                                   init_suite_chessboard,
                                   clean_suite_chessboard);
  if (NULL == pSuite_chessboard) {
    CU_cleanup_registry();
    return CU_get_error();
  }


  return EXIT_SUCCESS;
}
