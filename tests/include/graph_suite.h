/* This file is part of the ChessAInt project 2015 */

#ifndef TESTS_INCLUDE_GRAPH_SUITE_H_
#define TESTS_INCLUDE_GRAPH_SUITE_H_

#include "CUnit/Basic.h"
#include "include/graph.h"

int init_suite_graph(void);
int clean_suite_graph(void);

void test_isInBoardSquare(void);
void test_bishopMoveGenerator(void);
void test_rookMoveGenerator(void);
void test_queenMoveGenerator(void);
void test_knightMoveGenerator(void);
void test_kingMoveGenerator(void);
void test_pawnMoveGenerator1(void);
void test_pawnMoveGenerator2(void);
void test_castlesMoveGenerator(void);

void test_movesGenerator(void);

void test_play_move(void);
void test_update_board(void);

void test_findThreats(void);

void test_findAllPinnings(void);

void test_legalMoves2(void);
void test_legalMoves3(void);
void test_legalMoves4(void);
void test_legalMoves6(void);
void test_legalMoves7(void);
#endif /* TESTS_INCLUDE_GRAPH_SUITE_H_ */

