/* This file is part of the ChessAInt project 2015 */
/**
 *  @file
 */

#include "include/llist.h"

#include <assert.h>
#include <string.h>

/**
 *  @fn void arc_alloc(Arc *arc)
 *  @brief Inits an Arc
 *  @param[out] arc The arc to init
 *
 *  Inits arc and set its score to 0
 *
 */

void arc_alloc(Arc *arc) {
  arc->score = 0;
  arc->data = malloc(sizeof(mpz_t));
  stack_alloc(arc->data);
}

/**
 *  @fn void arc_free(Arc *arc)
 *  @brief Free an Arc
 *  @param[out] arc The arc to free
 *
 */

void arc_free(Arc *arc) {
  stack_free(arc->data);
  free(arc->data);
}

/**
 *  @fn void llist_add(Arc newvalue, Llist *list)
 *  @brief Adds an Arc a specified Llist
 *  @param[in] newvalue The Arc value to add
 *  @param[in,out] list Pointer on the targeted list, must be NULL if the list is empty
 *
 *  @bug Need to free the inited arcs (init IS needed)
 *
 *  @note The *Llist can be Null pointer, in this case,
 *  the list take newvalue as the first element, more, it should be NULL if empty.
 *
 */

void llist_add(Arc newvalue, Llist *list) {
  Element *newelement = malloc(sizeof(Element));
  arc_alloc(&(newelement->value));
  newelement->value.score = newvalue.score;
  mpz_set(*(newelement->value.data), *(newvalue.data));
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
    arc_free(&(tmp.value));
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
 *  @fn int llist_shorten(Llist *list, int from)
 *  @brief Shorten a llist
 *  @param[in,out] list The list to shorten
 *  @param[in] from Starting point of deletion
 *  @return 1 If something was suppressed
 *  @return 0 Otherwise
 *
 *  Suppress all elements after the point of deletion
 *
 */

int llist_shorten(Llist *list, int from) {
  Llist tmp = *list;
  Llist tmp2;
  for (int i = 1; i < from; ++i) {
    tmp = tmp->next;
    if (tmp->next == NULL)
      return 0;
  }
  tmp2 = tmp->next;
  tmp->next = NULL;
  llist_free(&tmp2);
  return 1;
}

/**
 *  @fn int llist_length(Llist list)
 *  @brief Computes the number of element of a llist
 *  @param[in] list The list to parse
 *  @return int The number of elements
 *
 */

int llist_length(Llist list) {
  Llist tmp = list;
  int ret = 0;
  while (tmp != NULL) {
    tmp = tmp->next;
    ret++;
  }
  return ret;
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
  identifier_print(*(value.data));
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
          identifier_is_equal(*(left.data), *(right.data)));
}

/**
 *  @fn void arc_extract(Arc arc, int move, int score)
 *  @brief Extract score and first move of the arc
 *  @param[in] arc The arc of which to extract data
 *  @param[out] move The first move of this arc
 *  @param[out] score The score of this arc
 *
 */

void arc_extract(Arc arc, int *move, int *score) {
  int tmp;
  Stack s;
  stack_alloc(&s);
  *score = arc.score;

  identifier_to_stack(*(arc.data), &s);
  while ( (tmp = stack_pop(&s)) != -1)
    *move = tmp;
}
