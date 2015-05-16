/* This file is part of the ChessAInt project 2015 */

#include "CUnit/Basic.h"
#include "include/llist.h"

int init_suite_llist(void) {
  return 0;
}

int clean_suite_llist(void) {
  return 0;
}

void test_arc_equal(void) {
  Arc left, right;
  arc_alloc(&left);
  arc_alloc(&right);
  left.score = 150;
  right.score = 150;

  /* When left and right are equal */
  CU_ASSERT_TRUE(arc_is_equal(left, right));

  /* change right to have different values in left and right */
  right.score++;

  /* When left and right are not equal */
  CU_ASSERT_FALSE(arc_is_equal(left, right));

  arc_free(&left);
  arc_free(&right);
}

void test_llist_add(void) {
  Llist list = NULL;
  Arc arc;
  arc_alloc(&arc);
  arc.score = 150;
  mpz_set_str(*(arc.data), "1234", 10);

  /* list should be NULL */
  CU_ASSERT_PTR_NULL(list);

  /* Add the arc to the list */
  llist_add(arc, &list);

  /* Look if the data contained in the list are the same than the arc added */
  CU_ASSERT_TRUE(arc_is_equal(list->value, arc));

  /* int i = 1; */
  /* Element *tmp = list; */
  /* while (tmp != NULL) { */
  /*   printf("#n = %d\n", i++); */
  /*   arc_print(tmp->value); */
  /*   tmp = tmp->next; */
  /* } */

  /* Add a new arc */
  arc.score++;
  mpz_set_str(*(arc.data), "5678", 10);
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

  /* i = 0; */
  /* tmp = list; */
  /* while (tmp != NULL) { */
  /*   printf("#n = %d\n", i++); */
  /*   arc_print(tmp->value); */
  /*   tmp = tmp->next; */
  /* } */

  arc_free(&arc);
}

void test_llist_rm_first(void) {
  Llist list = NULL;
  Arc arc1;
  Arc arc2;
  arc_alloc(&arc1);
  arc_alloc(&arc2);
  arc1.score = 150;
  arc2.score = 151;

  /* See if trying to suppress an element of an empty list works */
  CU_ASSERT_TRUE(llist_rm_first(&list));

  /* Add something in order to suppress it later */
  llist_add(arc1, &list);
  llist_add(arc2, &list);

  /* Suppress the first element of the list */
  llist_rm_first(&list);

  /* See if the remaining list have arc2 has its first element */
  CU_ASSERT_TRUE(arc_is_equal(list->value, arc1));

  /* See deleting an element returns 0 */
  CU_ASSERT_FALSE(llist_rm_first(&list));

  /* Confirm the list is now a NULL pointer */
  CU_ASSERT_PTR_NULL(list);

  arc_free(&arc1);
  arc_free(&arc2);
}

void test_llist_free(void) {
  Llist list = NULL;
  Arc arc1;
  Arc arc2;
  arc_alloc(&arc1);
  arc_alloc(&arc2);
  arc1.score = 150;
  arc2.score = 151;

  /* Add something in order to suppress it later */
  llist_add(arc1, &list);
  llist_add(arc2, &list);

  /* Free the list */
  llist_free(&list);

  /* Test if llist_free returns a NULL pointing list */
  CU_ASSERT_PTR_NULL(list);

  arc_free(&arc1);
  arc_free(&arc2);
}

void test_llist_shorten(void) {
  Arc arc;
  Llist list = NULL;
  arc_alloc(&arc);
  arc.score = 0;
  for (int i = 0; i < 50; ++i) {
    llist_add(arc, &list);
    arc.score++;
  }
  arc_free(&arc);

  /* int i = 1; */
  /* Element *tmp = list; */
  /* while (tmp != NULL) { */
  /*   printf("#n = %d\n", i++); */
  /*   arc_print(tmp->value); */
  /*   tmp = tmp->next; */
  /* } */

  /* printf("%d", llist_shorten(&list, 60)); */
  /* printf("%d", llist_shorten(&list, 30)); */

  /* i = 1; */
  /* tmp = list; */
  /* while (tmp != NULL) { */
  /*   printf("#n = %d\n", i++); */
  /*   arc_print(tmp->value); */
  /*   tmp = tmp->next; */
  /* } */
}

void test_llist_length(void) {
  Arc arc;
  Llist list = NULL;
  arc_alloc(&arc);
  arc.score = 0;
  for (int i = 0; i < 50; ++i) {
    llist_add(arc, &list);
    arc.score++;
  }
  arc_free(&arc);

  CU_ASSERT_EQUAL(llist_length(list), 50);
}

void test_arc_extract(void) {
  Arc arc;
  arc_alloc(&arc);
  Stack s;
  stack_alloc(&s);
  arc.score = 143;

  stack_push(&s, 4142);
  stack_push(&s, 4243);
  stack_push(&s, 4344);
  stack_push(&s, 4445);
  stack_to_identifier(arc.data, s, 111111);

  /* arc_print(arc); */

  int move, score;
  arc_extract(arc, &move, &score);
  CU_ASSERT_EQUAL(move, 4142);
  CU_ASSERT_EQUAL(score, 143);
}

void test_llist_concatenate(void) {
  Llist list1 = NULL;
  Llist list2 = NULL;
  Arc arc;
  arc_alloc(&arc);

  for (int i = 0; i < 4; ++i) {
    llist_add(arc, &list1);
    arc.score += 10;
    llist_add(arc, &list2);
    arc.score -= 9;
  }

  /* printf("LIST 1 \n\n"); */

  /* int i = 1; */
  /* Element *tmp = list1; */
  /* while (tmp != NULL) { */
  /*   printf("#n = %d\n", i++); */
  /*   arc_print(tmp->value); */
  /*   tmp = tmp->next; */
  /* } */

  /* printf("LIST 2 \n\n"); */

  /* i = 1; */
  /* tmp = list2; */
  /* while (tmp != NULL) { */
  /*   printf("#n = %d\n", i++); */
  /*   arc_print(tmp->value); */
  /*   tmp = tmp->next; */
  /* } */

  /* llist_concatenate(&list1, list2); */

  /* printf("LIST 1+2\n\n"); */

  /* i = 1; */
  /* tmp = list1; */
  /* while (tmp != NULL) { */
  /*   printf("#n = %d\n", i++); */
  /*   arc_print(tmp->value); */
  /*   tmp = tmp->next; */
  /* } */
  arc_free(&arc);
}
