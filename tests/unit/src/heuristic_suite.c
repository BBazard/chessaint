/* This file is part of the ChessAInt project 2015 */

#include "CUnit/Basic.h"
#include "include/heuristic.h"

int init_suite_heuristic(void) {
  return 0;
}

int clean_suite_heuristic(void) {
  return 0;
}

void test_is_mate(void) {
  char* white_mate_fen = "6rr/4pq2/3k4/4p3/8/8/8/B5KR w - - 0 1";
  char* black_mate_fen = "6RR/4PQ2/3K4/4P3/8/8/8/b5kr b - - 0 1";
  char* initial_fen =
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

  Board white_mate;
  Board black_mate;
  Board no_mate;

  fenToBoard(white_mate_fen, &white_mate);
  fenToBoard(black_mate_fen, &black_mate);
  fenToBoard(initial_fen, &no_mate);

  CU_ASSERT_EQUAL(is_mate(white_mate), white);
  CU_ASSERT_EQUAL(is_mate(black_mate), black);
  CU_ASSERT_EQUAL(is_mate(no_mate), neutral);
}

void test_update_threat(void) {
  Board board;
  int threat[8][8];
  initAGame(&board);

  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      board.square[i][j].piece = empty;
      board.square[i][j].color = neutral;
      // todo initialise this value
      threat[i][j] = 123454626;
    }
  }

  board.square[3][3].piece = pawn;
  board.square[3][3].color = white;
  board.square[4][5].piece = knight;
  board.square[4][5].color = black;
  board.square[6][3].piece = pawn;
  board.square[6][3].color = white;
  board.square[6][5].piece = rook;
  board.square[6][5].color = black;
  board.square[7][4].piece = pawn;
  board.square[7][4].color = black;

  update_threat(threat, black, board);

  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      if (i == 3 && j == 3) {
        CU_ASSERT_EQUAL(threat[i][j], 1);
      } else if (i == 6 && j == 3) {
        CU_ASSERT_EQUAL(threat[i][j], 2);
      } else {
        CU_ASSERT_EQUAL(threat[i][j], 0);
      }
    }
  }
}

void test_update_protection(void) {
  Board board;
  initAGame(&board);
  int threat[8][8];
  int protect[8][8];

  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      board.square[i][j].piece = empty;
      board.square[i][j].color = neutral;
      // todo initialise these values
      threat[i][j] = 21334;
      protect[i][j] = 13256;
    }
  }

  board.square[3][3].piece = pawn;
  board.square[3][3].color = white;
  board.square[4][5].piece = knight;
  board.square[4][5].color = black;
  board.square[6][3].piece = pawn;
  board.square[6][3].color = white;
  board.square[6][5].piece = rook;
  board.square[6][5].color = black;
  board.square[7][4].piece = pawn;
  board.square[7][4].color = black;

  board.square[2][2].piece = pawn;
  board.square[2][2].color = white;
  board.square[6][1].piece = rook;
  board.square[6][1].color = white;
  board.square[5][2].piece = pawn;
  board.square[5][2].color = white;

  update_threat(threat, black, board);
  update_protection(threat, protect, white, board);

  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      if (i == 3 && j == 3) {
        CU_ASSERT_EQUAL(protect[i][j], 1);
      } else if (i == 6 && j == 3) {
        CU_ASSERT_EQUAL(protect[i][j], 2);
      } else {
        CU_ASSERT_EQUAL(protect[i][j], -1);
      }
    }
  }
}

void test_heuristic(void) {
  /* heuristic function should return 0 with the fen representing
     the initial position */

  Board start;
  initAGame(&start);
  CU_ASSERT_EQUAL(heuristic(start), 0);

  /* When mat function should returns 500 (which is a little exception to
     the rule of computation only with current position) and not
     the normal score */

  char* mate_fen = "6rk/4pq2/3r4/8/8/8/8/B5KR w - - 0 1";
  Board mate;
  initAGame(&mate);

  fenToBoard(mate_fen, &mate);
  CU_ASSERT_EQUAL(heuristic(mate), 500);

  initAGame(&mate);
  play_move(5254, &mate);
  play_move(6775, &mate);
  play_move(1022, &mate);
  play_move(605, &mate);
  play_move(4051, &mate);
  play_move(7563, &mate);

  printBoardAndData(mate);

  CU_ASSERT_EQUAL(heuristic(mate), 500);
  CU_ASSERT_EQUAL(is_mate(mate), white);

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
  initAGame(&white_normal);
  Board white_reverse;
  initAGame(&white_reverse);

  fenToBoard(white_normal_fen, &white_normal);
  fenToBoard(white_reverse_fen, &white_reverse);

  CU_ASSERT_EQUAL((heuristic(white_normal) +
                    heuristic(white_reverse)), 0);

  /* Doing the same but by inversing the turn (w or b at the and of the FEN)
     rather than replacing uppercase by lowercase letters */

  char* white_fen =
    "rnbqkb1r/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq - 1 2";
  char* black_fen =
    "rnbqkb1r/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2";

  Board white;
  initAGame(&white);
  Board black;
  initAGame(&black);

  fenToBoard(white_fen, &white);
  fenToBoard(black_fen, &black);

  CU_ASSERT_EQUAL((heuristic(white) + heuristic(black)), 0);

  /* Assert that a piece in danger counts only half the value, with
     two computations, one with the pawn safe, and the second in danger */

  char* safe_fen = "rnbqkb1r/pppppppp/5n2/8/3P4/8/PPP1PPPP/RNBQKBNR w - - 0 1";
  char* danger_fen = "r1bqkbnr/pppppppp/n7/8/1P4/8/P1PPPPPP/RNBQKBNR w - - 0 1";

  Board safe;
  initAGame(&safe);
  Board danger;
  initAGame(&danger);

  fenToBoard(safe_fen, &safe);
  fenToBoard(danger_fen, &danger);

  CU_ASSERT_EQUAL(heuristic(safe), heuristic(danger) + 10/2);

  /* Assert that a piece in danger but protected is worth the original value */

  char* p_fen = "r1bqkbnr/pppppppp/2n5/8/3P4/5N2/PPP1PPPP/RNBQKB1R w - - 0 1";

  Board protected;
  initAGame(&protected);
  fenToBoard(p_fen, &protected);

  CU_ASSERT_EQUAL(heuristic(safe), heuristic(protected)-10*1/2);
}

