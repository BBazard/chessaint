/* This file is part of the ChessAInt project 2015 */

/**
 * @file
 * @todo handle error with a real stderr file
 * @todo create functions to open/close files
 * @todo parse uci strings
 */

#include "include/uci.h"
#include <string.h>
#include <sys/types.h>

/**
 * Print an error message
 * and stop the engine
 *
 * @todo stop the engine
 * with uci "quit" or something
 */
void manageErrors(char *msg) {
  fprintf(stderr, "Error ! Details : %s", msg);
  exit(EXIT_FAILURE);
}

/**
 * Compile the regex "compiled"
 * according to "pattern"
 *
 * @todo \\see pattern
 */
void regcompWrapper(regex_t *compiled, char *pattern) {
  int res = regcomp(compiled, pattern, REG_EXTENDED);
  if (res != 0)
    manageErrors(pattern);
}

/**
 * Compare "input" with the pattern in "compiled" and
 * fill "matchptr" with the matches
 * @return 1 if match
 * @return 0 if no match
 */
int regexecWrapper(const regex_t *compiled, const char *input,
                   regmatch_t *matchptr) {
  int res = regexec(compiled, input, compiled->re_nsub+1, matchptr, 0);

  if (res == REG_ESPACE) {
    char buffer[MSG_SIZE];
    regerror(res, compiled, buffer, sizeof(buffer));
    manageErrors(buffer);
  }

  return (res != REG_NOMATCH);
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
 * You need to call freeRegexes
 */
void initialiseRegexes(struct uciRegex *regexes) {
  regcompWrapper(&regexes->bla, "qdsmljkf");
}

void freeRegexes(struct uciRegex *regexes) {
  regfree(&regexes->bla);
}

int isQuit(FILE *log, char toCompare[UCI_SIZE]) {
  regex_t general;

  regcompWrapper(&general, "^(([^ ])+)\n$");

  regmatch_t *matchptr = calloc((general.re_nsub + 1), sizeof(regex_t));

  if (regexecWrapper(&general, toCompare, matchptr)) {
    fprintf(log, "\ninput %s", toCompare);

    for (size_t i = 0 ; i < general.re_nsub + 1 ; ++i) {
      fprintf(log, "match %ld : %d %d\n",
          i, matchptr[i].rm_so, matchptr[i].rm_eo);
    }

    fprintf(log, "\n");

    free(matchptr);
    regfree(&general);
    return 1;
  }

  free(matchptr);
  regfree(&general);
  return 0;
}

