/* This file is part of the ChessAInt project 2015 */

#ifndef TESTS_UNIT_INCLUDE_IDENTIFIER_SUITE_H_
#define TESTS_UNIT_INCLUDE_IDENTIFIER_SUITE_H_

#include "CUnit/Basic.h"
#include "include/identifier.h"

int init_suite_identifier(void);
int clean_suite_identifier(void);

void test_stack_exchange(void);

void test_stack_init(void);
void test_stack_pop(void);
void test_stack_push(void);

void test_identifier_print(void);
void test_identifier_is_leaf(void);
void test_identifier_is_white(void);
void test_identifier_is_passant(void);
void test_identifier_get_cast(void);
void test_identifier_get_halfmove(void);
void test_identifier_get_fullmove(void);

#endif /* TESTS_UNIT_INCLUDE_IDENTIFIER_SUITE_H_ */
