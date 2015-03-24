#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool IsAKnightMove(char Cfrom, int Lfrom, char Cto, int Lto) {
if ((Cto == (Cfrom + 2)) || (Cto == (Cfrom - 2))) {
     if ((Lto == (Lfrom + 1)) || (Lto == (Lfrom - 1)))
       return true ;}
if ((Cto == (Cfrom + 1)) || (Cto == (Cfrom - 1))) {
  if ((Lto == (Lfrom + 2)) || (Lto == (Lfrom - 2)))
     return true ;}
return false;
}

