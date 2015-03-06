#include "../include/graph.h"

int main(void) {
  
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
  llist_print(list);

  return 0;
}

