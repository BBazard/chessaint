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

void test_identifier_print(void) {
  Identifier id;

  /* Prints an identifier */
  mpz_init_set_str(id, "1010101010101010101010101010101010101010101010", 10);
  identifier_print(id);
}
