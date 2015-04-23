/* This file is part of the ChessAInt project 2015 */

#include "CUnit/Basic.h"
#include "include/concatenate.h"

/* The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite_concatenate(void) {
/*
 *   if (problem during initialisation)
 *     return -1; // this number can be used to explicit the problem
 */
  return 0;
}

/* The suite cleanup function.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite_concatenate(void) {
/*
 *   if (problem during cleaning)
 *     return -1; // this number can be used to explicit the problem
 */
  return 0;
}

void test_concatenate(void) {
   char str[5] ;
   getUciString(0, 1, 2, 3, str);
   CU_ASSERT_STRING_EQUAL(str, "a2c4");
}
