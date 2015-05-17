/* This file is part of the ChessAInt project 2015 */

#ifndef TESTS_INCLUDE_IDENTIFIER_SUITE_H_
#define TESTS_INCLUDE_IDENTIFIER_SUITE_H_

#include "CUnit/Basic.h"
#include "include/identifier.h"

int init_suite_identifier(void);
int clean_suite_identifier(void);

void test_stack_contract(void);

void test_stack_alloc(void);
void test_stack_pop(void);
void test_stack_push(void);
void test_stack_length(void);

void test_identifier_print(void);
void test_identifier_is_leaf(void);
void test_identifier_is_white(void);
void test_identifier_is_passant(void);
void test_identifier_get_cast(void);
void test_identifier_get_halfmove(void);
void test_identifier_get_fullmove(void);

void test_identifier_to_stack(void);

void test_float_to_int(void);

#endif /* TESTS_INCLUDE_IDENTIFIER_SUITE_H_ */

