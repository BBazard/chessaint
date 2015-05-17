/* This file is part of the ChessAInt project 2015 */

#ifndef TESTS_INCLUDE_ASTAR_SUITE_H_
#define TESTS_INCLUDE_ASTAR_SUITE_H_

#include "CUnit/Basic.h"
#include "include/astar.h"

int init_suite_astar(void);
int clean_suite_astar(void);

void test_move_to_node(void);
void test_next_gen(void);
void test_astar(void);

#endif /* TESTS_INCLUDE_ASTAR_SUITE_H_ */

