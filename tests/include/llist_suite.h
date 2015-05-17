/* This file is part of the ChessAInt project 2015 */

#ifndef TESTS_INCLUDE_LLIST_SUITE_H_
#define TESTS_INCLUDE_LLIST_SUITE_H_

#include "CUnit/Basic.h"
#include "include/llist.h"

int init_suite_llist(void);
int clean_suite_llist(void);

void test_node_equal(void);
void test_llist_add(void);
void test_llist_rm_first(void);
void test_llist_free(void);
void test_llist_shorten(void);
void test_llist_length(void);
void test_llist_concatenate(void);
void test_node_extract(void);

#endif /* TESTS_INCLUDE_LLIST_SUITE_H_ */

