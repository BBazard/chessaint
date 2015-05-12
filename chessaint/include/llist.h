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
 *  @typedef Arc
 *  @brief Definition of the Arc type
 *
 *  Defines struct Arc as the Arc type
 *
 */

typedef struct Arc Arc;

/** 
 *  @struct Arc
 *  @brief Represents the arc between two nodes of a graph
 *
 *  Stores the score a given board (for astar computation)
 *  and the others data about the game we need.
 *  For description of how data are handled read about
 *  Identifier type
 *
 */

struct Arc {
  int score; /**< The score of the arc */
  Identifier *data; /**< All the others data */
};

/** 
 *  @typedef Element
 *  @brief Definition of the Element type
 *
 *  Defines struct Element as the Element type
 *
 */

typedef struct Element Element;

/** 
 *  @struct Element
 *  @brief Definition of an list element
 *
 */

struct Element {
  Arc value; /**< The value of the element, an arc */
  struct Element *next; /**< The link to the next element of the list */
};

/** 
 *  @typedef Llist
 *  @brief Definition of the Llist type
 *
 *  Defines type Llist as a pointer on type Element (=struct Element).
 *
 */

typedef Element *Llist;

void arc_alloc(Arc *arc);
void arc_free(Arc *arc);

void llist_add(Arc newvalue, Llist *list);
int llist_suppr(Llist *list);
void llist_free(Llist *list);
int llist_shorten(Llist *list, int from);
int llist_length(Llist list);

void arc_print(Arc value);
int arc_is_equal(Arc left, Arc right);
void arc_extract(Arc arc, int *move, int *score);

#endif /* CHESSAINT_INCLUDE_LLIST_H_ */

