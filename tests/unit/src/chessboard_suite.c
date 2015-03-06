#include "CUnit/Basic.h"

#include "../../../chessaint/include/chessboard.h"
#include "../include/chessboard_suite.h"

/* The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite_chessboard(void) {
/* 
 *   if (problem during initialisation)
 *     return -1; // this number can be used to explicit the problem
 */
  return 0;
}

/* The suite cleanup function.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite_chessboard(void) {
/* 
 *   if (problem during cleaning)
 *     return -1; // this number can be used to explicit the problem
 */
  return 0;
}

/* A test
 */
void testNormalValues(void) {
  initBoardToStartPos(board);
  /* Pieces should be correctly placed in a start position after the last call ; just checking first and last cases */
  CU_ASSERT_EQUAL(board[0],'r');
  CU_ASSERT_EQUAL(board[63],'R');

  /*Just to whow off */
  printf("\n\n");
  printBoard(board);
  printf("\n\n");

}

/* Another test
 */
/*
*void testErrorValues(void) {
*
*
*}
*/
