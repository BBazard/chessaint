#include <stdlib.h>

#include "CUnit/Basic.h"

#include "include/chessboard.h"

#include "include/chessboard_suite.h"

int add_chessboard_suite(CU_pSuite pSuite_chessboard) {
  if(pSuite_chessboard != NULL)
    return EXIT_FAILURE;

  /* add a suite to the registry */
  pSuite_chessboard = CU_add_suite("Suite chessboard",
                                   init_suite_chessboard,
                                   clean_suite_chessboard);
  if (NULL == pSuite_chessboard) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add the tests to the suites */
  if ((NULL == CU_add_test(pSuite_chessboard,
       "Checking initialization and FEN reading for chessboard",
       testInitAndFenChessboard))) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  
  if ((NULL == CU_add_test(pSuite_chessboard,
       "Checking if a move given by human is correctly played on board",
       testPieceMoving))) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if ((NULL == CU_add_test(pSuite_chessboard,
       "Checking the move to arc function",
       testMoveToArc))) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if ((NULL == CU_add_test(pSuite_chessboard,
       "Checking the function that changes coordinates",
       testLetterToNumberCoord))) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if ((NULL == CU_add_test(pSuite_chessboard,
       "Testing legal moves",
       testLegalMove))) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  return EXIT_SUCCESS;
}
