#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool IsAKnightMove (char Cfrom, int Lfrom, char Cto, int Lto){

if ( 'Cinto' == ('Cfrom' +2) || 'Cinto' == ('Cfrom' -2)) {
     if (Lto == (Lfrom +1) || Lto == (Lfrom - 1))
       return true ;}
if ( 'Cinto' == ('Cfrom' +1) || 'Cinto' == ('Cfrom' -1)) {
  if (Lto == Lfrom +2 || Lto == Lfrom - 2)
     return true ;}
return false;
}

