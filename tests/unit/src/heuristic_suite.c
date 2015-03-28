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
  /* heuristic_fen function should return 501 if the string is not a fen, 
     502 if the fen is not correct */

  char* not_a_fen_at_all = "iamnotafenanditrytostickin";
  char* too_many_pawns =
    "rnbqkbnr/pppppppp/8/8/8/P/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

  CU_ASSERT_EQUAL(heuristic_fen(not_a_fen_at_all), 501);
  CU_ASSERT_EQUAL(heuristic_fen(too_many_pawns), 502);

  /* heuristic_fen function should return 0 with the fen representing
     the initial position */

  char* start = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  CU_ASSERT_EQUAL(heuristic_fen(start), 0);

  /* When mat function should returns 500 (which is a little exception to
     the rule of computation only with current position) and not 
     the normal score */

  char* mat = "6rk/4pq2/3r4/8/8/8/8/B5KR w - - 0 1";
  CU_ASSERT_EQUAL(heuristic_fen(mat), 500);

  /* Score is computed with white as reference meaning a good score (above 0)
     represents a advantage for white.
     But we should still assert that the sum of white and black score is equal
     to 0. In order to do this we just exchange the color of the fen
     (replacing uppercase letters by lowercase ones) */

  char* white =
    "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2";
  char* black =
    "RNBQKBNR/PP1PPPPP/8/2P5/4p3/5n2/pppp1ppp/rnbqkn1r b KQkq - 1 2";

  CU_ASSERT_EQUAL((heuristic_fen(white) + heuristic_fen(black)), 0);

  /* Assert that a piece in danger counts only half the value, with
     two computations, one with the pawn safe, and the second in danger */

  char* safe = "rnbqkb1r/pppppppp/5n2/8/3P4/8/PPP1PPPP/RNBQKBNR w - - 0 1";
  char* danger = "r1bqkbnr/pppppppp/2n5/8/3P4/8/PPP1PPPP/RNBQKBNR w - - 0 1";

  CU_ASSERT_EQUAL(heuristic_fen(safe), heuristic_fen(danger)/2);
}
