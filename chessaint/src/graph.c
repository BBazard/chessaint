/** 
 *  @file graph.c
 *  @brief graph structure basic functions
 *
 *  This file implements functions to add or remove Arc from a linked list, totally suppress a list and print an Arc or a list
 *
 */






#include "../include/graph.h"

/** 
 *  @fn void llist_add (Arc newvalue, Llist *list)
 *  @brief Adds an Arc a specified Llist
 *  @param[in] newvalue The Arc value to add
 *  @param[in,out] list Pointer on the targeted list, must be NULL if the list is empty
 *  The *Llist can be Null pointer, in this case, the list take newvalue as the first element
 */

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

/** 
 *  @fn Arc llist_suppr (Llist *list) 
 *  @brief Suppress and element
 *  @param[in,out] list Pointer on the targeted Llist, not NULL normally
 *  @return First object in the list, NULL if the list was empty.
 *
 *  This function print the "Empty list" string when list parameter was NULL, and also free memory space
 *
 */

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

/** 
 *  @fn void llist_free (Llist *list)
 *  @brief Suppress all elements
 *  @param[in,out] list Pointer on the targeted Llist
 *
 *  Use the llist_suppr function to suppress every element and let the targeted list poiting on NULL at the end of process
 *
 */

void llist_free (Llist *list) {
  while (*list != NULL)
    llist_suppr(list);
}

/** 
 *  @fn void arc_print (Arc value)
 *  @brief Print an Arc
 *  @param[in] value Arc to print, all elements of the structure must be defined
 *
 *  Print the content of an Arc in a formated output (on stdout), the content is print as the following example :
 *  Ex : #0| e4--2->e5 | Set : none | Color : white
 *
 */

void arc_print (Arc value) {
  char* set;
  char* color;

  if (value.whichSet == 0)
    set="none";
  else if (value.whichSet == 1)
    set="open";
  else
    set="closed";

  if (value.activeColor == 'w')
    color="white";
  else
    color="black";
  printf("#%d| %s--%d->%s | Set : %s | Color : %s\n", value.id, value.from, value.score, value.to, set, color);
}

/** 
 *  @fn void llist_print (Llist list)
 *  @brief Print a Llist
 *  @param[in] list Llist to print, can be NULL if the list is empty
 *  
 *  Print the content of a Llist, if list is a NULL pointer, print the "Empty Llist" string
 *  No side effects
 */

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

