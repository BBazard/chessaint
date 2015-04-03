/* This file is part of the ChessAInt project 2015 */

#ifndef TESTS_UNIT_INCLUDE_IDENTIFIER_SUITE_H_
#define TESTS_UNIT_INCLUDE_IDENTIFIER_SUITE_H_

#include "CUnit/Basic.h"
#include "include/identifier.h"

int init_suite_identifier(void);
int clean_suite_identifier(void);

void test_path_init(void);
void test_path_reset(void);

void test_identifier_print(void);

#endif /* TESTS_UNIT_INCLUDE_IDENTIFIER_SUITE_H_ */
