#include "../include/concatenate.h"

void getUciString(int a, int b, int c, int d, char str[5]) {

str[0]=correspondancelettrechiffre(a) ;
 str[1]= b + 'a'-'0' ;
str[2]=correspondancelettrechiffre(c) ;
 str[3]= d+'a'-'0' ;
str[4]= '\0';

}

char correspondancelettrechiffre (int a) {   /* mode bourrin */
switch(a){

case 0:

    return 'a' ;
case 1:

    return 'b' ;
case 2:

    return 'c' ;
case 3:

    return 'd' ;
case 4:

    return 'e' ;
case 5:

    return 'f' ;
case 6:

    return 'g' ;
case 7:

    return 'h' ;
default :

   return 'z';
    }}

