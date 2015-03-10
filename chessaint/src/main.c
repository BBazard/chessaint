#include "../include/graph.h"
#include "../include/chessboard.h"

int main(void) {
  printf("\n\n");
  printf("Welcome in ChessAint !\n");
  printf("**************************\n");
  int cur;

  Arc arc;
  arc.id=0;
  arc.from="e4";
  arc.to="e5";
  arc.score=5;
  arc.whichSet=none;
  arc.whoPlays=white;
  
  Arc arc2;
  arc2.id=1;
  arc2.from="d4";
  arc2.to="d5";
  arc2.score=6;
  arc2.whichSet=open;
  arc2.whoPlays=black;
  

  Llist list=NULL;
  llist_add(arc,&list);
  llist_add(arc2,&list);


  while (1) {
    printf("\n\n");
    printf("---------------------------------------------\n");
    printf("- 1 to print list of transitions\n");
    printf("- 2 to play moves on a board (no rules yet :p)\n");
    printf("- 3 to exit \n");
    printf("----------------------------------------------\n\n");

    scanf("%d", &cur);
    switch (cur) {
      case 1:
        llist_print(list);
        break;
      case 2:
        humanVHuman();
        break;
      case 3:
        return EXIT_SUCCESS;
        break;
    }
  }

  return 0;
}

