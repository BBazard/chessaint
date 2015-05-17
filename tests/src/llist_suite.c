/* This file is part of the ChessAInt project 2015 */

#include "CUnit/Basic.h"
#include "include/llist.h"

int init_suite_llist(void) {
  return 0;
}

int clean_suite_llist(void) {
  return 0;
}

void test_node_equal(void) {
  Node left, right;
  node_alloc(&left);
  node_alloc(&right);
  left.score = 150;
  right.score = 150;

  /* When left and right are equal */
  CU_ASSERT_TRUE(node_is_equal(left, right));

  /* change right to have different values in left and right */
  right.score++;

  /* When left and right are not equal */
  CU_ASSERT_FALSE(node_is_equal(left, right));

  node_free(&left);
  node_free(&right);
}

void test_llist_add(void) {
  Llist list = NULL;
  Node node;
  node_alloc(&node);
  node.score = 150;
  mpz_set_str(*(node.data), "1234", 10);

  /* list should be NULL */
  CU_ASSERT_PTR_NULL(list);

  /* Add the node to the list */
  llist_add(node, &list);

  /* Look if the data contained in the list are the same than the node added */
  CU_ASSERT_TRUE(node_is_equal(list->value, node));

  /* int i = 1; */
  /* Element *tmp = list; */
  /* while (tmp != NULL) { */
  /*   printf("#n = %d\n", i++); */
  /*   node_print(tmp->value); */
  /*   tmp = tmp->next; */
  /* } */

  /* Add a new node */
  node.score++;
  mpz_set_str(*(node.data), "5678", 10);
  llist_add(node, &list);

  /* Look if the node has been added BEFORE the first one
     (because his score is higher) */
  CU_ASSERT_TRUE(node_is_equal(list->value, node));

  /* Add another node */
  node.score -= 2;
  llist_add(node, &list);

  /* Look if the node at the top has not changed
     (because his score is lower) */
  node.score += 2;
  CU_ASSERT_TRUE(node_is_equal(list->value, node));

  /* i = 0; */
  /* tmp = list; */
  /* while (tmp != NULL) { */
  /*   printf("#n = %d\n", i++); */
  /*   node_print(tmp->value); */
  /*   tmp = tmp->next; */
  /* } */

  llist_free(&list);
  node_free(&node);
}

void test_llist_rm_first(void) {
  Llist list = NULL;
  Node arc1;
  Node arc2;
  node_alloc(&arc1);
  node_alloc(&arc2);
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
  CU_ASSERT_TRUE(node_is_equal(list->value, arc1));

  /* See deleting an element returns 0 */
  CU_ASSERT_FALSE(llist_rm_first(&list));

  /* Confirm the list is now a NULL pointer */
  CU_ASSERT_PTR_NULL(list);

  node_free(&arc1);
  node_free(&arc2);
}

void test_llist_free(void) {
  Llist list = NULL;
  Node arc1;
  Node arc2;
  node_alloc(&arc1);
  node_alloc(&arc2);
  arc1.score = 150;
  arc2.score = 151;

  /* Add something in order to suppress it later */
  llist_add(arc1, &list);
  llist_add(arc2, &list);

  /* Free the list */
  llist_free(&list);

  /* Test if llist_free returns a NULL pointing list */
  CU_ASSERT_PTR_NULL(list);

  node_free(&arc1);
  node_free(&arc2);
}

void test_llist_shorten(void) {
  Node node;
  Llist list = NULL;
  node_alloc(&node);
  node.score = 0;
  for (int i = 0; i < 50; ++i) {
    llist_add(node, &list);
    node.score++;
  }
  node_free(&node);

  /* int i = 1; */
  /* Element *tmp = list; */
  /* while (tmp != NULL) { */
  /*   printf("#n = %d\n", i++); */
  /*   node_print(tmp->value); */
  /*   tmp = tmp->next; */
  /* } */

  /* printf("%d", llist_shorten(&list, 60)); */
  /* printf("%d", llist_shorten(&list, 30)); */

  /* i = 1; */
  /* tmp = list; */
  /* while (tmp != NULL) { */
  /*   printf("#n = %d\n", i++); */
  /*   node_print(tmp->value); */
  /*   tmp = tmp->next; */
  /* } */
  llist_free(&list);
}

void test_llist_length(void) {
  Node node;
  Llist list = NULL;
  node_alloc(&node);
  node.score = 0;
  for (int i = 0; i < 50; ++i) {
    llist_add(node, &list);
    node.score++;
  }
  node_free(&node);

  CU_ASSERT_EQUAL(llist_length(list), 50);

  llist_free(&list);
}

void test_node_extract(void) {
  Node node;
  node_alloc(&node);
  Stack s;
  stack_alloc(&s);
  node.score = 143;

  stack_push(&s, 4142);
  stack_push(&s, 4243);
  stack_push(&s, 4344);
  stack_push(&s, 4445);
  stack_to_identifier(node.data, s, 111111);

  /* node_print(node); */

  int move, score;
  node_extract(node, &move, &score);
  CU_ASSERT_EQUAL(move, 4142);
  CU_ASSERT_EQUAL(score, 143);

  stack_free(&s);
  node_free(&node);
}

void test_llist_concatenate(void) {
  Llist list1 = NULL;
  Llist list2 = NULL;
  Node node;
  node_alloc(&node);

  for (int i = 0; i < 4; ++i) {
    llist_add(node, &list1);
    node.score += 10;
    llist_add(node, &list2);
    node.score -= 9;
  }

  /* printf("LIST 1 \n\n"); */

  /* int i = 1; */
  /* Element *tmp = list1; */
  /* while (tmp != NULL) { */
  /*   printf("#n = %d\n", i++); */
  /*   node_print(tmp->value); */
  /*   tmp = tmp->next; */
  /* } */

  /* printf("LIST 2 \n\n"); */

  /* i = 1; */
  /* tmp = list2; */
  /* while (tmp != NULL) { */
  /*   printf("#n = %d\n", i++); */
  /*   node_print(tmp->value); */
  /*   tmp = tmp->next; */
  /* } */

  /* llist_concatenate(&list1, list2); */

  /* printf("LIST 1+2\n\n"); */

  /* i = 1; */
  /* tmp = list1; */
  /* while (tmp != NULL) { */
  /*   printf("#n = %d\n", i++); */
  /*   node_print(tmp->value); */
  /*   tmp = tmp->next; */
  /* } */

  llist_free(&list1);
  llist_free(&list2);
  node_free(&node);
}

