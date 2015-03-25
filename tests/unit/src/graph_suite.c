/* This file is part of the ChessAInt project 2015 */

#include "CUnit/Basic.h"
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

void arc_init(Arc *arc) {
  arc->id = 0;
  strcpy(arc->from, "e4");
  strcpy(arc->to, "e5");
  arc->score = 5;
  arc->whichSet = none;
  arc->activeColor = 'b';
  arc->castlingAvailability = "-";
  arc->enPassant = "-";
  arc->halfmoveClock = 5;
  arc->fullmoveNumber = 3;
}

void test_arc_equal(void) {
  Arc left, right;
  arc_init(&left);
  arc_init(&right);

  /* When left and right are equal */
  CU_ASSERT_TRUE(arc_equal(left, right));

  /* change right to have different values in left and right */
  right.id++;

  /* When left and right are not equal */
  CU_ASSERT_FALSE(arc_equal(left, right));
}

void test_llist_add(void) {
  Llist list = NULL;
  Arc arc;
  arc_init(&arc);

  /* list should be NULL */
  CU_ASSERT_PTR_NULL(list);

  /* Add the arc to the list */
  llist_add(arc, &list);

  /* Look if the data contained in the list are the same than the arc added */
  CU_ASSERT_TRUE(arc_equal(list->value, arc));
}
