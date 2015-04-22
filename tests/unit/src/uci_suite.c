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

void test_uciToMove(void) {
  CU_ASSERT_EQUAL(uciToMove("b2b2"), 1111);
  CU_ASSERT_EQUAL(uciToMove("c3b2"), 2211);
  CU_ASSERT_EQUAL(uciToMove("h8h8"), 7777);
  CU_ASSERT_EQUAL(uciToMove("e2e4"), 4143);
}

void test_rmUCILastCharacter(void) {
  char buffer[5];
  char* word = "e1e2\n";

  rmUCILastCharacter(word, buffer);
  CU_ASSERT_STRING_EQUAL(buffer, "e1e2");
}

