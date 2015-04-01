/*This file is part of the ChessAInt project 2015*/
#ifndef TRUNK_CHESSAINT_INCLUDE_LLIST_H_
#define TRUNK_CHESSAINT_INCLUDE_LLIST_H_

#include <stdlib.h>
#include <stdio.h>

/** 
 *  @enum Set
 *  @brief Which set belongs the item
 *
 *  This enumeration represents the set in which
 *  is the item for astar calculation
 *
 */

enum Set {
  none, /**< Not belonging to any set */
  open, /**< Belongs to open set */
  closed /**< Belongs to closed set */
};


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
 *  @bug Problem of initialisation
 *
 *  It stores the game data we need, according to the data contained
 *  in a FEN string (5 last attributes).
 */

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

void llist_add(Arc newvalue, Llist *list);
int llist_suppr(Llist *list);
void llist_free(Llist *list);

void arc_print(Arc value);
int arc_equal(Arc left, Arc right);
void llist_print(Llist list);



#endif /*TRUNK_CHESSAINT_INCLUDE_LLIST_H_*/
