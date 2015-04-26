/* This file is part of the ChessAInt project 2015 */
/**
 *  @todo Need to add proper documentation
 *  @todo Correct syntax to have lint cleared
 *
 *  @todo If last bug is solved there's no need for second function anymore
 *
 *  @todo english pls (even comments not in doxygen)
 *
 *  @bug 'a'-'0' = 49 (= '1') why adding 49 to b ?
 *  this could be used to make second function less "mode bourrin"
 *  EX : 'a' - 49 = '0', 'b' - 49 = '1' etc ...
 *
 *  str[0] should take the value of a transformed in letter and then in char
 *  (this looks more or less ok)
 *  str[1] should take the value of b+1 transformed IN CHAR this don't work
 *  because the value of b is an int and you first need to tranform it into
 *  a char (see the ascii table : man ascii) it should be done by adding a
 *  constant number (such as 30 : see the table !)
 *  The same goes for str[3]
 *
 *
 */

#include "../include/concatenate.h"

void getUciString(int a, int b, int c, int d, char str[5]) {
  str[0] = correspondancelettrechiffre(a);
  str[1] = b + '0' + 1;
  str[2] = correspondancelettrechiffre(c);
  str[3] = d + '0' + 1;
  str[4] = '\0';
}


char correspondancelettrechiffre(int a) {
  /* mode bourrin */

  switch (a) {
  case 0:
    return 'a';
  case 1:
    return 'b';
  case 2:
    return 'c';
  case 3:
    return 'd';
  case 4:
    return 'e';
  case 5:
    return 'f';
  case 6:
    return 'g';
  case 7:
    return 'h';
  default :
    return 'z';
  }
}
