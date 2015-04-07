/* This file is part of the ChessAInt project 2015 */

#include "CUnit/Basic.h"
#include "include/identifier.h"

#include <time.h>

/* The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite_identifier(void) {
/* 
 *   if (problem during initialisation)
 *     return -1; // this number can be used to explicit the problem
 */
  return 0;
}

/* The suite cleanup function.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite_identifier(void) {
/* 
 *   if (problem during cleaning)
 *     return -1; // this number can be used to explicit the problem
 */
  return 0;
}

void test_path_init(void) {
  /* The path element to init */
  Path path_to_init = path_init(10);

  /* Assert malloced pointer is not null */
  CU_ASSERT_PTR_NOT_NULL(path_to_init.array);
}

void test_path_reset(void) {
  /* The path element to reset */
  Path path_to_reset = path_init(10);

  /* Change current pointer to NULL and then apply path_reset function */
  path_to_reset.current = NULL;
  path_reset(&path_to_reset);

  /* Assert pointer current is equal to static pointer array */
  CU_ASSERT_PTR_EQUAL(path_to_reset.array, path_to_reset.current);
}

void test_stack_init(void) {
  Stack s;
  stack_init(&s);

  CU_ASSERT_EQUAL(mpz_cmp_ui(s, 0), 0);

  stack_free(&s);
}

void test_stack_push(void) {
  Stack s;
  stack_init(&s);

  int to_push1 = 12345;
  int to_push2 = 6789;
  int to_push3 = 987654321;
  mpz_t tmp;

  mpz_init_set_str(tmp, "12345", 10);
  stack_push(&s, to_push1);

  CU_ASSERT_FALSE(mpz_cmp(tmp, s));

  mpz_set_str(tmp, "12345000006789", 10);
  stack_push(&s, to_push2);

  CU_ASSERT_FALSE(mpz_cmp(tmp, s));

  mpz_set_str(tmp, "12345000006789987654321", 10);
  stack_push(&s, to_push3);

  CU_ASSERT_FALSE(mpz_cmp(tmp, s));
  stack_free(&s);
  mpz_clear(tmp);
}

void test_stack_pop(void) {
  Stack s;

  int to_pop1 = 12345;
  int to_pop2 = 6789;
  int to_pop3 = 987654321;
  mpz_init_set_str(s, "12345000006789987654321", 10);

  CU_ASSERT_EQUAL(stack_pop(&s), to_pop3);
  CU_ASSERT_EQUAL(stack_pop(&s), to_pop2);
  CU_ASSERT_EQUAL(stack_pop(&s), to_pop1);

  stack_free(&s);
}


void test_identifier_print(void) {
  Identifier id;
  mpz_init_set_str(id, "1010101010101010101010101010101010101010101010", 10);

  /* Prints an identifier */
  identifier_print(id);
}

void test_identifier_is_leaf(void) {
  Identifier id_is_leaf;
  mpz_init_set_str(id_is_leaf, "5254200045", 10);
  Identifier id_not_leaf;
  mpz_init_set_str(id_not_leaf, "5254100045", 10);

  CU_ASSERT_TRUE(identifier_is_leaf(id_is_leaf));
  CU_ASSERT_FALSE(identifier_is_leaf(id_not_leaf));
}

void test_identifier_is_white(void) {
  Identifier id_is_white;
  mpz_init_set_str(id_is_white, "5254100045", 10);
  Identifier id_not_white;
  mpz_init_set_str(id_not_white, "5254200045", 10);

  CU_ASSERT_TRUE(identifier_is_white(id_is_white));
  CU_ASSERT_FALSE(identifier_is_white(id_not_white));
}

void test_identifier_is_passant(void) {
  Identifier id_is_passant;
  mpz_init_set_str(id_is_passant, "5254010045", 10);
  Identifier id_not_passant;
  mpz_init_set_str(id_not_passant, "5254000045", 10);

  CU_ASSERT_TRUE(identifier_is_passant(id_is_passant));
  CU_ASSERT_FALSE(identifier_is_passant(id_not_passant));
}

void test_identifier_get_cast(void) {
  Identifier id_no_cast;
  mpz_init_set_str(id_no_cast, "5254000045", 10);
  Identifier id_q;
  mpz_init_set_str(id_q, "5254100145", 10);
  Identifier id_KQkq;
  mpz_init_set_str(id_KQkq, "5254101645", 10);

  CU_ASSERT_EQUAL(identifier_get_cast(id_no_cast), 0);
  CU_ASSERT_EQUAL(identifier_get_cast(id_q), 1);
  CU_ASSERT_EQUAL(identifier_get_cast(id_KQkq), 16);
}

void test_identifier_get_halfmove(void) {
  Identifier id_halfmove_45;
  mpz_init_set_str(id_halfmove_45, "5254101645", 10);

  CU_ASSERT_EQUAL(identifier_get_halfmove(id_halfmove_45), 45);
}

void test_identifier_get_fullmove(void) {
  Identifier id_fullmove_5;
  mpz_init_set_str(id_fullmove_5, "11112222333344445555101645", 10);

  CU_ASSERT_EQUAL(identifier_get_fullmove(id_fullmove_5), 5);
}
