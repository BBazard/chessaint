#include "../include/graph.h"

int main(void) {
  
  Arc arc;
  arc.id=0;
  arc.from="c";
  arc.to="d";
  arc.score=5;
  arc.whichSet=none;
  arc.whoPlays=white;
  
  Arc arc2;
  arc2.id=1;
  arc2.from="d";
  arc2.to="e";
  arc2.score=6;
  arc2.whichSet=open;
  arc2.whoPlays=black;
  

  Llist list=NULL;
  llist_add(arc,&list);
  llist_add(arc2,&list);
  llist_print(list);

  return 0;
}

