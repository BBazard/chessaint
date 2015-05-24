/* This file is part of the ChessAInt project 2015 */
/**
 * @file
 */

#include "include/uci.h"
#include <string.h>
#include <sys/types.h>

/**
 * Print an error message
 * and stop the engine
 */
void manageErrors(char *msg) {
  fprintf(stderr, "Error ! Details : %s", msg);
  exit(EXIT_FAILURE);
}

/**
 * Send uci string to the gui
 */
void send(FILE *log, char buffer[UCI_SIZE]) {
  printf("%s\n", buffer);
  if (log != NULL)
    // extra padding spaces to align display
    fprintf(log, "sent to gui       : %s\n", buffer);
}

/**
 * Receive uci string from the gui
 * and put it in the variable buffer
 */
void receive(FILE *log, char buffer[UCI_SIZE]) {
  if (!fgets(buffer, UCI_SIZE, stdin))
    manageErrors("can't read");
  if (log != NULL)
    fprintf(log, "received from gui : %s", buffer);
}

/**
 * return the first word of a string
 *
 * * if the string contains no whitespace, return the string
 * * if the string contains at least a whitespace,
 * return the first characters until the first whitespace excluded
 *
 * example :
 * "word" -> "word"
 * "long sentence" -> "long"
 * 
 * @see getNextWord
 */
char* getFirstWord(char* sentence) {
  return strtok(sentence, " ");
}

/**
 * apply getFirstWord on the last string
 * called by getFistWord minus the return value of getFirstWord
 * 
 * examples :
 * getFirstWord("very long sentence") -> "very"
 * getNextWord() : "long"
 *
 * @see getFirstWord
 */
char* getNextWord() {
  return strtok(NULL, " ");
}

/**
 * example : "qmslqdjfk" -> 'k'
 * @note for the uci string the line
 * end with '\\n' and this is why this
 * function was created originally
 *
 */
char getLastCharacter(char* input) {
  char *bla = input + strlen(input) - 1;
  return *bla;
}

/**
 * convert a uci string into an int
 *
 * example : "c3b2" -> 2211
 */
int uciToMove(char* input) {
  int ans = 0;
  int base = 10;
  ans += input[0] - 'a';
  ans *= base;
  ans += input[1] - '1';
  ans *= base;
  ans += input[2] - 'a';
  ans *= base;
  ans += input[3] - '1';
  return ans;
}

/**
 * removes the trailing '\\n' in the end
 * of a uci string "input" like "a3b4\n"
 * and put it int the string "output" like "a3b4"
 *
 * example : "a3b4\n" -> "a3b4"
 */
void rmUCILastCharacter(char* input, char output[5]) {
  if (strlen(input) != 5)
    manageErrors("bad input in rmUCILastCharacter");

  strncpy(output, input, 4);
  output[4] = '\0';
}

/**
 * convert 4 int in a uci string
 * put the result in "str"
 *
 * example : (1, 2, 3, 4) -> "b3d5"
 *
 */
void getUciString(int a, int b, int c, int d, char str[5]) {
  str[0] = a + 'a';
  str[1] = b + '1';
  str[2] = c + 'a';
  str[3] = d + '1';
  str[4] = '\0';
}

