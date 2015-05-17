/* This file is part of the ChessAInt project 2015 */
/**
 *  @file
 */

#include "include/llist.h"

#include <assert.h>
#include <string.h>

/**
 *  @fn void node_alloc(Node *node)
 *  @brief Inits an Node
 *  @param[out] node The node to init
 *
 *  Inits node and set its score to 0
 *
 */
void node_alloc(Node *node) {
  node->score = 0;
  node->data = malloc(sizeof(mpz_t));
  stack_alloc(node->data);
}

/**
 *  @fn void node_free(Node *node)
 *  @brief Free an Node
 *  @param[out] node The node to free
 *
 */
void node_free(Node *node) {
  stack_free(node->data);
  free(node->data);
}

/**
 *  @fn void llist_add(Node newvalue, Llist *list)
 *  @brief Adds an Node a specified Llist
 *  @param[in] newvalue The Node value to add
 *  @param[in,out] list Pointer on the targeted list, must be NULL if the list is empty
 *
 *  @bug Need to free the inited arcs (init IS needed)
 *
 *  @note The *Llist can be Null pointer, in this case,
 *  the list take newvalue as the first element, more, it should be NULL if empty.
 *
 */
void llist_add(Node newvalue, Llist *list) {
  Element *newelement = malloc(sizeof(Element));
  node_alloc(&(newelement->value));
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
 *  @fn int llist_rm_first(Llist *list)
 *  @brief Suppress an element
 *  @param[in,out] list Pointer on the targeted Llist, not NULL normally
 *  @return 0 if the first element was suppressed successfully
 *  @return 1 otherwise
 *
 *  This function suppress the first element of the targeted Llist,
 *  returns 0 if processed normally.
 *
 */
int llist_rm_first(Llist *list) {
  Element *next;

  if (*list == NULL) {
      return 1;
  } else {
    next = (*list)->next;
    node_free(&((*list)->value));
    free(*list);
    *list = next;

    return 0;
  }
}

/**
 *  @fn void llist_free(Llist *list)
 *  @brief Suppress all elements
 *  @param[in,out] list Pointer on the targeted Llist
 *
 *  Use the llist_rm_first function to suppress every element
 *  and let the targeted list pointing on NULL at the end of process
 *
 */
void llist_free(Llist *list) {
  while (*list != NULL)
    llist_rm_first(list);
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
  if (from == -1)
    return 0;
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
 *  @fn void llist_concatenate(Llist *list, Llist to_concat)
 *  @brief Add all elements of a list to another
 *  @param[in, out] list The list in which are added elements
 *  @param[in] to_concat The list to add to the other
 *
 */
void llist_concatenate(Llist *list, Llist to_concat) {
  Llist tmp = to_concat;
  while (tmp != NULL) {
    llist_add(tmp->value, list);
    tmp = tmp->next;
  }
}

void llist_print(Llist list) {
  Element *tmp;
  tmp = list;
  if (list == NULL) {
    printf("Empty Llist\n");
  } else {
    while (tmp !=NULL) {
      node_print(tmp->value);
      tmp = tmp->next;
    }
  }
}

/**
 *  @fn void node_print(Node value)
 *  @brief Print an Node
 *  @param[in] value Node to print, all elements of the structure must be defined
 *
 *  Print the content of an Node in a formated output (on stdout), the content is print as the following example :
 *  Ex : #0| e4--2->e5 | Set : none | Color : white
 *
 */
void node_print(Node value) {
  printf("%d", value.score);
  identifier_print(*(value.data));
}

/**
 *  @fn int node_is_equal(Node left, Node right)
 *  @brief Test if to node are equals
 *  @param[in] left The left member of the equality
 *  @param[in] right The right member of the equality
 *  @return 1 if the two arcs are equal
 *  @return 0 otherwise
 *
 *  Returns 1 if every component of the two node are equal, 0 if not.
 */
int node_is_equal(Node left, Node right) {
  return (left.score == right.score &&
          identifier_is_equal(*(left.data), *(right.data)));
}

/**
 *  @fn void node_extract(Node node, int move, int score)
 *  @brief Extract score and first move of the node
 *  @param[in] node The node of which to extract data
 *  @param[out] move The first move of this node
 *  @param[out] score The score of this node
 *
 */
void node_extract(Node node, int *move, int *score) {
  int tmp;
  Stack s;
  stack_alloc(&s);
  *score = node.score;

  identifier_to_stack(*(node.data), &s);
  while ( (tmp = stack_pop(&s)) != -1)
    *move = tmp;
  stack_free(&s);
}

/**
 *  @fn void node_copy(Node source, Node *dest)
 *  @brief Copy node source in node dest
 *  @param[in] source The original node
 *  @param[out] dest Pointer on the destination node
 *
 *  @note dest MUST be initialized before
 *
 */
void node_copy(Node source, Node *dest) {
  dest->score = source.score;
  mpz_set(*(dest->data), *(source.data));
}

