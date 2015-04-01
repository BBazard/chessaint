/* This file is part of the ChessAInt project 2015 */

#ifndef TESTS_UNIT_INCLUDE_HEURISTIC_SUITE_H_
#define TESTS_UNIT_INCLUDE_HEURISTIC_SUITE_H_

#include "CUnit/Basic.h"
#include "include/heuristic.h"

int init_suite_heuristic(void);
int clean_suite_heuristic(void);

void test_is_mat(void);
void test_number_of_char(void);
void test_heuristic_fen(void);

#endif /* TESTS_UNIT_INCLUDE_HEURISTIC_SUITE_H_ */
