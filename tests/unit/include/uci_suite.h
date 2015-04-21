/* This file is part of the ChessAInt project 2015 */

#ifndef TESTS_UNIT_INCLUDE_UCI_SUITE_H_
#define TESTS_UNIT_INCLUDE_UCI_SUITE_H_

#include "include/uci.h"
#include "CUnit/Basic.h"

int init_suite_uci(void);
int clean_suite_uci(void);

void test_basic_case(void);

void test_whitespaces(void);

#endif /* TESTS_UNIT_INCLUDE_UCI_SUITE_H_ */

