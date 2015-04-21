/* This file is part of the ChessAInt project 2015 */

#include "include/uci.h"
#include "CUnit/Basic.h"

int init_suite_uci(void) {
  return 0;
}

int clean_suite_uci(void) {
  return 0;
}

void test_basic_case(void) {
  // char* don't work without strdup
  char sentence[] = "very long sentence\n";
  char anotherSentence[] = "random text\n";

  char* word = getFirstWord(sentence);

  CU_ASSERT_STRING_EQUAL(word, "very");

  word = getNextWord(sentence);
  CU_ASSERT_STRING_EQUAL(word, "long");

  word = getNextWord(sentence);
  CU_ASSERT_STRING_EQUAL(word, "sentence\n");

  word = getFirstWord(anotherSentence);
  CU_ASSERT_STRING_EQUAL(word, "random");
}

void test_whitespaces(void) {
  char sentence[] = "  very  long    sentence\n";

  char* word = getFirstWord(sentence);

  CU_ASSERT_STRING_EQUAL(word, "very");

  word = getNextWord(sentence);
  CU_ASSERT_STRING_EQUAL(word, "long");

  word = getNextWord(sentence);
  CU_ASSERT_STRING_EQUAL(word, "sentence\n");
}

