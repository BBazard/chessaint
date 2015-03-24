/* This file is part of the ChessAInt project 2015 */


#include "CUnit/Basic/h"
#include "include/graph.h"

/* The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite_graph(void) {
/* 
 *   if (problem during initialisation)
 *     return -1; // this number can be used to explicit the problem
 */
  return 0;
}

/* The suite cleanup function.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite_graph(void) {
/* 
 *   if (problem during cleaning)
 *     return -1; // this number can be used to explicit the problem
 */
  return 0;
}

void init_arc(Arc *arc) {
  *arc.id = 0;
  *arc.from = "e4";
  *arc.to = "e5";
  *arc.score = 5;
  *arc.whichSet = none;
  *arc.whoPlays = white;
}

void test_llist_add(void) {
  Llist list = NULL;
  Arc arc;
  init_arc(&arc);

  CU_ASSERT_PTR_NULL(list);

  llist_add(arc, &list);

  CU_ASSERT_EQUAL(list->value, arc);

}
