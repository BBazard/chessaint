/* This file is part of the ChessAInt project 2015 */

#ifndef TESTS_UNIT_INCLUDE_LLIST_SUITE_H_
#define TESTS_UNIT_INCLUDE_LLIST_SUITE_H_

#include "CUnit/Basic.h"
#include "include/llist.h"

int init_suite_graph(void);

int clean_suite_graph(void);

void test_arc_equal(void);
void test_llist_add(void);
void test_llist_suppr(void);
void test_llist_free(void);

#endif /* TESTS_UNIT_INCLUDE_LLIST_SUITE_H_ */
