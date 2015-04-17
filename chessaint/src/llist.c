/*This file is part of the ChessAInt project 2015*/

#include "include/llist.h"

#include <assert.h>
#include <string.h>

/**
 *  @fn void llist_add(Arc newvalue, Llist *list)
 *  @brief Adds an Arc a specified Llist
 *  @param[in] newvalue The Arc value to add
 *  @param[in,out] list Pointer on the targeted list, must be NULL if the list is empty
 *  The *Llist can be Null pointer, in this case, the list take newvalue as the first element
 */

void llist_add(Arc newvalue, Llist *list) {
  Element *newelement = malloc(sizeof(Element));
  newelement->value = newvalue;
  newelement->next = NULL;

  if (*list == NULL) {
    *list = newelement;
  } else {
    if ( ((*list)->value).score < newvalue.score ) {
      newelement->next = *list;
      *list = newelement;
    } else {
      Element *tmp = *list;
      while (tmp->next != NULL && ((tmp->next)->value).score > newvalue.score)
        tmp = tmp->next;
      newelement->next = tmp->next;
      tmp->next = newelement;
    }
  }
}

/**
 *  @fn int llist_suppr(Llist *list)
 *  @brief Suppress an element
 *  @param[in,out] list Pointer on the targeted Llist, not NULL normally
 *  @return 0 if the first element was suppressed succefully
 *  @return 1 otherwise
 *
 *  This function suppress the first element of the targeted Llist,
 *  returns 0 if processed normally.
 *
 */

int llist_suppr(Llist *list) {
  Element tmp;

  if (*list == NULL) {
      return 1;
  } else {
    tmp = **list;
    free(*list);
    *list = tmp.next;

    return 0;
  }
}

/**
 *  @fn void llist_free(Llist *list)
 *  @brief Suppress all elements
 *  @param[in,out] list Pointer on the targeted Llist
 *
 *  Use the llist_suppr function to suppress every element
 *  and let the targeted list poiting on NULL at the end of process
 *
 */

void llist_free(Llist *list) {
  while (*list != NULL)
    llist_suppr(list);
  *list = NULL;
}

/**
 *  @fn void arc_print(Arc value)
 *  @brief Print an Arc
 *  @param[in] value Arc to print, all elements of the structure must be defined
 *
 *  Print the content of an Arc in a formated output (on stdout), the content is print as the following example :
 *  Ex : #0| e4--2->e5 | Set : none | Color : white
 *
 */

void llist_print(Llist list) {
  Element *tmp;
  tmp = list;
  if (list == NULL) {
    printf("Empty Llist\n");
  } else {
    while (tmp !=NULL) {
      arc_print(tmp->value);
      tmp = tmp->next;
    }
  }
}

/**
 *  @fn void arc_print(Arc value)
 *  @brief Print an Arc
 *  @param[in] value Arc to print, all elements of the structure must be defined
 *  @todo transform "set" into an enumeration
 *
 *  Print the content of an Arc in a formated output (on stdout), the content is print as the following example :
 *  Ex : #0| e4--2->e5 | Set : none | Color : white
 *
 */

void arc_print(Arc value) {
  printf("%d", value.score);
  identifier_print(value.data);
}

/**
 *  @fn int arc_is_equal(Arc left, Arc right)
 *  @brief Test if to arc are equals
 *  @param[in] left The left member of the equality
 *  @param[in] right The right member of the equality
 *  @return 1 if the two arcs are equal
 *  @return 0 otherwise
 *
 *  Returns 1 if every component of the two arc are equal, 0 if not.
 */

int arc_is_equal(Arc left, Arc right) {
  return (left.score == right.score &&
          identifier_is_equal(left.data, right.data));
}



