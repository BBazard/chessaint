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

/* @todo Write this test function */
void test_is_mate(void) {
  char* white_mate_fen = "6rk/4pq2/3r4/8/8/8/8/B5KR w - - 0 1";
  char* black_mate_fen = "6RK/4PQ2/3R4/8/8/8/8/b5kr b - - 0 1";

  fenToBoard(white_mate_fen, &white_mate);
  fenToBoard(black_mate_fen, &black_mate);

  Board white_mate;
  Board black_mate;
  Board no_mate;
  
  CU_ASSERT_EQUAL(is_mate(white_mate), white);
  CU_ASSERT_EQUAL(is_mate(black_mate), black);
  CU_ASSERT_EQUAL(is_mate(no_mate), neutral);
}

void test_heuristic(void) {
  /* heuristic function should return 0 with the fen representing
     the initial position */

  Board start;
  initAGame(&start);
  CU_ASSERT_EQUAL(heuristic(&start), 0);

  /* When mat function should returns 500 (which is a little exception to
     the rule of computation only with current position) and not 
     the normal score */

  char* mate_fen = "6rk/4pq2/3r4/8/8/8/8/B5KR w - - 0 1";
  Board mate;
  
  fenToBoard(mate_fen, &mate);
  CU_ASSERT_EQUAL(heuristic(&mate), 500);

  /* Score is computed with white as reference meaning a good score (above 0)
     represents a advantage for white.
     But we should still assert that the sum of white and black score is equal
     to 0. In order to do this we just exchange the color of the fen
     (replacing uppercase letters by lowercase ones) */

  char* white_normal_fen =
    "rnbqkbn1/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq - 1 2";
  char* white_reverse_fen =
    "RNBQKBN1/PP1PPPPP/8/2P5/4p3/5n2/pppp1ppp/rnbqkb1r w KQkq - 1 2";

  Board white_normal;
  Board white_reverse;
  
  fenToBoard(white_normal_fen, &white_normal);
  fenToBoard(white_reverse_fen, &white_reverse);
  
  CU_ASSERT_EQUAL((heuristic(&white_normal) +
                    heuristic(&white_reverse)), 0);

  /* Doing the same but by inversing the turn (w or b at the and of the FEN)
     rather than replacing uppercase by lowercase letters */

  char* white_fen =
    "rnbqkb1r/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq - 1 2";
  char* black_fen =
    "rnbqkb1r/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2";

  Board white;
  Board black;
  
  fenToBoard(white_fen, &white);
  fenToBoard(black_fen, &black);
  
  CU_ASSERT_EQUAL((heuristic(&white) + heuristic(&black)), 0);

  /* Assert that a piece in danger counts only half the value, with
     two computations, one with the pawn safe, and the second in danger */

  char* safe_fen = "rnbqkb1r/pppppppp/5n2/8/3P4/8/PPP1PPPP/RNBQKBN1 w - - 0 1";
  char* danger_fen = "r1bqkbnr/pppppppp/2n5/8/3P4/8/PPP1PPPP/RNBQKBN1 w - - 0 1";

  Board safe;
  Board danger;
  
  fenToBoard(safe_fen, &safe);
  fenToBoard(danger_fen, &danger);

  CU_ASSERT_EQUAL(heuristic(&safe), heuristic(&danger) * 2);
}
