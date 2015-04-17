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

void test_arc_equal(void) {
  Arc left, right;
  arc_init(&left);
  arc_init(&right);
  left.score = 150;
  right.score = 150;

  /* When left and right are equal */
  CU_ASSERT_TRUE(arc_is_equal(left, right));

  /* change right to have different values in left and right */
  right.score++;

  /* When left and right are not equal */
  CU_ASSERT_FALSE(arc_is_equal(left, right));
}

void test_llist_add(void) {
  Llist list = NULL;
  Arc arc;
  arc_init(&arc);
  arc.score = 150;

  /* list should be NULL */
  CU_ASSERT_PTR_NULL(list);

  /* Add the arc to the list */
  llist_add(arc, &list);

  /* Look if the data contained in the list are the same than the arc added */
  CU_ASSERT_TRUE(arc_is_equal(list->value, arc));

  /* Add a new arc */
  arc.score++;
  llist_add(arc, &list);

  /* Look if the arc has been added BEFORE the first one
     (because his score is higher) */
  CU_ASSERT_TRUE(arc_is_equal(list->value, arc));

  /* Add another arc */
  arc.score -= 2;
  llist_add(arc, &list);

  /* Look if the arc at the top has not changed
     (because his score is lower) */
  arc.score += 2;
  CU_ASSERT_TRUE(arc_is_equal(list->value, arc));
}

void test_llist_suppr(void) {
  Llist list = NULL;
  Arc arc1;
  Arc arc2;
  arc_init(&arc1);
  arc_init(&arc2);
  arc1.score = 150;
  arc2.score = 151;

  /* See if trying to suppress an element of an empty list works */
  CU_ASSERT_TRUE(llist_suppr(&list));

  /* Add something in order to suppress it later */
  llist_add(arc1, &list);
  llist_add(arc2, &list);

  /* Suppress the first element of the list */
  llist_suppr(&list);

  /* See if the remaining list have arc2 has its first element */
  CU_ASSERT_TRUE(arc_is_equal(list->value, arc1));

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
  arc1.score = 150;
  arc2.score = 151;

  /* Add something in order to suppress it later */
  llist_add(arc1, &list);
  llist_add(arc2, &list);

  /* Free the list */
  llist_free(&list);

  /* Test if llist_free returns a NULL pointing list */
  CU_ASSERT_PTR_NULL(list);
}
