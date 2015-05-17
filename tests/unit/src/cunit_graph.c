/* This file is part of the ChessAInt project 2015 */

#include "CUnit/Basic.h"

#include "include/graph.h"

#include "include/graph_suite.h"

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
                           "Test play_move function",
                          test_play_move)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_graph,
                           "Test update_board function",
                          test_update_board)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

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
                           "Test of castlings moves",
                          test_castlesMoveGenerator)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_graph,
                           "Test of the move generator function",
                          test_movesGenerator)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_graph,
                           "Test of the threat generator function",
                          test_findThreats)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_graph,
                           "Test of the find pinnings function",
                          test_findAllPinnings)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_graph,
  "Another Test of a certain position for legal moves check",
                          test_legalMoves2)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_graph,
    "Another Test of a certain position for legal moves check",
                          test_legalMoves3)) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  if (NULL == CU_add_test(pSuite_graph,
"Test for legal moves : only solution put a piece between the threat king",
    test_legalMoves4)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_graph,
    "Another Test of a certain position for legal moves check",
                          test_legalMoves6)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite_graph,
    "Test for a buggy ingame situation",
                          test_legalMoves7)) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  return 0;
}

