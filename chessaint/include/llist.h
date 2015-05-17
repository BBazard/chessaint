/* This file is part of the ChessAInt project 2015 */
/**
 *  @file
 */

#ifndef CHESSAINT_INCLUDE_LLIST_H_
#define CHESSAINT_INCLUDE_LLIST_H_

#include <stdlib.h>
#include <stdio.h>

#include "include/identifier.h"

/**
 *  @struct Node
 *  @brief Represents the node between two nodes of a graph
 *
 *  Stores the score a given board (for astar computation)
 *  and the others data about the game we need.
 *  For description of how data are handled read about
 *  Identifier type
 *
 */
struct Node {
  int score; /**< The score of the node */
  Identifier *data; /**< All the others data */
};

/**
 *  @param Node Define struct Node as type
 */
typedef struct Node Node

/**
 *  @struct Element
 *  @brief Definition of an list element
 *
 */
struct Element {
  Node value; /**< The value of the element, an node */
  struct Element *next; /**< The link to the next element of the list */
};

/**
 *  @param Element Define struct Element as type
 */
typedef struct Element Element;

/**
 *  @typedef Llist
 *  @brief Definition of the Llist type
 *
 *  Defines type Llist as a pointer on type Element (=struct Element).
 *
 */
typedef Element *Llist;

void node_alloc(Node *node);
void node_free(Node *node);

void llist_add(Node newvalue, Llist *list);
int llist_rm_first(Llist *list);
void llist_free(Llist *list);
int llist_shorten(Llist *list, int from);
int llist_length(Llist list);
void llist_concatenate(Llist *list, Llist to_concat);

void node_print(Node value);
int node_is_equal(Node left, Node right);
void node_extract(Node node, int *move, int *score);
void node_copy(Node source, Node *dest);

#endif /* CHESSAINT_INCLUDE_LLIST_H_ */

