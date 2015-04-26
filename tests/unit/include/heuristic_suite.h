/* This file is part of the ChessAInt project 2015 */

#ifndef TESTS_UNIT_INCLUDE_HEURISTIC_SUITE_H_
#define TESTS_UNIT_INCLUDE_HEURISTIC_SUITE_H_

#include "CUnit/Basic.h"
#include "include/heuristic.h"

int init_suite_heuristic(void);
int clean_suite_heuristic(void);

void test_is_mate(void);
void test_update_threat(void);
void test_update_protection(void);
void test_heuristic(void);

#endif /* TESTS_UNIT_INCLUDE_HEURISTIC_SUITE_H_ */
