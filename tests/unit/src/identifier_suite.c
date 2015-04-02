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

void test_identifier_path(void) {
  /* Initialisation of the random seed */
  time_t t;
  srand((unsigned) time(&t));

  /* Array to stock the expected solution */
  unsigned long int init_path[20];
  int i;

  init_path[0] = 1;

  /* Identifier to test (and a temporary for computation) */
  Identifier id_to_test;
  Identifier tmp;
  mpz_init_set_str(id_to_test, "1", 10);
  mpz_init(tmp);

  /* Create both the array and the identifier */
  for (i=1; i < 20; i++) {
    init_path[i] = rand()%SON_MAX_NB;
    mpz_set(tmp, id_to_test);
    mpz_mul_ui(id_to_test, tmp, SON_MAX_NB);
    mpz_set(tmp, id_to_test);
    mpz_add_ui(id_to_test, tmp, init_path[i]);
  }

  /* Initialisation of the path for computation */
  Path path = path_init(20);

  /* Assert pointer malloced is not null */
  CU_ASSERT_PTR_NOT_NULL_FATAL(path.array);

  /* Execution of the function to test */
  identifier_path(id_to_test, &path);

  /* Assert each number of arc computed is equal to expected */
  for (i=0; i < 20; i++) {
    CU_ASSERT_EQUAL(init_path[i], path.array[i]);
  }
}
