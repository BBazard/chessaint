/* This file is part of the ChessAInt project 2015 */

#include "CUnit/Basic.h"
#include "include/heuristic.h"

/* The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite_heuristic(void) {
/* 
 *   if (problem during initialisation)
 *     return -1; // this number can be used to explicit the problem
 */
  return 0;
}

/* The suite cleanup function.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite_heuristic(void) {
/* 
 *   if (problem during cleaning)
 *     return -1; // this number can be used to explicit the problem
 */
  return 0;
}

void test_heuristic_fen(void) {

  /* heuristic_fen function should return 501 if the fen is not correct */

  char* notcorrect;

  CU_ASSERT_EQUAL(heuristic_fen(notcorrect), 501);

  /* heuristic_fen function should return 0 with the fen representing
     the initial position */

  char* start = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  CU_ASSERT_EQUAL(heuristic_fen(start), 0);

  /* When mat function should returns 500 (which is a little exception to
     the rule of computation only with current position */

  char* mat;
  CU_ASSERT_EQUAL(heuristic_fen(mat), 500);

  /* Score is computed with white as reference meaning a good score (above 0)
     represents a advantage for white.
     But we should still assert that the sum of white and black score is equal
     to 0. In order to do this we just exchange the color of the fen
     (replacing uppercase letters by lowercase ones) */

  char* white;
  char* black;

  CU_ASSERT_EQUAL( (heuristic_fen(white) + heuristic_fen(black) ), 0);

  /* Assert that a piece in danger counts only half the value, with
     two computations, one with the pawn safe, and the second in danger */

  char* safe;
  char* danger;

  CU_ASSERT_EQUAL( heuristic_fen(safe), heuristic_fen(danger)/2);
}
