/* This file is part of the ChessAInt project 2015 */

#include "CUnit/Basic.h"
#include "include/llist.h"

/* The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite_llist(void) {
/* 
 *   if (problem during initialisation)
 *     return -1; // this number can be used to explicit the problem
 */
  return 0;
}

/* The suite cleanup function.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite_llist(void) {
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

void test_llist_suppr(void) {
  Llist list = NULL;
  Arc arc1;
  Arc arc2;
  arc_init(&arc1);
  arc_init(&arc2);
  arc2.id++;

  /* See if trying to suppress an element of an empty list works */
  CU_ASSERT_TRUE(llist_suppr(&list));

  /* Add something in order to suppress it later */
  llist_add(arc1, &list);
  llist_add(arc2, &list);

  /* Suppress the first element of the list */
  llist_suppr(&list);

  /* See if the remaining list have arc2 has its first element */
  CU_ASSERT_TRUE(arc_equal(list->value, arc2));

  /* See deleting an element returns 0 */
  CU_ASSERT_FALSE(llist_suppr(&list));

  /* Confirm the list is now a NULL pointer */
  CU_ASSERT_PTR_NULL(list);
}

void test_llist_free(void) {
  Llist list = NULL;
  Arc arc1;
  Arc arc2;
  arc_init(&arc1);
  arc_init(&arc2);
  arc2.id++;

  /* Add something in order to suppress it later */
  llist_add(arc1, &list);
  llist_add(arc2, &list);

  /* Free the list */
  llist_free(&list);

  /* Test if llist_free returns a NULL pointing list */
  CU_ASSERT_PTR_NULL(list);
}
