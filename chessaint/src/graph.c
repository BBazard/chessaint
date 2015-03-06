#include "../include/graph.h"

void llist_add (Arc newvalue, Llist *list) {
  Element *newelement = malloc(sizeof(Element));
  newelement->value=newvalue;
  newelement->next=NULL;
 
  if (*list==NULL) {
    *list=newelement;
  }
  else {
    Element *tmp = *list;
    while (tmp->next != NULL)
      tmp = tmp->next;

    tmp->next = newelement;
  }

}

Arc llist_suppr (Llist *list) {
  Element tmp;

  if (*list == NULL) {
      printf("Empty Llist");
      return ;
  }
  else {
    tmp = **list;
    free(*list);
    *list = tmp.next;
    
    return tmp.value;
  }
}

void arc_print(Arc value) {
  printf("#%d| %s--%d->%s | Set : %d | Color : %d\n", value.id, value.from, value.score, value.to, value.whichSet, value.whoPlays);
}

void llist_free (Llist *list) {
  while (*list != NULL)
    llist_suppr(list);
}

void llist_print (Llist list) {
  Element *tmp;
  tmp = list;
  if (list == NULL)
    printf("Empty Llist\n");
  else {
    while (tmp !=NULL) {
      arc_print(tmp->value);
      tmp = tmp->next;
    }
  }
}

