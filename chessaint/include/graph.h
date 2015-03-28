/* This file is part of the ChessAInt project 2015 */
/** 
 *  @file graph.h
 *  @brief graph structure header
 *
 *  This file implements enumerations and structures for the graph item and 
 *  the prototype of the functions developped in graph.c file
 *
 */

#ifndef TRUNK_CHESSAINT_INCLUDE_GRAPH_H_
#define TRUNK_CHESSAINT_INCLUDE_GRAPH_H_

#include <stdlib.h>
#include <stdio.h>

/** 
 *  @enum Set
 *  @brief Which set belongs the item
 *  
 *  This enumeration represents the set in which is the item for astar calculation
 *  
 */

enum Set {
  none, /**< Not belonging to any set */
  open, /**< Belongs to open set */
  closed /**< Belongs to closed set */
};


/** 
 *  @struct Arc
 *  @brief Represents the arc between two nodes of a graph
 *  @bug Problem of initialisation
 *
 *  It stores the game data we need, according to the data contained
 * in a FEN string (5 last attributes).
 */

typedef struct Arc Arc;
struct Arc {
  int id;                /**< The id of the arc */
  char from[3];          /**< from  */
  char to[3];            /**< to */
  int score;             /**< The cumulated score of the move */
  enum Set whichSet;     /**< The set in which is the arc for astar */
  char activeColor;      /**< "w" for white and "b" for black */

  /** 
   * @todo the documentation suggest an enumeration
   *
   * "-" for none,
   * "K" if castle on white King side available
   * "Q" if castle on white Queen side,
   * "k" and "q" for equivalent on black side
   * Ex : "-"; "KQkq"; "K"
   */
  char* castlingAvailability;

  /** 
   * position behind the pawn which
   * has just done 2 squares move
   * or if none "-"
   */
  char* enPassant;

  /** 
   * number of half moves since
   * last capture or pawn advance
   */
  int halfmoveClock;

  /** 
   * the number of full movey
   * Starts at one, +1 after a black's move
   */
  int fullmoveNumber;
};

/** 
 *  @struct Element
 *  @brief Definition of an list element
 *
 */

typedef struct Element Element;
struct Element {
  Arc value; /**< The value of the element, an arc */
  struct Element *next; /**< The link to the next element of the list */
};

typedef Element *Llist;

void llist_add(Arc newvalue, Llist *list);
int llist_suppr(Llist *list);
void llist_free(Llist *list);

void arc_init(Arc *arc);
void arc_print(Arc value);
int arc_equal(Arc left, Arc right);
void llist_print(Llist list);

#endif /*TRUNK_CHESSAINT_INCLUDE_GRAPH_H_*/

